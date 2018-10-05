#include<stdio.h>
#include<stdlib.h>

int repeatNum(int**,int);

int equalSums(int**,int);

int main(int argc,char** argv){    

    if(argc != 2){
        printf("Please input the correct number of arguments\n");
        return 0;
    }

    FILE* fp;
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("error\n");
        return 0;
    }
    
    int** matrix;
   // int sum=0;
    int size,counter,counter2;
    fscanf(fp,"%d",&size);
  
    // declaring the size of the matrix
    matrix = (int**) malloc(size*sizeof(int*));
    // declaring each pointer inside the array of the matrix
    for(counter = 0;counter<size;counter++){
        matrix[counter] = (int*) malloc(size*sizeof(int));
    }
    // fill in the matrix with the given values
    for(counter = 0;counter<size;counter++){
        for(counter2 = 0;counter2<size;counter2++){
            fscanf(fp,"%d",&(matrix[counter][counter2]));
        }
    }

    // check if that each number is different from each other

    if(repeatNum(matrix,size) == 0){
        printf("not-magic\n");
        return 0;
    }
  
    if( equalSums(matrix,size) == 0){
        printf("not-magic\n");
        return 0;
    }

    printf("magic\n");
    fclose(fp);
    return 0;
}

// return 0 if repeating num. Return 1 if no repeating nums
int repeatNum(int** matrix,int size){
    // square size to get length of array
    int length = size*size;
    int* array = (int*) malloc(length*sizeof(int));
    int x,y;
    int counter = 0;
    // put info from matrix into the array
    for(x = 0;x<size;x++){
        for(y = 0;y<size;y++){
            array[counter] = matrix[x][y];
            counter++;
        }
    }
    // run through array checking if values are equal
    for(x = 0;x<length-1;x++){
        for(y = x+1;y<length;y++){
            if( array[x] == array[y] ){
                return 0;
            }
        }
    }
    return 1;
}

// return 0 if they do not match
int equalSums(int** matrix,int n){
    int sumNums = 2*(n+1);
    int x,y;
    int counter=0;
    // there will be 2(n+1) rows + cols + diagonals where n is the # of rows
    int* array = (int*) malloc(sumNums*sizeof(int));
    // initialize the array
    for(x=0;x<sumNums;x++)
        array[x] = 0;
    // set the values of the rows being added
    for(x=0;x<n;x++){
        for(y=0;y<n;y++){
            array[x] += matrix[x][y];
        }
        counter++;
    }

    // set the values of the cols being added
    for(x=0;x<n;x++){
        for(y=0;y<n;y++){
            array[counter] += matrix[y][x];
        }
        counter++;
    } 
    
    // set the values of the main diagonal
    
    for(x=0;x<n;x++){
        array[counter] += matrix[x][x];
    }
    counter++;

    // set the values of the off diagonal
    for(x=0;x<n;x++){
        array[counter]+= matrix[x][n-1-x];
    }
    counter++;    

    for(x = 0;x<sumNums-1;x++){
        for(y = x+1;y<sumNums;y++){
            if( array[x] != array[y] ){
                return 0;
            }
        }
    }

    return 1;
}
