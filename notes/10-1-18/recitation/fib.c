#include<stdio.h>
#include<stdlib.h>

int fib(int n){
    if(n == 0)
        return 0;
    if(n ==  1)
        return 1;
    int fibm1 = fib(n-1);
    int fibm2 = fib(n-2);
    return fibm1 + fibm2;
}


int main(int argc,char** argv){

    if(argc !=2){
        printf("Please input the correct number of arguments\n");
        return -1;
    }

    int num = atoi(argv[1]);
    int fibNum = fib(num);
    printf("Fibonacci Number: %d\n",fibNum);    

    return 0;
}
