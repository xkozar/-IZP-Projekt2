/**********************************************************
 * proj2 Iteracne vypocty
 * author: Tomas Kozar xkozar02
 * last edited: 14.november 2017
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define NUMOFCOEFS 13
#define DEFAULTHEIGHT 1.5
#define MAXITERATIONS 13
#define MEASUREITERATIONS 13

/**
 * Checks whether passed string is float
 * @param [in] str
 * @return true if string is float, else false
 */
bool stringIsFloat(char *str){
   bool dot = false;
   for(unsigned int i = 0; i < strlen(str); i++){
      if(!isdigit(str[i]) && str[i] != '.'){
         return false;
      }
      if(str[i] == '.' && !dot)
         dot = true;
      else if(str[i] == '.')
         return false;
   }
   return true;
}

/**
 * Checks whether or not there are only numbers in passed string
 * @param [in] str
 * @return true if there are only numbers in string, else false
 */
bool stringIsNumber(char *str){
   for(unsigned int i = 0; i < strlen(str); i++){
      if(!isdigit(str[i])) {
         return false;
      }
   }
   return true;
}

/**
 * Calculates next term in calculated polynomial
 * @param [in] term current term
 * @param [in] angle angle used for calculation
 * @param [in] num array containing defined values of numerator
 * @param [in] denom array containing defined values of denominator
 * @param [in] i number of current iteration
 * @return next term
 */
double taylorTanNextTerm(double term,double angle, const double *num, const double *denom, int i){
   return term * ((num[i]*angle*angle) / num[i-1]) / (denom[i]/denom[i-1]);
}

/**
 * Calculates value of tangens(angle) using taylor polynomial
 * @param [in] angle value of angle in radians used for calculation
 * @param [in] n number of iterations. Max. 13
 * @return tangens of passed angle
 */
double taylor_tan(double angle, unsigned int n){
   const double num[NUMOFCOEFS] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582,
                     443861162, 18888466084, 113927491862, 58870668456604};
   const double denom[NUMOFCOEFS] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625,
                       194896477400625, 49308808782358125, 3698160658676859375};
   double term = angle;
   double result = angle;

   for(unsigned int i = 1; i < n; i++){
      term = taylorTanNextTerm(term, angle, num, denom, i);
      result += term;
   }

   return result;
}

/**
 * Calculates value of tangens(angle) using continued fractions
 * @param [in] angle value of angle in radians used for calculation
 * @param [in] n number of iterations. Max. 13
 * @return tangens of passed angle
 */
double cfrac_tan(double angle, unsigned int n){
   double a;
   const double b = angle*angle;
   double result = 0.;
   for(unsigned int i = n; i > 0; i--){
      a = i + i - 1;
      result = b/(a-result);
   }
   return result/angle;
}

/**
 * Prints individual calculations and their difference
 * @param [in] degree used for calculations of tangens
 * @param [in] iterations number of iterations used for methods
 */
void printValues(double degree, int iterations){
   double taylorTan = taylor_tan(degree, iterations);
   double cfracTan = cfrac_tan(degree, iterations);
   double mathTan = tan(degree);

   printf("%d %e %e %e %e %e\n", iterations, mathTan, taylorTan,
          fabs(mathTan-taylorTan), cfracTan, fabs(mathTan-taylorTan));
}

/**
 * Cycles throu range of iterations and prints individual calculations and their differences
 * @param [in] degree used for caltulations of tangens
 * @param [in] N first number of iterations
 * @param [in] M last number of iterations
 */
void compareTanCalcs(double degree, int N, int M){
   if(M > MAXITERATIONS)
      fprintf(stderr, "Arguement M too high");
   if(N < 1 || M < N) {
      fprintf(stderr, "Wrong values of arguements N and/or M");
      exit(1);
   }
   printf("%.10e\n", degree);
   for(int i = N; i <= M; i++){
      printValues(degree, i);
   }
}

/**
 * Calculates and prints results of measurements
 * @param [in] alpha alpha angle used for calculating distance of measurement device from object
 * @param [in] beta beta angle used for calculating objects height
 * @param [in] deviceHeight height in which is device positioned
 * @param [in] betaIncluded tells if we also do calculation for beta
 */

void measurement(double alpha, double beta, double deviceHeight, bool betaIncluded){
   double d = deviceHeight/cfrac_tan(alpha, MEASUREITERATIONS);
   printf("%.10e\n", d);

   if(betaIncluded){
      printf("%.10e\n", (d*cfrac_tan(beta, MEASUREITERATIONS)) + deviceHeight);
   }
}

/**
 * Checks and evaluate in-line arguments used for measurement
 * @param [in] argc number of arguments
 * @param [in] argv 2d array of chars
 */
void checkMeasurementArguments(int argc, char *argv[]){
   double alpha;
   double beta = 0.;
   double deviceHeight = DEFAULTHEIGHT;
   bool betaIncluded = false;
   //printf("%d", strcmp(argv[1], "-m"));
   if(argc == 6 && !strcmp(argv[1], "-c") && !strcmp(argv[3], "-m")){
      if(stringIsFloat(argv[2]) && stringIsFloat(argv[4]) && stringIsFloat(argv[5])){
         alpha = atof(argv[4]);
         beta = atof(argv[5]);
         deviceHeight = atof(argv[2]);
         betaIncluded = true;
      }
      else{
         fprintf(stderr, "Wrong argument/s\n");
         exit(1);
      }
   }
   else if(argc == 5 && !strcmp(argv[1], "-c") && !strcmp(argv[3], "-m")){
      if(stringIsFloat(argv[2]) && stringIsFloat(argv[4])){
         alpha = atof(argv[4]);
         deviceHeight = atof(argv[2]);
      }
      else{
         fprintf(stderr, "Wrong argument/s\n");
         exit(1);
      }
   }
   else if(argc == 4 && !strcmp(argv[1], "-m")&& stringIsFloat(argv[2]) && stringIsFloat(argv[3])){
      alpha = atof(argv[2]);
      beta = atof(argv[3]);
      betaIncluded = true;
   }
   else if(argc == 3 && !strcmp(argv[1], "-m") && stringIsFloat(argv[2])){
      alpha = atof(argv[2]);
   }
   else{
      fprintf(stderr, "Wrong argument/s\n");
      exit(1);
   }
   measurement(alpha, beta, deviceHeight, betaIncluded);
}

int main(int argc, char *argv[]) {

   if(argc == 2 && !strcmp(argv[1], "--help")) {
      printf("Napoveda coming soon!!!\n");
      return 0;
   }
   else if(argc == 5 && !strcmp(argv[1], "--tan")) {
      if(stringIsFloat(argv[2]) && stringIsNumber(argv[3]) && stringIsNumber(argv[4]))
         compareTanCalcs(atof(argv[2]), atoi(argv[3]), atoi(argv[4]));
      else {
         fprintf(stderr, "Wrong format of arguement/s A,N and/or N");
         return 1;
      }
   }
   else if(argc == 3 || argc == 4 || argc == 6){
      checkMeasurementArguments(argc, argv);
   }
   else {
      fprintf(stderr, "Wrong argument/s\n");
      return 1;
   }

   return 0;
}