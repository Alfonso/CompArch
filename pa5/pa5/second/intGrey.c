#include"second.h"


int* tint_to_grey(int in,int numInput){

    int* bin = (int*)malloc(sizeof(int)*numInput);    

    unsigned int mask = 1U << (numInput - 1);

    int counter = 0;
    for(counter=0;counter<numInput;counter++){
        bin[counter] = (in & mask) ? 1 : 0;
        in <<= 1;
    }

    // binary values stored in bin
    // convert to grey and store in ret_val

    int* ret_val = (int*)malloc(sizeof(int)*numInput);    

    // first val is the same
    ret_val[0] = bin[0];
    printf("%d",ret_val[0]);


    for(counter=1;counter<numInput;counter++){
        ret_val[counter] = bin[counter] ^ bin[counter-1];
        printf("%d",ret_val[counter]);
    }

    printf("\n");

    return ret_val;
}


int main(int argc,char** argv){

    int inputNum = 4;

    return 0;
}
