#include<stdio.h>
#include<stdlib.h>
// ASK SANTOSH ABOUT TAB VS SPACE
// ALSO ASK ABOUT REHASHING, BC WHEN REHASHING
// IT WILL REPEAT THE OUTPUT OF INSERTING

typedef struct _node{
    int data;
    struct _node* next;
} node;

float lf = 0; // load factor = nodeCounter / size
int size = 100; // size of the array. Is this a good base?
int nodeCounter = 0; // amount of nodes in the whole hash table

node** hashTable;
// this is the array that is the hash table.
// it holds the pointers to each list

void hash(int,int);
// key is the index of the array
// value is the value stored in the node
// insert value if not already present

void rehash();
// if the load factor is more than .75, double size of array
// and re add everything

void search(int,int);
// find the inputed value, then return if found or not

// hash function = key % number of buckets
// load factor of 0.75
int main(int argc,char** argv){
    // initializing the hashTable
    hashTable = (node**) malloc(10000*sizeof(node*));

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
    
    char request;
    // dictates if we are adding or searching
    
    int iValue;
    // the value that is being added or searched

    while( fscanf(fp,"%c %d",&request,&iValue) != EOF ){
        if(request == 'i'){
            // inserting the value
            hash(abs(iValue % size),iValue);
        }else if(request == 's'){
                // searching for value
                search(abs(iValue % size),iValue);
            }
    }
    if(feof(fp)){
        // reached end of the file
    }else{
        // didnt reach end of the file
        // something happened
    }
    
    fclose(fp);
    return 0;
}

void hash(int key,int value){
    node* temp = (node*) malloc(1*sizeof(node));
    temp->data = value;
    temp->next = NULL;
    // first time running through this key
    // index of the array should have a null pointer
    if( hashTable[key] == NULL){
        hashTable[key] = temp;
        nodeCounter+=1;
        // recalculate the load factor
        lf = nodeCounter / size;
        printf("inserted\n");
        // if lf > 0.75, rehash
        if(lf > 0.75)
            rehash();
        return;
    }
    
    // There is at least one node in the list
    
    node* ptr = hashTable[key];
    // Check if its only one node
    if( ptr->next == NULL){
        // ptr is the only node in the list
        // Check if the value being added is in this node
        if(ptr->data == value){
            printf("duplicate\n");
            return;
        }else{
            // add the node
            ptr->next = temp;
            nodeCounter+=1;
            printf("inserted\n");
            lf = nodeCounter / size;
            if(lf > 0.75)
                rehash();
            return;
        }
    }

    node* prev;
    // There is more than 1 node so
    // loop through them all to check if thee is
    // one that exists already
    while(ptr != NULL){
        if(ptr->data == value){
            printf("duplicate\n");
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    // did not match the new value to any existing
    // therefore, add it to the back of the list
    prev->next = temp;
    nodeCounter+=1;
    printf("inserted\n");
    lf = nodeCounter / size;
    if(lf>0.75)
        rehash();
    return;
}

void rehash(){
    int oldSize = size;
    size = oldSize*2;
    int counter;
    // copy over the old table
    node** oldTable = hashTable;
    // prep for the new table by doubling size
    hashTable = (node**) malloc(size*sizeof(node));
    // get pointer for first element in first index of old table
    node* ptr = oldTable[0]; 
    // run through each list in each index and hash them
    for(counter=0;counter<oldSize;counter++){
        // go until there are no more nodes in this list in this index
        while(ptr != NULL){
            // hash the old node into the new table
            hash(ptr->data % size,ptr->data);
            // go to the next node
            ptr = ptr->next;
        }
        // move to next index
        ptr = oldTable[counter];
    } 
    return;
}

void search(int key,int value){
    node* ptr = hashTable[key];
    if(ptr == NULL){
        // There are no nodes in this list
        printf("absent\n");
        return;
    }

    // There is at least 1 node in the list
    while(ptr != NULL){
        if(ptr->data == value){
            printf("present\n");
            return;
        }
        ptr = ptr->next;
    }
    printf("absent\n");
    return;
}
