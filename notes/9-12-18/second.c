#include<stdio.h>
#include<stdlib.h>

long factorial (int);

int mynum = 0;

int main(int argc, char** argv){
  long result;
  printf("Hello World CS211 \n");
  
  if(argc != 2){
  printf("Insufficient arguments\n");
  return 0;
  }

  mynum = atoi(argv[1]);

  /*
 
  printf("Arguments to this program are:\n");
  for(int x=0;x<argc;x++){
   printf("Argument no. %d is %s\n",x,argv[x]);
  }
 
 */

  result = factorial(mynum);
  printf("Factorial of %d is %ld\n",mynum, result);

  return 0; 

}

long factorial(int n){

  if(n <=1) return 1;
  return n * factorial(n-1);
}

