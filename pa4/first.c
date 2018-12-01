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
        //printf("assoc: direct\n");
    }else if(n==-2){
        // assoc
        //printf("assoc: assoc\n");
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


    // go through the file in order read all of the lines
    
    char* pc = (char*)malloc(sizeof(char)*500);
    char operation;
    int address;

    


    while( fscanf(trace,"%s %c %x",pc,&operation,&address) == 3){
        printf("pc: %s, operation: %c, address: %x\n",pc,operation,address);
        
        

    }


    return 1;
}


// cacheSize is the given size of the cache
// blockSize is the given size of each block
// n is the associativity( Where it is dirct, assoc, or assoc:n )
// returns the newly created cache
cache* createCache(int cacheSize,int blockSize,int n){
    cache* c = (cache*)malloc(sizeof(cache));

    c->reads = 0;
    c->writes = 0;
    c->misses = 0;
    c->hits = 0;
    
    c->blockSize = blockSize;
    c->cacheSize = cacheSize;
    
    // check what type of associativity it is
    // if n is -1 it is direct
    // if n is -2 it is fully associative
    // if n is another value then it is assoc:n

    if( n == -1 ){
        // since the cache is direct, calculate the number of sets
        c->numSets = cacheSize / ( blockSize * 1 );
    }else if( n == -2 ){
        // since the cache is fully associative, calculate the number of sets
        c->numSets = 1;
        // change the value of n because there has to be a certain amount of blocks
        n = cacheSize / (blockSize * 1);
    }else{
        // since the cache is assoc:n calculate the number of sets
        c->numSets = cacheSize / ( blockSize * n );
    }

    int counter = 0;
    int counter2 = 0;

    // initialize the sets
    c->blocks = (block**)malloc(sizeof(block*)*c->numSets);
    
    // initilize each block in each set
    for(counter = 0;counter < c->numSets ;counter++){
        c->blocks[counter] = (block*)malloc(sizeof(block)*n);
        for(counter2=0;counter2<n;counter2++){
            // initializing the actual block itself
            c->blocks[counter][counter2].tag = "";
            c->blocks[counter][counter2].valid = 0;
            c->blocks[counter][counter2].offset = 0;
        }
    }

    // do I need to initialize the blocks and their parts themselves???
        

    return c;
}

void readCache(cache* c,char* memory){

    return;
}

void writeCache(cache* c,char* memory){
    
    
    return;
}
