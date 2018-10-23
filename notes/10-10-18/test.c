#include<stdio.h>
#include<stdlib.h>

int main(int argc,char** argv){

    int i = 0;,n;
    float sum = 0.0f;
    printf("Enter the loop count\n");
    scanf("%d",&n);
    while(i < n){
        sum+=.01f;
        i++;
    }

    printf("The sum is%f\n",sum);
    
    return 0;
}
