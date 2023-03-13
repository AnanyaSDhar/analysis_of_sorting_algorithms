#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double rand_gen() {
   // return a uniformly distributed random value
   return ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
}
double normalRandom() {
   // return a normally distributed random value
   double v1=rand_gen();
   double v2=rand_gen();
   return cos(2*3.14*v2)*sqrt(-2.*log(v1));
}
main() {

   FILE *file;
   file = fopen("normal100.txt", "w");
   if(file == NULL){
      printf("Error!");
      exit(1);
   }

   double sigma = 10.0;
   double Mi = 50.0;
   for(int i=0;i<100000;i++) {
      double x = normalRandom()*sigma+Mi;
      fprintf(file,"%d ",(int)x);
   }

}