// header file for first
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

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
    if(isdigit(token)){
        return atoi(token);
    }
    return -3;
}

