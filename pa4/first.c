#include"first.h"

/*
 * if its a miss and the op was read, increment cache miss and read count
 * if its a miss and the op was write, you increment cachemiss, readcount, and writecount
 * if its a hit and the op was read, increment cachehit goes up
 * if its a hit and the op was a write, increment cachehit and writecount
 * pre-fetch data:
 * if its a hit, incrememnt nothing
 * if its a miss, increment read
*/



int main(int argc,char** argv){

    int cacheSize;
    int n;
    char* policy;
    int policyNum=0;
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
    if(strcmp(policy,"fifo") == 0){
        policyNum = 0;
    }else if(strcmp(policy,"lru")==0){
        policyNum = 1;
    }else{
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

    // 0 represents no prefetch
    cache* c = createCache(cacheSize,blockSize,n,policyNum,0);
    cache* prec = createCache(cacheSize,blockSize,n,policyNum,1);
    
    while( fscanf(trace,"%s %c %llx",pc,&operation,&address) == 3){
        //printf("pc: %s, operation: %c, address: %llx\n",pc,operation,address);
        
        if( operation == 'R' ){
            readCache(c,address);
            readCache(prec,address);
        }else if( operation == 'W' ){
            writeCache(c,address);
            writeCache(prec,address);
        }
        

    }

    printf("no-prefetch\n");
    printCache(c);
    printf("with-prefetch\n");
    printCache(prec);    

    return 1;
}


// cacheSize is the given size of the cache
// blockSize is the given size of each block
// n is the associativity( Where it is dirct, assoc, or assoc:n )
// replace is the replacement policy. FIFO is 0 and LRU is 1
// pre is if it uses pre-fetching or not 0 is no 1 is yes
// returns the newly created cache
cache* createCache(int cacheSize,int blockSize,int n,int replace,int pre){
    cache* c = (cache*)malloc(sizeof(cache));

    c->reads = 0;
    c->writes = 0;
    c->misses = 0;
    c->hits = 0;
    c->replacePolicy = replace;
    c->prefetch = pre;   
 
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
        n=1;
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
        }
    }

        
    return c;
}

// do pre-fetching here
// the memory parameter is the new memory address
// old address + blockSize 
int prefetch(cache* c, unsigned long long int memory){

    int wrote = 0;
    int counter= 0;
    unsigned long long int blockOffset = log(c->blockSize) / log(2);
    unsigned long long int setIndex = log(c->numSets) / log(2);
    unsigned long long int index = (memory >> blockOffset) % (0x1 << setIndex);
    unsigned long long int tag = memory >> (blockOffset + setIndex);
    if(c->numSets == 1)
        index = 0;

    // check to see if the tag already exists in the cache
    for(counter = 0;counter<c->associativity;counter++){
        if(c->blocks[index][counter].tag == tag){
            // break?
            wrote = 1;
            // do I increment???

/*
// DO I NEED TO DO THIS SHIFT FOR PREFETCH?   
//              APPARENTLY NOT BC I AM OFF IF I DO USE IT         
            // check to see if it is LRU
            // if it is, then you have to move the tag that matched to the beginning of the array and shift everything over
            // call shift function that inputs the hit tag to the 0 index
            if( c->replacePolicy == 1 )
                shiftBlocks(c,tag,index);
*/  
            break;
        }
    }

    // check to see if there is an open spot if it didnt hit
    if(wrote == 0){
        for(counter=c->associativity-1;counter>=0;counter--){
            if(c->blocks[index][counter].valid == 0){
                c->blocks[index][counter].valid = 1;
                c->blocks[index][counter].tag = tag;
                wrote = 1;
                // do i increment???
                c->reads++;
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
            fifo(c,tag,index);
            c->reads++;
        }else if (c->replacePolicy == 1){
            // LRU
            lru(c,tag,index);
            c->reads++;
        }

    }
    

    return 1;
}

int fifo(cache* c,unsigned long long int tag,unsigned long long int index){
    int counter;
    // shifting over the values in the array to the right (get rid of the one all the way at the right)
    for(counter = c->associativity-1;counter>0;counter--)
        c->blocks[index][counter].tag = c->blocks[index][counter-1].tag;
    // add new block line to the beginning of the array
    c->blocks[index][0].tag = tag;
    return 1;
}

int lru(cache* c,unsigned long long int tag,unsigned long long int index){
    int counter;
    
    // shift everything over right one. just like in fifo
    // add the new one to the front
    for(counter = c->associativity-1;counter>0;counter--)
        c->blocks[index][counter].tag = c->blocks[index][counter-1].tag;
    c->blocks[index][0].tag = tag;
    // this is because I am going to try to structure the array of blocks
    // with the ones that have been used more recently being to the beginning of the array
    // and the ones that have been used least recently to the right


    return 1;
}

// shift all the blocks over and then sets the given tag to the 
// 0 index
// have to find the tag where it is in the array
// and then shift everything over to the right up to that point and then put the
// given tag to the beginning
int shiftBlocks(cache* c,unsigned long long int tag,unsigned long long int index){
    int counter;
    int oldIndex=0;

    // find what index in the array the tag is in

    for(counter=0;counter<c->associativity;counter++){
        if( c->blocks[index][counter].tag == tag){
            oldIndex = counter;
        }
    }

    // go from the found index to the beginning shifting
    // everything over one
    for(counter=oldIndex;counter>0;counter--){
        c->blocks[index][counter].tag = c->blocks[index][counter-1].tag;
    }

    c->blocks[index][0].tag = tag;

    return 1;
}

int readCache(cache* c,unsigned long long int memory){
    // calculate the number of bits needed for the block offset
    unsigned long long int blockOffset = log(c->blockSize) / log(2);
    unsigned long long int setIndex = log(c->numSets) / log(2);
    unsigned long long int index = (memory >> blockOffset) % (0x1 << setIndex);
    if( c->numSets == 1 ){
        index = 0;
    }
    unsigned long long int tag = memory >> (blockOffset+setIndex);
/*   
    printf("memory: %llx\n",memory); 
    printf("blockOffset: %u\n",blockOffset);
    printf("setINdex; %lu\n",setIndex);
    printf("memory shifted: %lu\n",memory>>blockOffset);
    printf("index: %lu\n",index);
    printf("tag: %llx\n",tag);
*/
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
            
            // check to see if it is LRU
            // if it is, then you have to move the tag that matched to the beginning of the array and shift everything over
            // call shift function that inputs the hit tag to the 0 index
            if( c->replacePolicy == 1 )
                shiftBlocks(c,tag,index);

            c->hits++;
            break;
        }
    }

    // check to see if there is an open spot if it didnt hit
    if(wrote == 0){
        for(counter=c->associativity-1;counter>=0;counter--){
            if(c->blocks[index][counter].valid == 0){
                c->blocks[index][counter].valid = 1;
                c->blocks[index][counter].tag = tag;
                wrote = 1;
                // do i increment???
                c->reads++;
                c->misses++;

                // check if the cache has pre-fetch on
                if( c->prefetch == 1){
                    prefetch(c,memory+c->blockSize);
                }
        
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
            // shifting over the values in the array to the right
       /*     for(counter=c->associativity-1;counter>0;counter--){
                c->blocks[index][counter].tag = c->blocks[index][counter-1].tag;
            }

            // add new block line to the beginning of the array
            c->blocks[index][0].tag = tag;
        */
            fifo(c,tag,index);
            c->reads++;
            c->misses++;    
            // check if the cache has pre-fetch on
            if( c->prefetch == 1){
                prefetch(c,memory+c->blockSize);
            }
        }else if (c->replacePolicy == 1){
            // LRU
            lru(c,tag,index);
            c->reads++;
            c->misses++;
            if(c->prefetch == 1)
                prefetch(c,memory+c->blockSize);
        }

    }

    return 1;

}

int writeCache(cache* c,unsigned long long int memory){
    // calculate the number of bits needed for the block offset
    unsigned int long blockOffset = log(c->blockSize) / log(2);
    unsigned int long setIndex = log(c->numSets) / log(2);
    unsigned int long index = (memory >> blockOffset) % (0x1 << setIndex);
    if( c->numSets == 1 ){
        index = 0;
    }    

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
            
            // check to see if it is LRU
            // if it is, then you have to move the tag that matched to the beginning of the array and shift everything over
            // call shift function that inputs the hit tag to the 0 index
            if( c->replacePolicy == 1 )
                shiftBlocks(c,tag,index);

            break;
        }
    }

    // check to see if there is an open spot if it didnt hit
    if(wrote == 0){
        for(counter=c->associativity-1;counter>=0;counter--){
            if(c->blocks[index][counter].valid == 0){
                c->blocks[index][counter].valid = 1;
                c->blocks[index][counter].tag = tag;
                wrote = 1;
                // do i increment???
                c->reads++;
                c->writes++;
                c->misses++;
                // check if the cache has pre-fetch on
                if( c->prefetch == 1){
                    prefetch(c,memory+c->blockSize);
                }
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
            fifo(c,tag,index);
            
            c->reads++;
            c->writes++;
            c->misses++;    
            // check if the cache has pre-fetch on
            if( c->prefetch == 1){
               prefetch(c,memory+c->blockSize);
            }
        }else if (c->replacePolicy == 1){
            // LRU
            lru(c,tag,index);
            c->reads++;
            c->writes++;
            c->misses++;
            if( c->prefetch == 1)
                prefetch(c,memory+c->blockSize);
        }

    }

    return 1;
}
