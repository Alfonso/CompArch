#include<stdio.h>
#include<stdlib.h>

char* mystrcpy(char* dest,char* src){
    
    char* temp=dest;
    while(*src != '\0'){
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return temp;
}

int main(int argc,char** argv){

    int len;
    char c;
    char* ptr;

    printf("Enter the number of characters\n");
    scanf("%d\n",&len);
    
    // we also have to consider the null terminator in the length
    ptr = (char*) malloc(sizeof(char)*(len+1));

    for(int i =0;i<len;i++){
        scanf("%c",&c);
        ptr[i] = c;
    }    

    ptr[len] = '\0';
    printf("entered string is %s\n",ptr);
    
    char* mynew_string = (char*) malloc(100*sizeof(char));
    //my

    return 0;
}
