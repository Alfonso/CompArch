#include<stdio.h>
#include<stdlib.h>

char* mystrcpy(char*,char*);

int findLength(char*);

int findVowel(char*);

char* makeVowelFront(char*,int);

void printSentence(char**,int);

int main(int argc,char** argv){
    
    if(argc<2){
        printf("Please enter the correct number of arguments!");
        return 0;
    }

    int counter,size;
    char* temp;
    char* end;
    char** sentence;
    // initialize the array of strings
    sentence = (char**) malloc((argc-1)*sizeof(char*));
    
    for(counter = 1;counter<argc;counter++){
        // set temp equal to the next word
        temp=argv[counter];
        size = findLength(temp);
        // if index of first vowel is 0, starts with vowel
        if(findVowel(temp) == 0){
            end = (char*) malloc((size+4)*sizeof(char));
            end = mystrcpy(end,temp);
            // write over the current null terminator
            end[size] = 'y';
            end[size+1] = 'a';
            end[size+2] = 'y';
            end[size+3] = '\0';
            sentence[counter-1] = end;
        }else if(findVowel(temp) == -1){
                // there are no vowels, so just return same word
                end = (char*) malloc((size+3)*sizeof(char));
                end = mystrcpy(end,temp);
                end[size] = 'a';
                end[size+1] = 'y';
                end[size+2] = '\0';
                sentence[counter-1] = end;
            }else{
                // there is a vowel but just not at the beginning of the word
                end = (char*) malloc((size+3)*sizeof(char));
                end = makeVowelFront(temp,findVowel(temp));
                sentence[counter-1]=end;
            }
        
    }

    // print out the sentence
    printSentence(sentence,argc-1);

    return 0;
}

// prints out the given char**
void printSentence(char** sentence,int wordCount){
    int counter;
    for(counter=0;counter<wordCount;counter++){
        if(counter<(wordCount-1)){
            printf("%s ",sentence[counter]);
        }else{
            printf("%s\n",sentence[counter]);
        }
    }

    return;
}

// given a word with a vowel not at the front, return the word but with all of the consonants
// from the beginning ot the first vowel at the end and add ay to end
char* makeVowelFront(char* word,int vowelIndex){
    char* temp;
    char* ptr;
    temp = (char*) malloc((findLength(word)+3)*sizeof(char));
    ptr = word;
    // this counter will start from 0 to allow us to write from
    // the start of the new word
    int counter2=0;
    // this counter starts from the first vowel index 
    int counter=vowelIndex;
    // copy the first vowel and onwards to the new string
    while( ptr[counter] != '\0' ){
        temp[counter2] = ptr[counter];
        counter++;
        counter2++;
    }

    // tack on the first consonants to the end of the new string
    // set counter to 0
    ptr = word;
    for(counter = 0;counter<vowelIndex;counter++){
        temp[counter2] = ptr[counter];
        counter2++;
    }
    temp[counter2] = 'a';
    temp[counter2+1] = 'y';
    temp[counter2+2] = '\0';

    return temp;
}

// returns the index of the first vowel
// -1 means there is no vowel
int findVowel(char* word){
    int counter = 0;
    char* temp = word;
    while( *temp != '\0' ){
        if(word[counter] == 'a' || word[counter] == 'A' || word[counter] == 'E' || word[counter] == 'e' || word[counter] == 'I' || word[counter] == 'i' || word[counter] == 'O' || word[counter] == 'o' || word[counter] == 'U' || word[counter] == 'u'){
            return counter;
        }
        counter++;
        temp++;
    }
    return -1;
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
