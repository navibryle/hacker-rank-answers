
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; 

/*
cur goal:need to update the height of the nodes, including the node that is being inserted, after insertion and rotation
doing: set the height of the tree
to do: do postorder traversal and set the height of the leafnode to zero 
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
void postTraverse(node * aNode);
void increaseHeight(node * aNode,int height);
void decreaseHeight(node * aNode,int height);
node * insert(node * root,int val);
_Bool heightUpdateCheck(node * aNode);
int getBalanceFactor(node * aNode);
void traversePrintBf(node * root);
int setDepth(node * root);
void traverseDepth(node * aNode,node * parent,int * maxDepth);
void setHeight(node* root);
void traverseHeight(node * aNode,node * parent);
void imabalancedTraverse(node * aNode,node * root,bool * boolVal);
void imabalancedTraverse(node * aNode,node * root,bool * boolVal){
    if (aNode->left != NULL){
        imabalancedTraverse(aNode->left,root,boolVal);
    }
    if (aNode->right != NULL){
        imabalancedTraverse(aNode->right,root,boolVal);
    }
    if (isImbalanced(aNode)){
        *boolVal = true;
        return;
    }else{
        if (aNode == root && isImbalanced(aNode) == false && *boolVal == false){
            *boolVal = false;
            return;
        }
    }
    
}
void setHeight(node * root){
    if (root->left != NULL){
        setHeight(root->left);
    }    
    if (root->right != NULL){
        setHeight(root->right);
    }
    if (root->left == NULL && root->right == NULL){
        root->ht = 0;
    }else if (root->right != NULL){
        root->ht = root->right->ht + 1;
    }else if (root->left != NULL){
        root->ht = root->left->ht +1 ;
    }
}
void traverseHeight(node * aNode, node * parent){
    aNode->ht = parent->ht-1;
    if (aNode->right != NULL){
        traverseHeight(aNode->right,aNode);
    }
    if(aNode->left != NULL){
        traverseHeight(aNode->left,aNode);
    }
}
int setDepth(node * root){
    // will return the maximum depth
    root->ht = 0;
    int maxDepth = 0;
    if (root->left != NULL){
        traverseDepth(root->left,root,&maxDepth);
    }
    if (root->right != NULL){
        traverseDepth(root->right,root,&maxDepth);
    }
    return maxDepth;
}
void traverseDepth(node * aNode,node * parent,int * maxDepth){
    //aNode will be the right or left child of the root
    aNode->ht = parent->ht+1;
    *maxDepth = *maxDepth>(parent->ht+1) ? *maxDepth:parent->ht+1;
    if (aNode->left != NULL){
        traverseDepth(aNode->left,aNode,maxDepth);
    }
    if(aNode->right != NULL){
        traverseDepth(aNode->right,aNode,maxDepth);
    }
}
int getBalanceFactor(node * aNode){
    int leftHeight = getHeight(aNode->left);
    int rightHeight = getHeight(aNode->right);
    return leftHeight - rightHeight;
}
void traversePrintBf(node * root){
    if (root->right != NULL){
        traversePrintBf(root->right);
    }
    if (root->left != NULL){
        traversePrintBf(root->left);
    }
    printf("balance height for node %d is : %d\n",root->val,root->ht);
}
void increaseHeight(node * aNode,int height){
    if (aNode->left != NULL){
       increaseHeight(aNode->left,height);
   }
   if ( aNode->right != NULL){
    increaseHeight(aNode->right,height);
   }
    aNode->ht += height;
}
void decreaseHeight(node * aNode,int height){
    if (aNode->left != NULL){
       decreaseHeight(aNode->left,height);
   }
   if ( aNode->right != NULL){
    decreaseHeight(aNode->right,height);
   }
    aNode->ht--;
}
_Bool heightUpdateCheck(node * aNode){
    //checks if the height needs to be updated aNode needs to be a parent node for the node that is being inserted
    if (aNode->ht == 0){
        return true;
    }
    return false;
}
node * insert(node * root,int val){
    _Bool inserted = false;
    node * curNode = root;
    node * newNode = (node *) malloc(sizeof(struct node));
    node * testNode;
    bool boolVal = false;
    while (inserted == false){
        /*
        if (curNode->val == 5){
            testNode = curNode;
            printf("BF pre insertion: %d\n",getBalanceFactor(testNode));
        }*/
        if (curNode->val > val){
            if (curNode->left == NULL){
                if (heightUpdateCheck(curNode) == true){
                    increaseHeight(root,1);
                    *newNode = (node) {val,NULL,NULL,0};
                }else{
                    *newNode = (node) {val,NULL,NULL,(curNode->ht)-1};
                }
                curNode->left = newNode;
                inserted = true;
            }else{
                curNode = curNode->left;
            }
        }else{
            //curNode->val <= val
            if (curNode->right == NULL){
                if (heightUpdateCheck(curNode) == true){
                    increaseHeight(root,1);
                    *newNode = (node) {val,NULL,NULL,0};
                }else{
                    *newNode = (node) {val,NULL,NULL,(curNode->ht)-1};
                }
                curNode->right = newNode;
                inserted = true;
            }else{
                curNode = curNode->right;
            }
        }
    }
    imabalancedTraverse(root,root,&boolVal);
    while (boolVal){
        postTraverse(root);
        setHeight(root);
        boolVal = false;
        imabalancedTraverse(root,root,&boolVal);
    }
    
    //traversePrintBf(root);
    
    
    
    //printf("BF after rotation: %d\n",getBalanceFactor(testNode));
    return root;
}
int getHeight(node * aNode){
    if (aNode == NULL){
        return -1;
    }else{
        return aNode->ht;
    }
}
_Bool isImbalanced(node * aNode){
    //will return true if the node is imbalanced
    
    int leftHeight;
    int rightHeight;
    if (aNode->left == NULL){
        leftHeight = -1;
    }else{
        leftHeight = aNode->left->ht;
    }
    if (aNode->right == NULL){
        rightHeight = -1;
    }else{
        rightHeight = aNode->right->ht;
    }
    //printf("leftHeight: %d \nrightHeight: %d\n",leftHeight,rightHeight);
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
   if (aNode->left != NULL){
       postTraverse(aNode->left);
   }
   if ( aNode->right != NULL){
    postTraverse(aNode->right);
   }    
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
//========================================DRIVER CODE DO NOT COPY TO HACKERRANK==============================
int main(){
    node five = (node) {5,NULL,NULL,0};
    node two = (node) {2,NULL,NULL,1};
    node four = (node) {4,NULL,&five,1};
    node three = (node) {3,&two,&four,2};
    insert(&three,6);
    return 0;
}