// header file for first
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

// returns whether or not the given num is a power of two
// returns 1 if it is a power of two
// returns 0 if it is not a power of two
int powerOfTwo(int num){
    if( num<=0 )
        return 0;
    return ((num & (num-1))==0);
}
