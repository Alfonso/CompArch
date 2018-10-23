#include<stdio.h>
#include<stdlib.h>

//Global variables are stored in 1 of the 3 locations of memory
int b;

void swap(int, int); //function prototype

void fixedSwap(int*, int*); //function prototype for new function

void swap(int a, int b){ //This swap is not able to swap the values of two variables because it creates a new stack
                         // when a new function is run. The values that were passed to the function were copied
                         //and then the new variables are swapped and then when done, the stack closes
                         //thats why the original variables passed to the function are not swapped
                         //instead we must create another function that takes in pointers instead of values

  //  printf("a = %d, b = %d\n",a,b);
    int temp = a;
    a = b;
    b = temp;
  //  printf("a after = %d, b after = %d\n",a,b);    

}

void fixedSwap(int* a, int* b){ //This function takes in the pointer to the integers instead of the values itself
                                
    int temp = *a; //store the value at memory address a into temp
    *a = *b; //change the value stored at memory address a into what is stored at memory address b
    *b = temp; //change the value stored at memory address b into what is stored in temp

}

int main(int argc, char** argv){

    int p, q;
    printf("Enter the value of p\n");
    scanf("%d", &p); //takes in something from the input terminal. It then goes to the memory address
                     //and makes it equal to the input
    printf("Enter the value of q\n");
    scanf("%d",&q);
    printf("[Before swap] p = %d, q = %d\n",p,q);
    fixedSwap(&p,&q);
    printf("[After swap] p = %d, q = %d\n",p,q);    
    
    return 0;

/*
    int p=7, q = 42;
    printf("[before swap] p = %d, q = %d\n",p,q);
    //swap(p,q); see why we must use the next function
    fixedSwap(&p, &q);
    printf("[after swap] p = %d, q = %d\n",p,q);
    return 0;
*/
	
/*
	int a=42;
	//local variables are stored in a stack
	//The stack stays along as long as the function is being called / going on
	
    int* q;	//q is a pointer that points to nothing
    

    q = &a; //the "&" operator returns the address of the memory of the variable after it.
            // Therefore, we set the pointer "q" equal to the location of "a"

    *q = 54;
    //typing this is equivalent to typing a = 54;
    //because you are changing the data found at the memory address of q
    
    printf("a is: %d\n",a);
    printf("Value at the location pointed by q is: %d\n",*q); //if you do the "*" operator followed by a pointer
                                                              //you get what is stored in that memory address
   
    int c = *q;

    printf("Value at the location pointed by q and stored by c is: %d\n",c);
   
    return 0;
*/
}
