#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){

/*
    // 1. Show default argument (./PassArg has 1 argument)
    printf("argc is: %d\n",argc);
        
    int i;
    for(i = 0;i < argc; i++){

        printf("argv[%d] = %s\n",i,argv[i]);

    }

    // 2. Show how to read more command line argument
    // 3. Exercise: Adding all numbres in command line argument.
*/

    int i;
    int sum;
    for(i = 1; i < argc; i++){

        sum = sum + atoi(argv[i]);

    }

    printf("The sum of the arguments is : %d\n",sum);

    return 0;

}
