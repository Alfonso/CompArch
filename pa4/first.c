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
    unsigned long long int address;

    // 0 represents FIFO
    cache* c = createCache(cacheSize,blockSize,n,0);

    while( fscanf(trace,"%s %c %llx",pc,&operation,&address) == 3){
        //printf("pc: %s, operation: %c, address: %llx\n",pc,operation,address);
        if( operation == 'R' ){
            readCache(c,address);
        }
        

    }

    
    printCache(c);

    return 1;
}


// cacheSize is the given size of the cache
// blockSize is the given size of each block
// n is the associativity( Where it is dirct, assoc, or assoc:n )
// returns the newly created cache
cache* createCache(int cacheSize,int blockSize,int n,int replace){
    cache* c = (cache*)malloc(sizeof(cache));

    c->reads = 0;
    c->writes = 0;
    c->misses = 0;
    c->hits = 0;
    c->replacePolicy = replace;
    
    c->blockSize = blockSize;
    c->cacheSize = cacheSize;
    
    // check what type of associativity it is
    // if n is -1 it is direct
    // if n is -2 it is fully associative
    // if n is another value then it is assoc:n

    if( n == -1 ){
        // since the cache is direct, calculate the number of sets
        c->numSets = cacheSize / ( blockSize * 1 );
        c->associativity = 1;
    }else if( n == -2 ){
        // since the cache is fully associative, calculate the number of sets
        c->numSets = 1;
        // change the value of n because there has to be a certain amount of blocks
        n = cacheSize / (blockSize * 1);
        c->associativity = n;
    }else{
        // since the cache is assoc:n calculate the number of sets
        c->numSets = cacheSize / ( blockSize * n );
        c->associativity = n;
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
            c->blocks[counter][counter2].tag = 0;
            c->blocks[counter][counter2].valid = 0;
            c->blocks[counter][counter2].offset = 0;
        }
    }

    // do I need to initialize the blocks and their parts themselves???
        

    return c;
}

int readCache(cache* c,unsigned long long int memory){
    // we have to access the memory depending on what
    // type of cache it is (direct, assoc, assoc:n)

    return 1;
}

int writeCache(cache* c,unsigned long long int memory){
    // calculate the number of bits needed for the block offset
    unsigned int blockOffset = log(c->blockSize) / log(2);
    unsigned int setIndex = log(c->numSets) / log(2);
    unsigned int index = (memory >> blockOffset) % (0x1 << setIndex);
    unsigned long long int offset = memory % (0x1 << blockOffset);
    unsigned long long int tag = memory >> (blockOffset+setIndex);
    
    int counter=0;

    // go to index in the blocks 2d array and then traverse through all of the blocks in that set and see if there is an open block
    // if so, just write to it
    // if not, then find FIFO

    int wrote = 0;

    // check to see if the tag already exists in the cache
    for(counter = 0;counter<c->associativity;counter++){
        if(c->blocks[index][counter].tag == tag){
            // break?
            wrote = 1;
            // do I increment???
            c->writes++;
            c->hits++;
            break;
        }
    }

    // check to see if there is an open spot if it didnt hit
    if(wrote == 0){
        for(counter=0;counter<c->associativity;counter++){
            if(c->blocks[index][counter].valid == 0){
                c->blocks[index][counter].valid = 1;
                c->blocks[index][counter].tag = tag;
                c->blocks[index][counter].offset = offset;
                wrote = 1;
                // do i increment???
                c->reads++;
                c->writes++;
                c->misses++;
                break;
            }
        }
    }

    // check to see if it put it in because there was an open block
    // if there was not an open block then we have to do FIFO or LRU

    if(wrote == 0 ){
        // do FIFO or LRU here
        
        if( c->replacePolicy == 0 ){
            // FIFO
            // shifting over the values in the array two the right
            for(counter=c->associativity;counter>0;counter++){
                c->blocks[index][counter].tag = c->blocks[index][counter-1].tag;
                c->blocks[index][counter].offset = c->blocks[index][counter-1].offset;
            }

            // add new block line to the beginning of the array
            c->blocks[index][0].tag = tag;
            c->blocks[index][0].offset = offset;
            c->reads++;
            c->writes++;
            c->misses++;    
        }else if (c->replacePolicy == 1){
            // LRU

        }

    }

    

    return 1;
}
