
#include <stdio.h>
#include <stdbool.h>
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; 

/*
need to identify the height of the tree then need to identify if the tree is unbalanced and then need to the proper rotations.
Need to be done from the bottom up. therefore traverse the tree from the bottom first. Therefore use postorder tree traversal.
update: the height of each node is a property of the struct
cur goal: write out the function that will actually do the rotation i.e. 'case#'
*/
_Bool isCase1(node *aNode);
_Bool isCase2(node *aNode);
_Bool isCase3(node *aNode);
_Bool isCase4(node *aNode);
node * insert(node * root,int val);
_Bool isImbalanced(node * aNode);
void case1(node * aNode);
void case2(node * aNode);
void case3(node * aNode);
void case4(node * aNode);
void switchContents(node * Node1,node * Node2);
void performRotation(node * aNode);
int getHeight(node * aNode);
node * insert(node * root,int val);
node * insert(node * root,int val){
    node * newNode = {val,NULL,NULL,-1};
    //postTraverse()
}
int getHeight
_Bool isImbalanced(node * aNode){
    int leftHeight = aNode->left->ht;
    int rightHeight = aNode->right->ht;
    return ((leftHeight - rightHeight) > 1) || ((leftHeight - rightHeight) < -1);
}
_Bool isCase1(node * aNode){
    return (aNode->left != NULL && aNode->left->right != NULL);
}
_Bool isCase2(node * aNode){
    return (aNode->right != NULL && aNode->right->left != NULL);
}
_Bool isCase3(node * aNode){
    return (aNode->left != NULL && aNode->left->left != NULL);
}
_Bool isCase4(node * aNode){
    return (aNode->right && aNode->right->right);
}
void case1(node * aNode){
    //left right case
    /*
    aNode is the node where we want to perform the case1 avl rotation
    */
    switchContents(aNode,aNode->left->right);
    node * leaf1 = aNode->left->left;
    node * leaf2 = aNode->left->right->left;
    node * leaf3 = aNode->left->right->right;
    node * leaf4 = aNode->right;
    node * root = aNode;
    node * leftChild = aNode->left;
    node * rightChild = aNode->left->right;
    //now just need to connect the nodes to create the balanced trees
    root->left = leftChild;
    root->right = rightChild;
    leftChild->left = leaf1;
    leftChild->right = leaf2;
    rightChild->left = leaf3;
    rightChild->right = leaf4;   
    
}
void case2(node * aNode){
    //right left case
    /*
    aNode is the node where we want to perform the case1 avl rotation
    */
    switchContents(aNode,aNode->right->left);
    node * leaf1 = aNode->left;
    node * leaf2 = aNode->right->left->left;
    node * leaf3 = aNode->right->left->right;
    node * leaf4 = aNode->right->right;
    node * root = aNode;
    node * leftChild = aNode->right->left;
    node * rightChild = aNode->right;
    //now just need to connect the nodes to create the balanced trees
    root->left = leftChild;
    root->right = rightChild;
    leftChild->left = leaf1;
    leftChild->right = leaf2;
    rightChild->left = leaf3;
    rightChild->right = leaf4;   
    
}
void case3(node * aNode){
    //left left case 
    /*
    aNode is the node where we want to perform the case1 avl rotation
    */
    switchContents(aNode,aNode->left);
    node * leaf1 = aNode->left->left->left;
    node * leaf2 = aNode->left->left->right;
    node * leaf3 = aNode->left->right;
    node * leaf4 = aNode->right;
    node * root = aNode;
    node * leftChild = aNode->left->left;
    node * rightChild = aNode->left;
    //now just need to connect the nodes to create the balanced trees
    root->left = leftChild;
    root->right = rightChild;
    leftChild->left = leaf1;
    leftChild->right = leaf2;
    rightChild->left = leaf3;
    rightChild->right = leaf4;   
    
}
void case4(node * aNode){
    //right right case
    /*
    aNode is the node where we want to perform the case1 avl rotation
    */
    switchContents(aNode,aNode->right);
    node * leaf1 = aNode->left;
    node * leaf2 = aNode->right->left;
    node * leaf3 = aNode->right->right->left;
    node * leaf4 = aNode->right->right->right;
    node * root = aNode;
    node * leftChild = aNode->right;
    node * rightChild = aNode->right->right;
    //now just need to connect the nodes to create the balanced trees
    root->left = leftChild;
    root->right = rightChild;
    leftChild->left = leaf1;
    leftChild->right = leaf2;
    rightChild->left = leaf3;
    rightChild->right = leaf4;   
    
}
void performRotation(node * aNode){
    if (isCase1(aNode) == true){
        case1(aNode);
    }else if (isCase2(aNode) == true){
        case2(aNode);
    }else if (isCase3(aNode) == true){
        case3(aNode);
    }else if (isCase4(aNode) == true){
        case4(aNode);
    }else{
        //idk what to put here 
    }
}
void postTraverse(node * aNode){
    postTraverse(aNode->left);
    postTraverse(aNode->right);
    if (isImbalanced(aNode) == true){
        performRotation(aNode);
    }
}
void switchContents(node * Node1,node * Node2){
    //this function will switch the contents of two nodes but keep the same pointers
    int temp1 = Node1->val;
    int temp2 = Node2->val;
    Node1->val = temp2;
    Node2->val = temp1;
}
