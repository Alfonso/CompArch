#include<stdio.h>
#include<stdlib.h>


int main(int argc,char** argv){

    int myArray[10];
    int i;
    for(i = 0;i<10;i++){
        myArray[i] = i;
    }

    printf("The value of myArray: %p\n",myArray);
    printf("The address of myArray[0]: %p\n",&(myArray[0]));

    printf("The value of my myArray+1: %p\n",(myArray+1));
    

    return 0;
}
