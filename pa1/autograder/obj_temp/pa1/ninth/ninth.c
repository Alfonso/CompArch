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

node* deleteNode(node*,int);

node* minNode(node*);

node* updateHeights(node*);

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
        printf("error\n");
        return 0;
    }
    // char of what we are doing: inserting or searching
    char request;
    // the int we are performing the action on    
    int iValue;
    int exist = 0;
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
            }else if(request == 'd'){
                    // searching the tree to delete a node
                    
                    // check if the value was even there
                    // to begin with
                    temp = searchTree(root,iValue);
                    if( temp == NULL ){
                        // the value being searched for
                        // is not in the list
                        exist = 0;
                    }else exist = 1;
                    root = deleteNode(root,iValue);
                    temp = searchTree(root,iValue);
    
                    if( temp == NULL ){
                        if( exist == 0 )
                            printf("fail\n");
                        else printf("success\n");
                    }
                    
                    if(root == NULL)
                        firstTime=1;
                }
    }
    if(feof(fp)){

    }else{

    }
    
    fclose(fp);
    return 0;
}

node* updateHeights(node* root){
    if(root->left != NULL)
        updateHeights(root->left);
    if(root->right != NULL)
        updateHeights(root->right);
    root->height--;
    return root;
}

// There exist three cases for deleting a node
// 1) the node is a leaf
// 2) the node has one child
// 3) the node has two children
// 1 and 2 are fairly simple
// 3, we have to find the smallest node in
// the right subtree and replace the one being
// deleted with that one
node* deleteNode(node* root,int value){
    
    // if root is null, then we are at the end
    // of the tree without deleting anyhting. Return
    if( root == NULL ){
        return NULL;
    }
    if( value < root->data ){
        // the value we are searching for 
        // is down the left subtree
        // replace this current node with an
        // update one that has the node we are
        // looking for removed
        root->left = deleteNode(root->left,value);

    }else if( value > root->data ){
        // the value we are searching for
        // is down the right subtree
        // repelace this current node with
        // an updated one that has the node we
        // are looking for removed
        root->right = deleteNode(root->right,value);

    }else if( root->data == value ){
        // delete this node
    
        // the node has either one or o
        // children
        if( root->right == NULL ){
            // if right is null then return left
            // no matter if lfet is null or not
            // just return it and it will make
            // the current node's parent's
            // child to the node (or null)
            node* temp = root->left;
            // free this memory since we dont need it anymore
            free(root);
// do i need to change the heights??
            if( temp != NULL)
                updateHeights(temp);
            return temp;
        }else if( root->left == NULL ){
            // if left is null then return right
            // no matter if right is null or not, just
            // return it and it will make the current node's
            // parent child to the temp node
            // or null
            node* temp = root->right;
            // free this memory as this node is not used anymore
            free(root);
            if( temp != NULL)
                updateHeights(temp);
            return temp;
        }

        // this node has two children
        // so we need to move the smallest child
        // in its right subtree to its position
        node* temp = minNode(root->right);
        
        // change the data of the node to the smallest
        root->data = temp->data;

        // we need to now remove the smallest node that
        // we just moved to this position
        root->right = deleteNode(root->right,temp->data);
        
    }
    
    return root;
}

// returns the smallest node in the given tree
node* minNode(node* root){
    node* min = root;
    
    while( min->left != NULL )
        min = min->left;
    return min;
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
