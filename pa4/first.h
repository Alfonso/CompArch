// header file for first
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>


//                  Structs

typedef struct _block{
    int valid;
    unsigned long long int tag;

} block;

typedef struct _cache{
    block** blocks;
    int blockSize;
    int numSets;
    int associativity;
    int cacheSize;
    int reads;
    int writes;
    int misses;
    int hits;
    int replacePolicy;
    int prefetch;

} cache;


//              Prototype Functions

// creates a cache with the given parameters
// returns the newly created cache
cache* createCache(int,int,int,int,int);

int writeCache(cache*,unsigned long long int);

int readCache(cache*,unsigned long long int);

int prefetch(cache*,unsigned long long int);

int fifo(cache*,unsigned long long int,unsigned long long int);

int lru(cache*,unsigned long long int,unsigned long long int);

int shiftBlocks(cache*,unsigned long long int,unsigned long long int);

void freeCache(cache*);

//              Utility Functions

// returns whether or not the given num is a power of two
// returns 1 if it is a power of two
// returns 0 if it is not a power of two
int powerOfTwo(int num){
    if( num<=0 )
        return 0;
    return ((num & (num-1))==0);
}

// checks to see the associativity
// returns -3 if error
// returns -1 if it is direct
// returns -2 if it is assoc
// returns n if it is assoc:n
int setAssoc(char* assoc){
    int counter;
    char* buff = (char*)malloc(sizeof(char)*(1+strlen(assoc))); 

    strcpy(buff,assoc);
    
    char* token = strtok(buff,":");
    token = strtok(NULL,":");
    // if token is null, either direct, assoc, or error
    if( token == NULL ){
        if(strcmp(assoc,"direct")==0)
            return -1;
        else if(strcmp(assoc,"assoc")==0)
                return -2;
            else return -3;
    }

    // not null, so return n
    
    for(counter=0;counter<strlen(token);counter++){
        if(!isdigit(token[counter]))
            return -3;
    }

    return atoi(token);
}

// prints out the data in the cache
void printCache(cache* c){
    printf("Memory reads: %d\n",c->reads);
    printf("Memory writes: %d\n",c->writes);
    printf("Cache hits: %d\n",c->hits);
    printf("Cache misses: %d\n",c->misses);
    
    return;

}

