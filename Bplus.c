#include<stdio.h>
#include<stdlib.h>
#define ORDER 3

struct BtreeNode
{
    int keys[ORDER];
    struct BtreeNode* childPointers[ORDER+1];
    int totalKeys;
    int totalChildPtr;
    struct BtreeNode* right;

}*Root;

struct BtreeNode* createNode();
struct BtreeNode* insert(struct BtreeNode*,int);   //To handle the splitting of root 
void insertValue(struct BtreeNode*,struct BtreeNode*,int);
struct BtreeNode* findPositionByRecurssion(struct BtreeNode*,int);
struct BtreeNode* makeChanges(struct BtreeNode* ,struct BtreeNode*,struct BtreeNode*);
            //will return the parent address if chaned then that becomes the root
struct BtreeNode* getSplitNode(struct BtreeNode*);
void traverse(struct BtreeNode *);
int searching(struct BtreeNode *,int,int);


int main()
{
    Root=NULL;
    int data,choice;
   
   	while (1)
	{
		printf("\n1. Insertion\t2. Traversal\n");
		printf("3. Searching\t4. Exit\n\n");
		printf("Enter your choice:");
		scanf("%d",&choice);
		switch (choice) 
		{
			case 1:
				printf("Enter your input:");
				scanf("%d", &data);
				Root = insert(Root,data);
				break;
		
			case 2:
				printf("\nThe values are as follows :- \n");
				traverse(Root);
				printf("\n\n");
				break;
		
			case 3:
				printf("Enter the element to search:");
				scanf("%d", &data);
				searching(Root,data,1);
				break;
		
			case 4:
				exit(0);
				break;
		
			default:
				printf("Invalid\n");
				break;
		}
	}


   	
   

    return 0;
}
struct BtreeNode* createNode()
{
    struct BtreeNode* temp = (struct BtreeNode*)malloc(sizeof(struct BtreeNode));
    temp->totalChildPtr=temp->totalKeys=0;
    for(int i=0;i<ORDER;i++)
        temp->keys[i]=-1;
    temp->right=NULL;
    return temp;
}

struct BtreeNode* insert(struct BtreeNode* root,int data)
{
    if(root == NULL)    //base condn for creating the first node of btree
    {
         struct BtreeNode *newNode =createNode();
         newNode->keys[0] = data;
         newNode->totalKeys++;
         return newNode;
    }
    

    int flag = searching(root,data,0);
    if(flag)
    {
        printf("Key is present in the tree, no repetition is allowed\n");
        return root;
    }
    struct BtreeNode *ptr = findPositionByRecurssion(root,data);
    
   
    
    if(ptr != root)
        return makeChanges(root,ptr,NULL);  //new root will be returned
    
    return root;
}

struct BtreeNode* findPositionByRecurssion(struct BtreeNode* root,int data)
{
    struct BtreeNode* newNode;
    int i;

    if(root->totalChildPtr > 0) //non leaf; then recursively locate the branch to follow
    {
        for(i=0;i<root->totalKeys && data>root->keys[i];i++); //only finds the required branch to follow

        newNode = findPositionByRecurssion(root->childPointers[i],data);
        if(newNode != root->childPointers[i]) //ie splitting has occur and we have to make changes
            return makeChanges(root->childPointers[i],newNode,root);
        
        return root;
    }

 
    else    
    {
        if(root->totalKeys < ORDER-1)//no overflow
        {
            insertValue(root,NULL,data);
            return root;
        }
        else    //overflow
        {
            insertValue(root,NULL,data);
            return getSplitNode(root);;
            
        }
    } 
}

int searching(struct BtreeNode * root , int data ,int flag)
{

    // Find the first key greater than or equal to k 
    int i = 0; 
    while ( i< root->totalKeys && data> root->keys[i]) 
        i++;
  
    // If the found key is equal to k, return this node 
    if (root->keys[i] == data) 
      {
          if(flag)
      	  printf("Key is present in the tree\n");
      	  return 1;
      }
  
    // If the key is not found here and this is a leaf node 
    if (root->totalChildPtr<=0) 
       {
             if(flag)
       		 printf("Key not found\n\n");
       		 return 0;
       }
  
    // Go to the appropriate child 
    searching(root->childPointers[i],data,flag);
} 


struct BtreeNode* getSplitNode(struct BtreeNode* root)
{
    /*
     *  returns a new node which contains all the values>mid
     *  middle key is temporarily stored in the original node
     * 
     */
    int i,j;
    struct BtreeNode* newNode = createNode();
    
    //copy value till i<order
    for(i=(ORDER/2),j=0;i<ORDER;i++,j++)
    {
        newNode->keys[j]=root->keys[i];
        newNode->totalKeys++;
        root->totalKeys--;

    }
    //copy ptr till i<=order pointer = key+1
    for(i=(ORDER/2),j=0;i<=ORDER;i++,j++)
        newNode->childPointers[j]=root->childPointers[i];

    //newNode->totalKeys = (ORDER/2)+1;
    //root->totalKeys = ORDER - (ORDER/2) - 1;

    //setting the number of pointers, which would be equally distributed
    if(root->totalChildPtr>0)
    {
        newNode->totalChildPtr = newNode->totalKeys + 1;
        root->totalChildPtr = root->totalKeys + 1;

    }
    else    //leaf nodes hence no child
    {
         newNode->totalChildPtr = root->totalChildPtr = 0;
         newNode->right = root->right;
         root->right = newNode;
    }
    

    return newNode;
}
void insertValue(struct BtreeNode* root,struct BtreeNode* newNode,int data)
{
    int i,j;
    for(i=0;i<root->totalKeys && data > root->keys[i];i++);

    //shift keys and pointers 
    for(j=root->totalKeys-1;j>=i;j--)
    {
        root->keys[j+1]=root->keys[j];
        root->childPointers[j+2]=root->childPointers[j+1];
    }

    root->keys[i]=data;
    root->childPointers[i+1]=newNode;
    root->totalKeys++;

    if(newNode!=NULL)
    {
        root->totalChildPtr++;
        if(newNode->totalChildPtr > 0)  //shift keys and pointers
        {
            for(i=1;i<newNode->totalKeys;i++)
                newNode->keys[i-1] = newNode->keys[i];
            
            newNode->totalKeys--;
            
            for(i=1;i<newNode->totalKeys+1;i++)
                newNode->childPointers[i-1]=newNode->childPointers[i];

            newNode->totalChildPtr--;
        }
    }

    
}
struct BtreeNode* makeChanges(struct BtreeNode* overflowNode,struct BtreeNode* newNode,struct BtreeNode* parent)
{

    int midValue = newNode->keys[0]; 
 
    if(parent==NULL)    //1st case 
    {
        parent = createNode();
        parent->childPointers[0]=overflowNode;
        parent->totalChildPtr++;
    }

    if(parent->totalKeys<ORDER-1)   //2a
    {
        insertValue(parent,newNode,midValue);
        return parent;
    }
    else //2b
    {
        insertValue(parent,newNode,midValue);
        return getSplitNode(parent);
    }
}

void traverse(struct BtreeNode *root)
{
    struct BtreeNode *temp = root;

    while(root->childPointers[0]!=NULL)
        root = root->childPointers[0];  

    while (root!= NULL)
    {
        for(int i=0;i<root->totalKeys;i++)
            printf("%d  ",root->keys[i]);

        root = root->right;
    }

    printf("\n\n"); 
}

