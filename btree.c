#include<stdio.h>
#include<stdlib.h>
#define ORDER 3

struct BtreeNode
{
    int keys[ORDER];
    struct BtreeNode* childPointers[ORDER+1];
    int totalKeys;
    int totalChildPtr;

}*Root;

struct BtreeNode* createNode();
struct BtreeNode* insert(struct BtreeNode*,int);   //To handle the splitting of root 
void insertValue(struct BtreeNode*,struct BtreeNode*,int);
struct BtreeNode* findPositionByRecurssion(struct BtreeNode*,int);
struct BtreeNode* makeChanges(struct BtreeNode* ,struct BtreeNode*,struct BtreeNode*);
            //will return the parent address if chaned then that becomes the root
struct BtreeNode* getSplitNode(struct BtreeNode*);
void traverse(struct BtreeNode *);
void searching(struct BtreeNode *,int);


int main()
{
    Root=NULL;
    int data,choice;
   
   	while (1)
	{
		printf("1. Insertion\t2. Traversal\n");
		printf("3. Searching\t4. Exit\n");
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
				printf("\n");
				traverse(Root);
				printf("\n");
				break;
		
			case 3:
				printf("Enter the element to search:");
				scanf("%d", &data);
				searching(Root,data);
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
    
    struct BtreeNode *ptr = findPositionByRecurssion(root,data);
    
    /* 
     * This condn is just for the first node which is leaf 
     * as well as the root at that time we have to check 
     * the makechanges in here 
     *
     */
    
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

    /*  
     *   leaf node here insertion occurs
     *   But there occurs two condn 
     *   1) Node has vacant places for keys, i.e no overflow
     *   2) Node doesn't has vacant place ,  i.e overflow 
     * 
     */ 
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

void searching(struct BtreeNode * root , int data)
{

    // Find the first key greater than or equal to k 
    int i = 0; 
    while ( i< root->totalKeys && data> root->keys[i]) 
        i++;
  
    // If the found key is equal to k, return this node 
    if (root->keys[i] == data) 
      {
      	  printf("Key found at index %d and the data is %d \n",i,root->keys[i]);
      	  return;
      }
  
    // If the key is not found here and this is a leaf node 
    if (root->totalChildPtr<=0) 
       {
       		 printf("\nKey not found\n");
       		 return;
       }
  
    // Go to the appropriate child 
    searching(root->childPointers[i],data);
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
    for(i=(ORDER/2)+1,j=0;i<ORDER;i++,j++)
        newNode->keys[j]=root->keys[i];

    //copy ptr till i<=order pointer = key+1
    for(i=(ORDER/2)+1,j=0;i<=ORDER;i++,j++)
        newNode->childPointers[j]=root->childPointers[i];

    newNode->totalKeys = ORDER/2;
    root->totalKeys = ORDER - (ORDER/2) - 1;

    //setting the number of pointers, which would be equally distributed
    if(root->totalChildPtr>0)
    {
        newNode->totalChildPtr = 1+ORDER/2;
        root->totalChildPtr = ORDER-(ORDER/2);

    }
    else    //leaf nodes hence no child
        newNode->totalChildPtr = root->totalChildPtr = 0;
    

    return newNode;
}
void insertValue(struct BtreeNode* root,struct BtreeNode* newNode,int data)
{
    /*
     * One additional address is used while splitting 
     * 
     * find the position where we hav to insert
     * shift the keys one place ahead as insertion in array 
     * shift all the j>i one place ahead leaving the i'th  
     * index pointer as it is coz that will maintain the BST
     * according to the temporary middle logic
     * 
     */

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
        root->totalChildPtr++;

    
}
struct BtreeNode* makeChanges(struct BtreeNode* overflowNode,struct BtreeNode* newNode,struct BtreeNode* parent)
{
    /*
     *  First retrieve the temporarily stored median value
     *  Put the middle node in its parrent node if exists 
     *  else Create a new node and set its 0th and 1st index
     *  of childptr as if left and right child and put the value
     *  in Oth index of array
     * 
     * 
     *  i.e There are 2 cases 
     *  1 : parent is NULL
     *  2a: there is space inside parent node (for NULL parent this will always be true)
     *  2b: no space first insert then split 
     */

    int midValue = overflowNode->keys[overflowNode->totalKeys]; 
    /*
     *  3/2 = 1 but zero indexing gives 2nd element 
     * ie the temporary mid elememt 
     *  
     */

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
    
    int i;
    for (i = 0; i < root->totalKeys; i++)
    {
        if (root->totalChildPtr > 0)
        {
            traverse(root->childPointers[i]);
        }
        printf("   %d",root->keys[i]);
    } 
    if (root->totalChildPtr > 0)
        traverse(root->childPointers[i]);

    
}


