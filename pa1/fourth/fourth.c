#include<stdio.h>
#include<stdlib.h>

void cleanMatrix(int**);

void printMatrix(int**,int,int);

int matrixMultiply(int*,int**,int,int);

int main(int argc,char** argv){
    if(argc != 2){
        printf("Please input the correct number of arguments!\n");
        return 0;
    }

    FILE* fp;
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("error");
        return 0;
    }

    int numRow1,numCol1;
    int numRow2,numCol2;
    int numRowR,numColR;
    int** matrix1;
    int** matrix2;
    int** resultMatrix;
    int counter,counter2,temp;

    // both matrices will start of by being declared with the
    // number of rows that is in the file   
    
    // finding out the dimensions of the first matrix
    fscanf(fp,"%d %d",&numRow1,&numCol1);

    // declaring the size of the first matrix
    matrix1 = (int**) malloc(numRow1*sizeof(int*));
    // declaring each pointer inside the array    
    for(counter = 0;counter<numRow1;counter++){
        matrix1[counter] = (int*) malloc(numCol1*sizeof(int));
    }
    // filling in matrix 1 with the given value
    for(counter = 0;counter<numRow1;counter++){
        for(counter2 = 0;counter2<numCol1;counter2++){
            fscanf(fp,"%d",&temp);
            // printf("Temp: %d\n",temp);
            matrix1[counter][counter2] = temp;
        }
    }

    // finding out the dimensions of the second matrix
    fscanf(fp,"%d %d",&numRow2,&numCol2);

    // delcaring the size of the second matrix
    matrix2 = (int**) malloc(numRow2*sizeof(int*));
    // declaring each pointer inside the array
    for(counter = 0;counter<numRow2;counter++){
        matrix2[counter] = (int*) malloc(numCol2*sizeof(int));
    }
    // filling in matrix 2 with the given values
    for(counter = 0;counter<numRow2;counter++){
        for(counter2 = 0;counter2<numCol2;counter2++){
            fscanf(fp,"%d",&temp);
            // printf("Temp: %d\n",temp);
            matrix2[counter][counter2] = temp;
        }
    }
    // check to see if we can even do matrix multiplication
    if(numCol1 != numRow2){
        printf("bad-matrices\n");
        return 0;
    }
    
    // set the dimensions of the result matrix
    numRowR = numRow1;
    numColR = numCol2;
    // initialize the matrix
    resultMatrix = (int**) malloc(numRowR*sizeof(int*));
    // Initialize each row in the matrix
    for(counter = 0;counter<numRowR;counter++){
        resultMatrix[counter] = (int*) malloc(numColR*sizeof(int));
    }

    // fill in the values 
    for(counter = 0;counter<numRowR;counter++){
        for(counter2 = 0;counter2<numColR;counter2++){
            resultMatrix[counter][counter2] = matrixMultiply(matrix1[counter],matrix2,numCol1,counter2);
        }
    }
    //iprintMatrix(matrix1,numRow1,numCol1);
    //printMatrix(matrix2,numRow2,numCol2);    
    printMatrix(resultMatrix,numRowR,numColR);


    fclose(fp);
    return 0;
}

void cleanMatrix(int** matrix){

    return;
}

void printMatrix(int** matrix,int row,int col){
    int x,y;
    for(x = 0;x<row;x++){
        for(y=0;y<col;y++){
            if(y != col-1)
                printf("%d\t",matrix[x][y]);
            else printf("%d",matrix[x][y]);
        }
        printf("\n");
    }
    return;
}

int matrixMultiply(int* row,int** col,int size,int colNum){
    int counter;
    int total=0;
    for(counter = 0;counter<size;counter++){
        total += row[counter] * col[counter][colNum];
    }
    return total;
}

