#include<stdio.h>
#include<stdlib.h>

struct Tree
{
    int key;
    struct Tree *left;
    struct Tree *right;
};
struct Tree *Root =NULL;

struct Tree *insert(struct Tree * ,int );
void inorder(struct Tree *);
struct Tree *findMinimum(struct Tree *);
struct Tree *delete(struct Tree * , int);
int hasChild(struct Tree *);

int main()
{

    int flag,choice;
    flag=1;

    while(flag)
    {
       
        printf("1] Insert\n");
        printf("2] Search\n");
        printf("3] Delete\n");
        printf("4] Find Minimum\n");
        printf("5] Traverse\n");
        printf("6] EXit\n");

        printf("\n");
        printf("Enter the choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            {
                int data[100],n;

                printf("Enter No of elements :  ");
                scanf("%d",&n);

                printf("Enter the Keys\n");
                for (int i = 0; i < n; i++)
                {
                    scanf("%d",&data[i]);
                }

                Root = insert(Root,data[0]);
                
                for (int i = 1; i < n; i++)
                {

                   struct Tree *temp = insert(Root,data[i]);
                  
                }
                printf("\n\n");
                
                break;
            }
            case 5:
            {
                printf("\n\n");
                printf("Inorde Traversal is shown below : \n");
                inorder(Root);
                printf("\n\n");
                break;
            }

            case 4:
            {

                printf("\n\n");    
                
                struct Tree *loc= findMinimum(Root);
                if(loc !=NULL)
                printf("The minimum key is %d \n",loc->key);
               
                printf("\n\n"); 
               
                break;
            }

            case 3:
            {
                printf("\n\n");

                printf("Enter the key to be deleted\n");
                int key;
                scanf("%d",&key);
                struct Tree *loc = delete(Root,key);    //The location returned is always the root location
                printf("Returned loc is %d \n",loc->key);
                

                printf("\n\n");
                break;
            }
            case 6:
                exit(0);
        }
        

    }


    return 0;
}

struct Tree *insert(struct Tree *root,int key)
{
    if(root==NULL)
    {
        struct Tree *temp = (struct Tree *)malloc(sizeof(struct Tree ));
        temp->left=temp->right=NULL;
        temp->key=key;
        return(temp);
    }
    else if(key < root->key)
    root->left=insert(root->left,key);
    else
    root->right=insert(root->right,key);

   
    return(root);
}

void inorder(struct Tree *root)
{
  

    if(root==NULL)
        return;
    
    inorder(root->left);
    printf("%d  ",root->key);
    inorder(root->right);

    
}

struct Tree *findMinimum(struct Tree *node)
{
    while(node->left != NULL)
        node=node->left;

    return node;
}

struct Tree *delete(struct Tree *root , int key)
{
    if(key < root->key)
    {
        root->left = delete(root->left,key);
        return root;
    }
    else if(key > root->key)
    {
        root->right = delete(root->right,key);
        return root;
    }

    //If we are here then this root's key is equal to key to be deleted 

    if(hasChild(root)==2)
    {
        free(root);
        return NULL;
    }

    else if(hasChild(root)==6)      //only left child
    {
       struct Tree *temp = root->left;
       free(root);
       return temp;
    }

    else if(hasChild(root)==3)  //only right child
    {
        struct Tree *temp = root->right;
        free(root);
        return temp;
    }
    else            //both child
    {
        struct Tree *minimum = findMinimum(root->right);
        root->key = minimum->key;

        root->right = delete(root->right,minimum->key);

        return root;
    }
    

    

}

int hasChild(struct Tree *root)
{
    if(root->left == NULL && root->right == NULL)
        return 2;
    else if( root->left==NULL)
        return 3;
    else if(root->right==NULL)
        return 6;
    else
        return 7;
}