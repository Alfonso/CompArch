#include<stdio.h>
#include<stdlib.h>

double** computeInverse(double**, int, int);

double** makeIdentity(int,int,int);

double** computeTranspose(double**,int,int);

double** multiplyMatrix(double**,double**,int,int,int,int);

void printMatrix(double**,int,int);

double multiplyRowCol(double*,double**,int,int);

void printVector(double*,int);

double* computeWeights(double**,double*,int,int);

double** changePivot(double**,int,int,int,int);

int findPivot(double*,int);

void freeMatrix(double**,int);

int main(int argc,char** argv){
    
    // check the argument values and check if there is the correct amount
    if(argc < 3 ){
        printf("error\n");
        return 0;
    }

    FILE* fp;
    fp = fopen(argv[1],"r");
    // open the file and check if it is the correct file
    if(fp == NULL){
        printf("error\n");
        return 0;
    }

    // read the file and store the appropriate values
    // the first line is the number of attributes
    int numCols;
    fscanf(fp,"%d",&numCols);
    numCols++; // have to account for the col of 1's
    int numRows;
    fscanf(fp,"%d",&numRows);
    int counter = 0;    
    int counter2 = 0;
    // make the price matrix
    double* y = (double*)malloc(numRows*sizeof(double));
    // make the matrix that stores the data
    double** x = (double**)malloc(numRows*sizeof(double*)); 
    // malloc each row
    for(counter = 0;counter<numRows;counter++){
        x[counter] = (double*)malloc(numCols*sizeof(double));
    }
    // increase the number of cols by 1 because of the col of 1s
    // the last col (the prices) is not included in this count
    for(counter=0;counter<numRows;counter++){
        for(counter2=0;counter2<(numCols+1);counter2++){
            // if col is first col, put a one in it
            if(counter2 == 0){
                x[counter][counter2] = 1;
            }else if(counter2 < numCols){
                fscanf(fp,"%lf,",&x[counter][counter2]);
            }else if(counter2 == numCols){
                // we are at the last col so put these values
                // into the price matrix
                fscanf(fp,"%lf",&y[counter]);
            }
        }
    }

    // i have the vector y (the prices) as well as
    // the matrix x which contains all of the values of the
    // attributes. we will now use the equation 
    // W = (X^T * X)^-1 * (X^T) *Y
    // where W is the matrix that contains the values of the weights

    double* w = (double*)malloc(numCols*sizeof(double));
    
    w = computeWeights(x,y,numRows,numCols);
    
    // use the calculated weights to find the predicted values
    // we subtract 1 because the 1 was to account for the columns of 1
    int attributeCount = numCols - 1;
    int numTRows;

    FILE* fpTest;
    fpTest = fopen(argv[2],"r");
    if(fpTest == NULL){
        printf("error");
        return 0;
    }
    
    // read in the test data
    fscanf(fpTest,"%d\n",&numTRows);
    printf("Num T Rows: %d\n",numTRows);
    
    double** test = (double**)malloc(sizeof(double*)*numTRows);
    for(counter=0;counter<numTRows;counter++){
        test[counter] = (double*)malloc(sizeof(double)*attributeCount);
    }

    // put all of the test data into a matrix;
    
    // free all of the matrices and data
    
    fclose(fpTest);
    fclose(fp);
    return 0;
}

double* multiplyVector(double** matrix,double* vector,int rowCount1,int rowCount2,int colCount){
    double* result = (double*)malloc(rowCount1*sizeof(double));
    int counter = 0;
    int counter2 = 0;    
    double total = 0;
    
    for(counter=0;counter<rowCount1;counter++){
        for(counter2=0;counter2<colCount;counter2++){
            total+= matrix[counter][counter2]*vector[counter2];        
        }
        result[counter] = total;
    }


    return result;
}

double* computeWeights(double** x,double* y, int rowCount,int colCount){
    // W = (X^T * X)^-1 * (X^T) *Y
    // where W is the matrix that contains the values of the weights

    int counter;

    // result is going to store the values of the weights
    double* result = (double*)malloc(colCount*sizeof(double));
    
    double** m1 = (double**)malloc(colCount*sizeof(double*));
    double** m2 = (double**)malloc(colCount*sizeof(double*));
    double** xT = (double**)malloc(colCount*sizeof(double*));
    double** m0 = (double**)malloc(colCount*sizeof(double*));
    for(counter=0;counter<colCount;counter++){
        xT[counter] = (double*)malloc(rowCount*sizeof(double));
        m1[counter] = (double*)malloc(colCount*sizeof(double));
        m2[counter] = (double*)malloc(rowCount*sizeof(double));
        m0[counter] = (double*)malloc(colCount*sizeof(double));
    }    


    xT = computeTranspose(x,rowCount,colCount);
    
    m0 = multiplyMatrix(xT,x,colCount,rowCount,rowCount,colCount);   
 
    m1 = computeInverse( m0,colCount,colCount );
    
    
    m2 = multiplyMatrix(m1,xT,colCount,colCount,colCount,rowCount);
    

    result = multiplyVector(m2,y,colCount,rowCount,rowCount  );
    
    printf("x: \n");
    printMatrix(x,rowCount,colCount);
    printf("y: \n");
    printVector(y,colCount);
    printf("xT: \n");
    printMatrix(xT,colCount,rowCount);
    printf("m0: \n");
    printMatrix(m0,colCount,colCount);
    printf("m1: \n");
    printMatrix(m1,colCount,colCount);
    printf("m2: \n");
    printMatrix(m2,colCount,rowCount);
    printf("result: \n");
    printVector(result,colCount);

    // free all of the matrices that we do not need anymore
    freeMatrix(m1,colCount);
    freeMatrix(m2,colCount);
    freeMatrix(xT,colCount);
    freeMatrix(m0,colCount);

    return result;

}

void freeMatrix(double** matrix,int rowCount){
    int counter;
    for(counter=0;counter<rowCount;counter++){
        free(matrix[counter]);
    }

    free(matrix);
    return;
}

double** computeTranspose(double** matrix,int rowCount,int numCount){
    double** result = (double**)malloc(numCount*sizeof(double*));
    int newRow = numCount;
    int newCol = rowCount;
    int x,y;
    // initialize the result matrix
    for(x=0;x<newRow;x++){
        result[x] = (double*)malloc(newCol*sizeof(double));
    }

    // transpose the values
    for(x=0;x<newRow;x++){
        for(y=0;y<newCol;y++){
            result[x][y] = matrix[y][x];
        }
    }

    return result;
}

double** multiplyMatrix(double** matrix1, double** matrix2,int rowCount1,int rowCount2,int colCount1,int colCount2){
    double** result = (double**)malloc(rowCount1*sizeof(double*));
    // check if we can even matrix multiply. col1 and row2 should be equal
    if(colCount1 != rowCount2){
        // do something?
    }
    
    int x,y;
    for(x=0;x<rowCount1;x++){
        result[x] = (double*)malloc(colCount2*sizeof(double));
    }

    // set each of the doubles in the result matrix equal to 0 to begin with
    for(x=0;x<rowCount1;x++){
        for(y=0;y<colCount2;y++){
            result[x][y] = 0;
        }
    }

    // actually calculate the matrix multiplication
    for(x=0;x<rowCount1;x++){
        for(y=0;y<colCount2;y++){
            result[x][y] = multiplyRowCol(matrix1[x],matrix2,colCount1,y);
        }
    }

    return result;
}

double** computeInverse(double** matrix,int rowCount,int colCount){
    double** iMatrix = (double**)malloc(rowCount*sizeof(double*));
    double** augMatrix = (double**)malloc(rowCount*sizeof(double*));
    int x,y;
    int newColCount = rowCount+colCount;



    // intialize the rows and make each the length of the original column count + amount of rows
    for(x=0;x<rowCount;x++)
        augMatrix[x] = (double*)malloc((newColCount)*sizeof(double));

    // copy the original data over to the augmented matrix
    for(x=0;x<rowCount;x++){
        for(y=0;y<(colCount);y++){
            augMatrix[x][y] = matrix[x][y];
        }
    }



    // make the last indexes the identity matrix
    for(x=0;x<rowCount;x++){
        for(y=colCount;y<(colCount+rowCount);y++){
            if((y-colCount) == x){
                augMatrix[x][y] = 1;
            }else augMatrix[x][y] = 0;
        }
    }
 
 
    int pivot; 
    // do the actual row operations
    for(x=0;x<rowCount;x++){
        // loop through all of the rows and make sure that they are put into RREF
        pivot = findPivot(augMatrix[x],newColCount);
        augMatrix = changePivot(augMatrix,x,pivot,rowCount,newColCount);
    } 

    
    // initialize iMatrix
    for(x=0;x<rowCount;x++){
        iMatrix[x] = (double*)malloc(rowCount*sizeof(double));
    }

    // set iMatrix equal to just the inverse part of the matrix
    for(x=0;x<rowCount;x++){
        for(y=colCount;y<newColCount;y++){
            iMatrix[x][y-colCount] = augMatrix[x][y];
        }
    }


    return iMatrix;
}

// turn the pivot to a 1 and change the values above and below equal to zeros
double** changePivot(double** matrix,int row,int pivotCol,int rowCount,int colCount){
    int counter,counter2;
    double value;

    // change the pivot to 1 and do the operation on the rest  of the row
    value = matrix[row][pivotCol];
    for(counter=pivotCol;counter<colCount;counter++){
        matrix[row][counter] = matrix[row][counter] / value;
    }

    // change all of the values above the pivot to 0
    for(counter=0;counter<row;counter++){
        value = matrix[counter][pivotCol];
        for(counter2=pivotCol;counter2<colCount;counter2++){
            if( value != 0)
                matrix[counter][counter2] = matrix[counter][counter2] - (value * matrix[row][counter2]);
        }
    }

    // change all of the values below the pivot to 0
    for(counter=row+1;counter<rowCount;counter++){
        value = matrix[counter][pivotCol];
        for(counter2=pivotCol;counter2<colCount;counter2++){
            if( value != 0)
                matrix[counter][counter2] = matrix[counter][counter2] - (value * matrix[row][counter2]);
        }
    }

    return matrix;
}

// returns the pivot col of the given row
int findPivot(double* row,int colCount){
    int counter;
    for(counter=0;counter<colCount;counter++){
        if( row[counter] != 0 )
            return counter;
    }

    // there is no pivot col????
    return -1;
}

void printVector(double* vector,int row){
    int x;
    for(x=0;x<row;x++){
        printf("%lf\n",vector[x]);
    }

    return;
}

void printMatrix(double** matrix,int row,int col){
    int x,y;
    for(x=0;x<row;x++){
        for(y=0;y<col;y++){
            if(y!=col-1)
                printf("%lf\t",matrix[x][y]);
            else printf("%lf",matrix[x][y]);
        }
        printf("\n");
    }
    return;
}

double** makeIdentity(int rowCount,int colCount,int value){
    double** matrix = (double**)malloc(rowCount*sizeof(double*));;
    
    int x;
    // set up the rows
    for(x=0;x<rowCount;x++){
        matrix[x] = (double*)malloc(colCount*sizeof(double));
    }
    // set up the columns now
    int y;
    for(x=0;x<rowCount;x++){
        for(y=0;y<colCount;y++){
            matrix[x][y] = 0;
        }
    }
    
    for(x=0;x<rowCount;x++)
        matrix[x][x] = value;

    return matrix;
}

double multiplyRowCol(double* row,double** col,int size,int colNum){
    int counter;
    double total = 0;
    for(counter = 0;counter<size;counter++){
        total += row[counter] * col[counter][colNum];
    }

    return total;
}
