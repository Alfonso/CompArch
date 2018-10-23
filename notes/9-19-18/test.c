#include<stdio.h>
#include<stdlib.h>

typedef struct _listNode{

    int value;
    struct _listNode * next;

} listNode;

void traverse(listNode*);

void cleanup(listNode*);

void traverse(listNode* myList){

    listNode* t1 = myList;

    printf("Traversing: \n");    

    while(t1 != NULL){
   
        printf("%d\n",t1 -> value);
        t1 = t1 -> next;

    }
    return;
}

void cleanup(listNode* myList){

    listNode* t1 = myList;
    listNode* t2 = NULL;
    while(t1 != NULL){

        t2=t1;
        t1 = t1 -> next;
        free(t2);

    }
    return;
}

int main(int argc, char ** argv){
    
   // int* points; // declaring a pointer that points to nothing right now.

   // int points[5]; // we have statically declared an array with 5 intgers
    int num;

    int a;
    //int b,c;    
    
    listNode* head = NULL;

   // printf("Enter three elements\n");
   // scanf("%d %d %d",&a,&b,&c);

    printf("How many elements?\n");
    scanf("%d",&num);
    
    printf("Please enter in the elements\n");    

    for(int x = 0; x < num; x++){
        printf("%d: ",x);
        scanf("%d",&a);
        listNode* temp = (listNode*) malloc(1* sizeof(listNode));
        temp -> value = a; // since temp is a pointer to a structure we use the -> instead of the . operator
        temp -> next = head;
        head = temp;

    }

    traverse(head);
    cleanup(head);    

    return 0;

/*
    points = (int*) malloc(num*sizeof(int)); // makes points equal to the newly casted pointer that is created by malloc
   
    if(points == NULL){ // if you try allocatng too much memory, the system will not and thus malloc will return null

        printf("Not able to allocate memory \n");
        return 0;
   
    }
 
    // int points[num] // CANNOT DO THIS BECAUSE NUM IS A VARIABLE SO IT WILL CRASH. Thats why we need to use pointer
    
    printf("Enter the elements:\n");       
    for(int x = 0;x < num; x++){
        
        printf("%d: ",x);
        scanf("%d",&points[x]);

    }

    free(points);
    return 0;
*/
}

