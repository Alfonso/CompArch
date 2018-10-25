#include<stdio.h>
#include<stdlib.h>

// treat 0 and 1 as false and true respectively

// Need to differentiate this program from program 3 as program 3
// can solve some boards that this program cannot.
// how it will work is go section by section and try to figure out
// which numbers are missing. It will then check if any of them are
// valid in the

// the input board may not be valid so check
// if it is valid, if not, quit
// return 0 if it is not valid
// return 1 if it is valid
int isValid(int**);

// checks the if at the given cell,
// there can be exactly 1 number that fits
int onlyOne(int**,int,int);

// prints the given board
void printBoard(int**);

// give a row and col and figure out what 3x3
// section it is in
// 0 1 2
// 3 4 5
// 6 7 8
int sectionFinder(int,int);

// returns 0 if not in the section
// returns 1 if in the section
int checkSection(int**,int,int);

// returns 0 if not in the col
// returns 1 if it is the col
int checkCol(int**,int,int);

// returns 0 if it is not in the row
// returns 1 if it is in the row
int checkRow(int**,int,int);

// returns 0 if there is not an empty spot
// returns 1 if there is an empty spot
int hasEmpty(int**);

int main(int argc,char** argv){

    if(argc!=2){
        printf("error\n");
        return 0;
    }

    FILE* fp;
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("error");
        return 0;
    }

    // put all of the characters into a 9x9 
    // matrix of chars because of the '-''s

    int counter,counter2;
    char temp=' ';    

    // initialize the first col of arrays
    int** board = (int**)malloc(9*sizeof(int*));
    // initialize each col in each row
    for(counter=0;counter<9;counter++){
        board[counter] = (int*)malloc(9*sizeof(int));
    }

    // get the input from the files and put them into the 9x9 matrix
    for(counter=0;counter<9;counter++){
        for(counter2=0;counter2<9;counter2++){
            fscanf(fp,"%c\t",&temp);
            if(temp != '-'){
                board[counter][counter2] = temp - '0';
            }else board[counter][counter2] = 0;
        }
    }

    // check if the board is vaid before solving it
    if( isValid(board) == 0 ){
        // board is not valid
        printf("no-solution");
        return 0;
    }

    int cellCounter = 0;

    // actually solve the board
    while( hasEmpty(board) == 1 && cellCounter<81 ){
        // loop while there is an empty spot on the board
        for(counter=0;counter<9;counter++){
            for(counter2=0;counter2<9;counter2++){
                // check if the current cell has a value
                // if it does, then set it
                if( board[counter][counter2] == 0 ){
                    if( onlyOne(board,counter,counter2) == 0 ){
                        // more than one value exists so just skip this?
                    }else{
                        board[counter][counter2] = onlyOne(board,counter,counter2);
                    }
                }
            }
        }
        cellCounter++;

    }

    if( hasEmpty(board) == 1){
        // board still has an empty spot
        printf("no-solution");
        return 0;
    }else printBoard(board);

    return 0;
}

// checks if multiple values can exist
// in the provided cell.
// returns 0 if more than one value exists
// returns the number if only 1 exists
int onlyOne(int** board,int row,int col){
    int counter;
    int numOfValid = 0;
    int value=0;
    int section = sectionFinder(row,col);    

    for(counter=1;counter<10;counter++){
        if( (checkRow(board,row,counter) == 0) && (checkCol(board,col,counter) == 0) && (checkSection(board,section,counter) == 0) ){
            numOfValid++;
            value = counter;
            if( numOfValid > 1){
                return 0;
            }
        }
    }    

    return value;
}

// return 0 if not valid
// return 1 if valid
int isValid(int** board){

    int counter,counter2;

    for(counter=0;counter<9;counter++){
        for(counter2=0;counter2<9;counter2++){
            int temp=board[counter][counter2];
            // if there is a number in this spot
            // check if there are repeating values in the row,col or section
            if( temp !=0 ){
                // there exists a value in this spot
                // SO set it equal to 0 so the functions work
                board[counter][counter2] = 0;
                if( (checkCol(board,counter2,temp) == 1) || (checkRow(board,counter,temp)==1) || (checkSection(board,sectionFinder(counter,counter2),temp) == 1) ){
                    // the number matches another one that is in the row, col, or section
                    // the board is not solvable/valid
                    return 0;
                }
                // there does not exist a matching number so set it back
                board[counter][counter2] = temp;
            }
        }
    }

    return 1;
}

// returns 0 if there is no empty spot
// returns 1 if there is an empty spot
// that has the empty location
int hasEmpty(int** board){
    int row,col;
    for(row=0;row<9;row+=1){
        for(col=0;col<9;col+=1){
            if( board[row][col] == 0 ){
                return 1;
            }
        }
    }

    return 0;
}

// returns 0 if it is not in the col
// returns 1 if it is in the col
int checkCol(int** board,int col,int num){
    int counter;
    for(counter=0;counter<9;counter++){
        if(board[counter][col] == num){
            // the current number is in the row already
            return 1;
        }
    }

    return 0;
}

// returns 0 if it is not in the row
// returns 1 if it is in the row
int checkRow(int** board,int row,int num){
    int counter;
    for(counter=0;counter<9;counter++){
        if(board[row][counter] == num){
            // the current number is in the row already
            return 1;
        }
    }

    return 0;
}

// returns 0 if it is not in the section
// returns 1 if it is in the section
int checkSection(int** board,int section,int num){
    int counter,counter2;


    if(section == 0 ){

        for(counter=0;counter<3;counter++){
            for(counter2=0;counter2<3;counter2++){
                if( board[counter][counter2] == num ){
                    return 1; 
                }
            }
        }

    }else if( section == 1 ){
        for(counter=0;counter<3;counter++){
            for(counter2=3;counter2<6;counter2++){
                if( board[counter][counter2] == num ){
                    return 1; 
                }
            }
        }

        }else if( section == 2 ){
                for(counter=0;counter<3;counter++){
                    for(counter2=6;counter2<9;counter2++){
                        if( board[counter][counter2] == num ){
                            return 1;
                        }
                    }
                }
            }else if( section == 3 ){
                    for(counter=3;counter<6;counter++){
                        for(counter2=0;counter2<3;counter2++){
                            if( board[counter][counter2] == num ){
                                return 1;
                            }
                        }
                    }

                }else if( section == 4 ){
                        for(counter=3;counter<6;counter++){
                            for(counter2=3;counter2<6;counter2++){
                                if( board[counter][counter2] == num ){
                                    return 1;
                                }
                            }
                        }
                    }else if( section == 5 ){
                            for(counter=3;counter<6;counter++){
                                for(counter2=6;counter2<9;counter2++){
                                    if( board[counter][counter2] == num ){
                                        return 1;
                                    }
                                }
                            }

                        }else if( section == 6 ){
                                for(counter=6;counter<9;counter++){
                                    for(counter2=0;counter2<3;counter2++){
                                        if( board[counter][counter2] == num ){
                                             return 1;
                                        }
                                    }
                                }

                            }else if( section == 7 ){
                                    for(counter=6;counter<9;counter++){
                                        for(counter2=3;counter2<6;counter2++){
                                            if( board[counter][counter2] == num ){
                                                return 1;
                                            }
                                        }
                                    }

                                }else if( section == 8 ){
                                        for(counter=6;counter<9;counter++){
                                            for(counter2=6;counter2<9;counter2++){
                                                if( board[counter][counter2] == num ){
                                                    return 1;
                                                }
                                            }
                                        }

                                    }
               
    return 0;
}

int sectionFinder(int row,int col){

    // sections:
    // 0 1 2
    // 3 4 5
    // 6 7 8

    if(row<3 && col<3){
        // in the first section
        return 0;
    } else if((col<6 && col>2) && row<3){
            // in the second section
            return 1;
        }else if((col<9 && col>5) && row<3){
                // in the third section
                return 2;
            }else if((col<3) && (row>2 && row<6)){
                    // in the fourth section
                    return 3;
                }else if( (col>2 && col<6) && (row>2 && row<6) ){
                        // in the fifth section
                        return 4;
                    }else if( (col>5 && col<9) && (row>2 && row<6) ){
                            // in the sixth section
                            return 5;
                        }else if( (col<3) && (row>5 && row<9) ){
                                // in the seventh section
                                return 6;
                            }else if( (col>2 && col<6) && (row>5 && row<9) ){
                                    // in the eighth section
                                    return 7;
                                }else if( (col>5 && col<9) && (row>5 && row<9) ){
                                        // in the ninth section
                                        return 8;
                                    }
           
    // there is some wack error
    return -1;
}

void printBoard(int** board){
    int counter,counter2;
    
    for(counter=0;counter<9;counter++){
        for(counter2=0;counter2<9;counter2++){
            if(counter2<8)
                printf("%d\t",board[counter][counter2]);
            else printf("%d",board[counter][counter2]);
        }
        printf("\n");
    }

    return;
}
