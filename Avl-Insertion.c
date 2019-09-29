/*
* Try enchancing balance factor function for only one pointer input
* Write testing function of rotateLeft and right


*/


#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int key,height,bf;
    struct Node *left,*right;

};

struct Node *createNode(int );//done
int max(int ,int ); //done
int setHeight(struct Node *);//done
int getHeight(struct Node *);//done
int balanceFactor(struct Node *,struct Node *); //done
struct Node *rotateLeft(struct Node *);//done
struct Node *rotateRight(struct Node *);//done
struct Node *insert(struct Node *,int);//done


void inorder(struct Node *);//done

int main()
{

    struct Node *root = NULL; 
  
  /* Constructing tree given in the above figure  */
  root = insert(root, 10); 
  root = insert(root, 20); 
  root = insert(root, 30); 
  root = insert(root, 40); 
  root = insert(root, 50); 
  root = insert(root, 25); 
 
  /* The constructed AVL Tree would be 
            30 
           /  \ 
         20   40 
        /  \     \ 
       10  25    50 
  */
  
  printf("Inorder traversal of the constructed AVL tree is \n"); 
  printf("KEY --> (BF) AND (HT)\n\n");
  
  inorder(root);
  printf("\n");


    return 0;
}


void inorder(struct Node *root)
{
  

    if(root==NULL)
        return;
    
    inorder(root->left);
    printf("%d-->(%d) and (%d)\n",root->key,root->bf,root->height);
    inorder(root->right);

}

struct Node *createNode(int key)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->key=key;
    temp->left = temp->right = NULL;
    temp->bf = temp->height = 0;

    return temp;
}

int max(int a,int b)
{
    return (a>b)?a:b ;  //beacuse of this if two integers are equal that case is also esaily handeled
}

int setHeight(struct Node *root)
{
    if(root ==NULL)
        return -1;
        
    int lheight,rheight;

    if(root->left != NULL)
        lheight = root->left->height;
    else
        lheight = -1;
    
    if(root->right != NULL)
        rheight = root->right->height;
    else
        rheight = -1;

    
    return(1 + max(lheight,rheight));
}

int getHeight(struct Node *root)
{
    if(root == NULL)
        return -1;
    else
        return root->height;
}

int balanceFactor(struct Node *rootLeft,struct Node *rootRight)
{
    return getHeight(rootLeft) - getHeight(rootRight);
}

struct Node *rotateLeft(struct Node *unbalanced)
{
    struct Node *newRoot = unbalanced->right;
    unbalanced->right = newRoot->left;
    newRoot->left = unbalanced;

    //Setting Height

    unbalanced->height = setHeight(unbalanced);
    newRoot->height = setHeight(newRoot);

    //testing
    unbalanced->bf = balanceFactor(unbalanced->left,unbalanced->right);
    newRoot->bf = balanceFactor(newRoot->left,newRoot->right);

    return newRoot;
    
}

struct Node *rotateRight(struct Node *unbalanced)
{
    struct Node *newRoot = unbalanced->left;
    unbalanced->left = newRoot->right;
    newRoot->right = unbalanced;

    //Setting Height

    unbalanced->height = setHeight(unbalanced);
    newRoot->height = setHeight(newRoot);

    unbalanced->bf = balanceFactor(unbalanced->left,unbalanced->right);
    newRoot->bf = balanceFactor(newRoot->left,newRoot->right);

    //testing

    return newRoot;
    
}

struct Node *insert(struct Node *root,int key)
{
    if(root == NULL)
        return createNode(key);
    
    if(key <= root->key)
        root->left = insert(root->left,key);
    else
        root->right = insert(root->right,key);

    //Balancing

    int balance = balanceFactor(root->left,root->right);        //print balance acc to aim of exp

    root->bf = balance;   //testing can print the bf of all nodes using this too acc to exp
    if(balance > 1)
    {
        if( getHeight(root->left->left) >= getHeight(root->left->right) )   
            root = rotateRight(root);       //print type of rotation acc to aim of exp i.e LL
        else
        {
            root->left = rotateLeft(root->left);   //print type of rotation acc to aim of exp i.e LR
            root = rotateRight(root);   
        }
        
    }
    else if(balance < -1)
    {
        if( getHeight(root->right->right) >= getHeight(root->right->left) )   
            root = rotateLeft(root);       //print type of rotation acc to aim of exp i.e RR
        else
        {
            root->right = rotateRight(root->right);   //print type of rotation acc to aim of exp i.e RL
            root = rotateLeft(root);   
        }
        
    }
    else        //while going back recursively update the height of each node which was visited down the path 
    {
        root->height = setHeight(root);
            
    }

    return root;
    
}