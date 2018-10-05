#include<stdio.h>
#include<stdlib.h>


int findLength(char*);

void printWord(char*,int);

char getLastChar(char*,int);

int main(int argc,char** argv){
    
    if(argc<2){
        printf("Please enter the correct number of arguments!");
        return 0;
    }

    int counter,size;
    char* temp;
    char* sentence;
    // initialize the array of characters
    sentence = (char*) malloc((argc-1)*sizeof(char));
    
    for(counter = 1;counter<argc;counter++){
        // set temp equal to the next word
        temp=argv[counter];
        size = findLength(temp);
        // find the last char and add to the array
        sentence[counter-1] = getLastChar(temp,size);

    }

    // print out the letters
    printWord(sentence,argc-1);

    return 0;
}

// given the word and the length of the word
// (not including the \0, return last char
char getLastChar(char* word,int length){
    return word[length-1];
}

// prints out the given char**
void printWord(char* sentence,int wordCount){
    int counter;
    for(counter=0;counter<wordCount;counter++){
        if(counter<(wordCount-1)){
            printf("%c",sentence[counter]);
        }else{
            printf("%c\n",sentence[counter]);
        }
    }

    return;
}

int findLength(char* word){
    int counter=0;
    char* ptr = word;
    while(*ptr != '\0'){
        counter++;
        ptr++;
    }
    // return length without null character being considered
    return counter;
}
