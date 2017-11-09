#include <stdio.h>
#include <string.h>

double taylor_tan(double x, unsigned int n){
   unsigned long num[13] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582,
                     443861162, 18888466084, 113927491862, 58870668456604};
   unsigned long denom[13] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625,
                       194896477400625, 49308808782358125, 3698160658676859375};

   double term = x;
   double result = x;

   for(int i = 0; i < n; i++){
      //term =
      result += term;
   }

   return 0.;
}

int main(int argc, char *argv[]) {
   if(argc == 2 && !strcmp(argv[1], "--help"))
      printf("Napoveda coming soon!!!\n");
   else {
      fprintf(stderr, "Wrong argument");
      return -1;
   }

   printf("Hello\n");
   return 0;
}