#include <stdio.h>
#include <string.h>

double taylorTanNextTerm(double term,double angle, const double *num, const double *denom, int i){
   return term * ((num[i]*angle*angle) / num[i-1]) / (denom[i]/denom[i-1]);
}

double taylor_tan(double angle, unsigned int n){
   const double num[13] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582,
                     443861162, 18888466084, 113927491862, 58870668456604};
   const double denom[13] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625,
                       194896477400625, 49308808782358125, 3698160658676859375};

   double term = angle;
   double result = angle;

   for(unsigned int i = 1; i < n; i++){
      printf("Term %f\n", term);
      term = taylorTanNextTerm(term, angle, num, denom, i);
      result += term;
   }

   return result;
}

int main(int argc, char *argv[]) {
   if(argc == 2 && !strcmp(argv[1], "--help"))
      printf("Napoveda coming soon!!!\n");
   else {
      fprintf(stderr, "Wrong argument\n");
      //return -1;
   }

   printf("Vysledok je %f\n", taylor_tan(1.024, 10));
   printf("Hello\n");
   return 0;
}