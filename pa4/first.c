#include"first.h"

int main(int argc,char** argv){
    int cacheSize;
    int n;
    char* policy;
    int blockSize;
    FILE* trace;
// check arguments and stuff
    if(argc!=6){
        printf("error");
        printf("Input correct # of args\n");
        return -1;
    }

    cacheSize = atoi(argv[1]);
    if(powerOfTwo(cacheSize) == 0 ){
        printf("error");
        printf("Cache Size: %d is not a power of two\n",cacheSize);
        return -1;
    }

    n = setAssoc(argv[2]);
    if(n==-1){
        // direct
    }else if(n==-2){
        // assoc
    }else if(n==-3){
        printf("error");
        printf("Associativity is incorrect\n");
        return -1;
    }else{
        // assoc:n
        // check if n is a power of 2
        if(powerOfTwo(n) == 0){
            printf("error");
            printf("N is not a power of 2\n");
            return -1;
        }
    }

    policy = argv[3];
    if(strcmp(policy,"fifo") != 0){
        printf("error");
        printf("Cache policy is not valid\n");
        return -1;
    }

    blockSize = atoi(argv[4]);
    if(powerOfTwo(blockSize) == 0 ){
        printf("error");
        printf("Block Size: %d is not a power of two\n",blockSize);
        return -1;
    }
    
    trace = fopen(argv[5],"r");
    if(trace == NULL){
        printf("error");
        printf("Trace file is not valid\n");
        return -1;
    }

// argument setup is done
// actually do cache stuff now


    return 1;
}
