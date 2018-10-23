#include<stdio.h>
#include<stdlib.h>

int main(int argc,char** argv){

    // stuff tha tcan be used for the matrix multiplication part of the project
    int size1,size2;
    printf("Enter size1 and size2:  ");
    scanf("%d",&size1);
    printf("\n");
    
    int** matrix;
    matrix = (int**) malloc(size1*sizeof(int*));

    for(int x = 0;x<size1;x++){
        matrix[x] = (int*) malloc(size2*sizeof(int));
    }    
    
    for(int x = 0;x<size1;x++){
        for(int y = 0;y<size2;y++){
            matrix[x][y] = 0;
        }
    }    
    
    for(int x = 0;x<size1;x++){
        free(matrix[x]);
    }

    free(matrix);
    return 0;
}
