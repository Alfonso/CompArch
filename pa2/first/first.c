#include<stdio.h>
#include<stdlib.h>

double** computeInverse(double**, int, int);

double** makeIdentity(int,int,int);

double** computeTranspose(double**,int,int);

double** multiplyMatrix(double**,double**,int,int,int,int);

void printMatrix(double**,int,int);

double multiplyRowCol(double*,double**,int,int);

int main(int argc,char** argv){
    double** matrix = makeIdentity(3,3,9);
    printMatrix(matrix,3,3);
    double** matrix2 = makeIdentity(3,3,2);
    printMatrix(matrix2,3,3);
    printf("\n");
    printMatrix(multiplyMatrix(matrix,matrix2,3,3,3,3),3,3);
    printf("\n");
    

    return 0;
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
    double** augMatrix = (double**)malloc(rowCount*sizeof(double));
    int x,y;

    // intialize the rows and make each the length of the original column count + amount of rows
    for(x=0;x<rowCount;x++)
        augMatrix[x] = (double*)malloc((rowCount+colCount)*sizeof(double));

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
    
    // do the actual row operations
    
    iMatrix = matrix;

    return iMatrix;
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
    int total = 0;
    for(counter = 0;counter<size;counter++){
        total += row[counter] * col[counter][colNum];
    }

    return total;
}
