#include<stdio.h>
#include<stdlib.h>

void swap(int*,int*);

void bSort(int*,int);

void evenOdd(int*,int);

int main(int argc, char ** argv){
    
    // have to check that we are getting the correct number of arguments
    if( argc != 2 ){
    
        printf("Please enter the correct number of arguments!\n");
        return 0;

    }

    FILE* fp;
    int num = 0;
    int* points;

    fp = fopen(argv[1],"r");
    if(fp == NULL){

        printf("Please input a proper file name!\n");
        return 0;

    }

    fscanf(fp, "%d",&num);
    //printf("Number of elements: %d\n",num);
    points = (int*) malloc(num*sizeof(int));
    int counter;

    for(counter=0; counter < num; counter++){

        fscanf(fp,"%d",&points[counter]);
        //printf("Element %d is: %d\n",counter,points[counter]);
   
    }
    
    bSort(points,num);
    evenOdd(points,num);
 
    for(counter = 0; counter < num; counter++){

        printf("%d\t",points[counter]);

    }
    printf("\n");
    free(points);
    fclose(fp);
    return 0;
}

void swap(int* a, int* b){

    int temp = *a;
    *a = *b;
    *b = temp;
    return;

}

void bSort(int* list,int n){

    int x,y;
    for(x = 0;x < n-1;x++){

        for(y = 0; y < n-x-1;y++){

            if( list[y] > list[y+1] ){

                swap(&list[y],&list[y+1]);

            }

        }

    }

    return;

}

void evenOdd(int* list,int n){
   
    // Have two arrays, one with the odds and even lists
    int* eTemp;
    int* oTemp;
    
    // Checking how many even numbers there are
    int even = 0; // How many even numbers there are
    int counter; // Counter used for for loops
    int eCounter = 0; // Counter used for evens
    int oCounter = 0; // Counter used for odds
    for(counter = 0;counter<n;counter++){

        if(list[counter] % 2 == 0)
            even = even +1;

    }

    eTemp = (int*) malloc(even*sizeof(int));
    oTemp = (int*) malloc((n-even)*sizeof(int));
    
    for(counter = 0;counter<n;counter++){

        if(list[counter] % 2 == 0){
            
            eTemp[eCounter] = list[counter];
            eCounter = eCounter + 1;            

        }else{

            oTemp[oCounter] = list[counter];
            oCounter = oCounter + 1;

        }

    }
    
    eCounter = 0;
    oCounter = 0;

    for(counter = 0;counter<n;counter++){

        if(even>0){
            list[counter] = eTemp[eCounter];
            even = even - 1;
            eCounter = eCounter + 1;
        }else{
            list[counter] = oTemp[oCounter];
            oCounter = oCounter + 1;
        }

    }

    free(eTemp);
    free(oTemp);
    return;
}


