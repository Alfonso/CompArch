#include<stdio.h>
#include<stdlib.h>

typedef struct _node{
    int data;
    int height;
    struct _node* left;
    struct _node* right;
} node;

node* insertNode(node*,int);

node* searchTree(node*,int);

// int to tell if it is either our first time or not
int firstTime;

int main(int argc,char** argv){
    if(argc != 2){
        printf("Please input the correct number of arguments\n");
        return 0;
    }    

    FILE* fp;
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("error");
        return 0;
    }
    // char of what we are doing: inserting or searching
    char request;
    // the int we are performing the action on    
    int iValue;
    // root node
    node* root;
    root = NULL;
    // node
    node* temp;

    firstTime = 1;

    while(fscanf(fp,"%c %d",&request,&iValue) != EOF){
        if(request == 'i'){
            // inserting a node into the tree
            if(firstTime == 1){
                root = insertNode(root,iValue);
                printf("inserted %d\n",root->height);
            }else{
                // search the tree for the value
                temp = searchTree(root,iValue);
                // if it doesnt exist. add it
                if(temp == NULL){
                    insertNode(root,iValue);
                    temp = searchTree(root,iValue);
                    printf("inserted %d\n",temp->height);
                }else{
                    printf("duplicate\n");
                }
            }
        }else if(request == 's'){
                // searching the tree
                temp = searchTree(root,iValue);
                if(temp == NULL)
                    printf("absent\n");
                else{
                    printf("present %d\n",temp->height);
                }
            }
    }
    if(feof(fp)){

    }else{

    }
    
    fclose(fp);
    return 0;
}

node* insertNode(node* root,int value){
    // if the tree is empty, return a new node
    if( root == NULL){
        node* temp = (node*) malloc(1*sizeof(node));
        temp->data = value;
        temp->right = NULL;
        temp->left = NULL;
        if(firstTime == 1){
            firstTime = 0;
            temp->height = 1;
        }
        return temp;
    }

    // else, either go down the left or right subtree
    // if the value being inserted is more than curr value
    // go down right side
    if( value > root->data){
        root->right = insertNode(root->right,value);
        root->right->height = root->height+1;
    }else if(value < root->data){
        root->left = insertNode(root->left,value);
        root->left->height = root->height+1;
    }


    return root;
}

// returns null if not found
// else, returns found node
node* searchTree(node* root,int value){
    
    // recursive base case
    // if its either null or it matches
    if(root == NULL || root->data == value)
        return root;

    // if the value we are searching for is
    // less than the current nodes value
    if( root->data > value)
        return searchTree(root->left,value);

    // if the value we are searching for is
    // greater than the current node's value
    if( root->data < value)
        return searchTree(root->right,value);    

    return NULL; // placeholder so compiler doesnt yell at us
}
