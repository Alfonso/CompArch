#include<stdio.h>
#include<stdlib.h>

// this is the node that we will be using to make a 
// linked list
typedef struct _listNode{

    int data;
    struct _listNode* next;

} listNode;

void insertNode(listNode**,int,int);

void deleteNode(listNode**,int,int*);

void cleanList(listNode*);

void traverse(listNode*);

int main(int argc, char** argv){

    if(argc !=2){
        printf("Please input the correct number of arguments\n");
        return 0;
    }

    FILE* fp;
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("error");
        return 0;
    }
    
    listNode* head;
    head = (listNode*) malloc(1*sizeof(listNode));;
    
    // char that dictates if it inputs or deletes   
    char request;
    // int that is the the value in the file
    int iValue;
    int firstTime = 0;    

    // have to read the values from the file
    while( fscanf(fp,"%c %d",&request,&iValue ) != EOF){
        //printf("%c: %d\n",request,iValue);
        if(request == 'i'){
            if(firstTime == 0){
                firstTime = 1;
                insertNode(&head,iValue,0);
            }else{
                insertNode(&head,iValue,1);
            }
        }else if(request == 'd'){
            if(firstTime == 0){
                // There are no nodes inside the list
                // so dont really do anything
                head = NULL;
            }else if(firstTime == 1){
                // There is atleast 1 node in the list
                 deleteNode(&head,iValue,&firstTime);
            }
        }
    }
    if(feof(fp)){
        // hit the end of the file
       // printf("Hit end of the file\n");
       // check if its still first time
       if(firstTime == 0)
            head = NULL;
    }else{
        // something else happened. Didnt reach end of file
    }
    
    // traverse the list and print out the # of nodes
    // as well as the nodes themselves
    traverse(head);

    // have to write the method to free all of the
    // nodes inside the linked list
    cleanList(head);
    fclose(fp);
    return 0;
}

void cleanList(listNode* list){
    
    listNode* t1 = list;
    listNode* t2 = NULL;
    while( t1 != NULL){
        t2 = t1;
        t1 = t1 -> next;
        free(t2);
    }
    return;
}

void insertNode(listNode** front,int value,int firstTime){
    listNode* temp = (listNode*) malloc(1*sizeof(listNode));
    // Inserting the first node. make it the head
    if( firstTime == 0){
        temp-> next = NULL;
        temp->data = value;
        *front = temp;
        return;
    }
    // check if there only exists 1 node in the list
    // if so, check if the values are >,<, or =
    if((*front)->next == NULL){
        if((*front)->data == value){
            // trying to insert the same value
            return;
        }else if((*front)->data > value){
                // the current front is greater than
                // the value, so add the new value
                // to the front
                temp->next = *front;
                temp->data = value;
                *front = temp;
                return;
            }else if((*front)->data < value){
                    // the current front is less than
                    // the value, so add the new value
                    // to the point after
                    temp->next = NULL;
                    temp->data = value;
                    (*front)->next = temp;
                    return;
                }
    }    

    // There already exists more than 1 node in the list
    // check if if its less than, greater than, or equal
    // to the already existing node
    listNode* ptr = *front;
    listNode* prev = NULL;
    while(ptr != NULL){
        if((ptr->data) == value ){
            // We are trying to insert data that already
            // exists in the list, dont add it
            return;
        }else if((ptr->data) > value){
                // The current data is greater than the
                // one trying to be added, make it the
                // node before this one
                temp->next = ptr;
                temp->data = value;
                // if it is the first node make front
                // equal to it
                if(ptr == *front){
                    *front = temp;
                }else prev->next = temp;
                return;
            }else if(((ptr->data) < value) && ((ptr->next) == NULL)){
                    // current data is less than the one
                    // we are trying to add, so check
                    // if this is the last node, if so
                    // make the new value the last node
                    temp->next = NULL;
                    temp->data = value;
                    ptr->next = temp;
                    return;
                }
        // move the two pointers forward
        prev = ptr;
        ptr = ptr->next;
    }
    return;
}

void deleteNode(listNode** front, int value,int* firstTime){
    
    // Only the head exists
    if((*front)->next == NULL){
        if((*front)->data == value){
            *front = NULL;
            *firstTime = 0;
            // treat it like the first node does not exist
        }
        return;
    }

    // two or more exists
    listNode* ptr = *front;
    listNode* prev = NULL;
    while(ptr != NULL){
        // check if the current pointer data matches
        // the value trying to be deleted
        if(ptr->data == value){
            // the first node is the one being deleted
            if(ptr == *front){
                *front = ptr->next;
                free(ptr);
                return;
            }
            // delete the node by make the previous node
            // point to the node after the pointer
            prev->next = ptr->next;
            free(ptr);
            return;
        }
        // move the pointers forward
        prev = ptr;
        ptr = ptr->next;
    }
    return;
}

void traverse(listNode* head){
    int counter = 0;
    listNode* ptr = head;
    while(ptr != NULL){
        counter+=1;
        ptr = ptr->next;
    }
    printf("%d\n",counter);
    ptr = head;
    while(ptr != NULL){
        if(ptr->next != NULL)
            printf("%d\t",ptr->data);
        else printf("%d",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
    return;
}
