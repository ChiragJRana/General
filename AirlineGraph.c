/*           STATES
 -1  -----> Not Explored (initial)
  0  -----> Added to queue(waiting)
  1  -----> Visited 

*/

/*
print()             -----> To print NODES in the system which are Cities , Adjacency array Adj[i] 
print1()            -----> To print all the VERTEX from a given nodes ie possible ways from a particular node 
printRoute()        -----> To print the path which is found for a particular source and destination city 

 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Cities                   //Represents a vertex 
{
   char cityname[20];
   struct ConnectedCities *firstEdge;  //*first edge of the adjacency list of this vertex
   struct Cities *next;               //*next vertex in the linked list of vertices
   struct Cities *parent;
   int state;
   int state2;
}*start,*end;

struct ConnectedCities          //Represents  an edge
{
    char destinationName[20];
    struct Cites *destinationloc;     //Address of Destination vertex of the edge
    struct ConnectedCities *next;  //next edge of the adjacency list 
};

//For BFS purpose
struct queue
{
    char name[20];
    struct Cities *loc;
    struct queue *next;
};
struct queue *front=NULL;
struct queue *rear=NULL;

void enque(struct Cities *);
struct Cities *dequeue();

int isEmpty();

//End of BFS Interface


//Controls for user
void addCities(char name[]);
struct Cities *searchCity(char name[]);
void addRoute(char [] ,char []);
int findRoute(struct Cities *, struct Cities *);  //returns 1 if route exists else 0

// End of Control Interface


// For Printing Different Content
void print();
void print1(struct ConnectedCities *);
void printRoute(struct Cities *); 
//End Of print interface

void bfs(struct Cities *source);       //for reusablity


int main()
{
    start=NULL;
    end=NULL;

    int choice,flag=1;
    char name[20],destination[20];  //Using name variable as sourceName during addRoute function

    while(flag)
    {
        printf("1] AddCities\n");
        printf("2] Searrch\n");
        printf("3] Print (cities array pointers down)\n");
        printf("4] AddRoute\n");
        printf("5] Print1(connected cities)\n");
        printf("6] FindRoute\n");
        printf("Enter Your Choice\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: 
            {
                printf("enter the city name\n");
                scanf(" %s",name);
                addCities(name);
                break;
            }
            case 2:
            {
                printf("enter the city name to search\n");
                scanf(" %s",name);
                struct Cities *add = searchCity(name);
                printf("City found is  %s\n",add->cityname);
                break;
            }
            case 3:
            {
                print();
                break;
            }
            case 4:
            {
                printf("enter the source name and then destination's name\n");
                scanf(" %s %s",name,destination);
                addRoute(name,destination);
                break;
            }
            case 5:
            {
                printf("enter the city name whose connectivity is to be looked \n\n");
                scanf(" %s",name);

                struct Cities *add = searchCity(name);
                print1(add->firstEdge);
                break;

            }

            case 6:
            {
                printf("enter the source city \n");
                scanf(" %s",name);
                struct Cities *s= searchCity(name);
                printf("enter the destination city \n");
                scanf(" %s",destination);
                struct Cities *d= searchCity(destination);
                int returnValue= findRoute(s,d);

                int count=0;
                if(returnValue == 1)
                    {

                        count++;
                      

                        if(count)
                            {
                                printf("Clearing the state to initial\n\n");
                                struct Cities *start = searchCity("Pune");
                                bfs(start);
                                break;
                            }
                    }
                else
                {
                    printf("No path exists \n");
                    break;   
                }
                
                break;
            }

            default:
                break;
        }

        printf("if more press 1 else 0\n");
        scanf("%d",&flag);

    }
    
    

    return 0;
}

void addCities(char name[])
{
    struct Cities *temp = (struct Cities *)malloc(sizeof(struct Cities));
    strcpy(temp->cityname,name);
    temp->firstEdge=NULL;
    temp->next=NULL;
    temp->parent=NULL;
    temp->state=-1;
    temp->state2=-1;
   
    if(start==NULL)
    {
        end =temp;
        start=temp;
    }
    else
    {
        end->next=temp;
        end=temp;
    }
    
}

struct Cities *searchCity(char name[])
{
    struct Cities *traverse =start;
    while(traverse!=NULL)
    {
        if(strcmp(traverse->cityname,name)==0)
            return(traverse);
        
        traverse=traverse->next;
    }

    return(NULL);
}

void print()
{
    struct Cities *traverse =start;
    printf("CITYNAME \n");
    while(traverse!=NULL)
    {
        printf("%s  \n",traverse->cityname);
        
        traverse=traverse->next;
    }
}


void print1(struct ConnectedCities *start)
{
    struct ConnectedCities *traverse =start;
    printf("CITYNAME \n");
    while(traverse!=NULL)
    {
        printf("%s  \n",traverse->destinationName);
        
        traverse=traverse->next;
    }   
}

void addRoute(char source[],char destination[])
{
    struct Cities *sourceAddress;
    struct Cities *destinationAddress;

    sourceAddress=searchCity(source);
    destinationAddress=searchCity(destination);

    if(sourceAddress==NULL)
    {
        printf("Invalid source name\n\n");
        return;
    }
    if(destinationAddress==NULL)
    {
        printf("Invalid destination name\n\n");
        return;
    }

    struct ConnectedCities *temp;
   
    temp= (struct ConnectedCities *)malloc(sizeof(struct ConnectedCities));
    strcpy(temp->destinationName,destination);
    temp->destinationloc = destinationAddress;
    temp->next =NULL;

    //IF no connected cities then insert it as the first connected city else
    // iterate connected cities till you reach the last element
    if(sourceAddress->firstEdge ==NULL)
    {
        sourceAddress->firstEdge = temp;
        return;
    }
    
    struct ConnectedCities *traverse;
   
    traverse=sourceAddress->firstEdge;
    while(traverse->next !=NULL)
        traverse=traverse->next;

    traverse->next=temp;

}

void enque(struct Cities *loc)
{
    struct queue *temp = (struct queue *)malloc(sizeof(struct queue));
    temp->loc=loc;
    strcpy(temp->name,loc->cityname);
    temp->next=NULL;

    if(front == NULL)
    {
        front=temp;
        rear=temp;
    }
    else
    {
        rear->next=temp;
        rear=temp;

    }   
}
struct Cities *dequeue()
{
    struct queue *temp= front;
    struct Cities *loc;
    if(front!=NULL)
    {
        front=front->next;
        loc= temp->loc;
        free(temp);
        return(loc);
    }
    else
        return(NULL);
    
}

int findRoute(struct Cities *source, struct Cities *destination)
{
    enque(source);
    source->state=0;            //waiting state
    source->parent=NULL;
    struct Cities *temp;
    struct Cities *p; //represents parent level of current level

    while(isEmpty())
    {
        p=dequeue();
        p->state =1;        // Visited state
        if((strcmp(destination->cityname,p->cityname))==0)
            {
                printf("Path Found \n\n");
                printRoute(p);
                return 1;
            }

        struct ConnectedCities *trav;
        trav = p->firstEdge;

        while(trav!=NULL)
        {
            temp= trav->destinationloc;

            if(temp->state == -1)       //if in initial state then enqueue thema
            {
                 enque(temp);
                 temp->state=0;
                 temp->parent=p;        //setting current level parent as previous level
                                        //ie if CL = 1  CL[1]=parent=CL[0]
                                        //if i is current level parent will be i-1 level
            }

            trav=trav->next;
               
                
        }
        
        
        
    }

    if(!isEmpty())
    {
        
        return 0;
    }

}


int isEmpty()               //queue empty or not if empty return 0 else 1
{
    if(front == NULL)
        return 0;
    else
        return 1;
}


void bfs(struct Cities *source)         //for code reusability
{
    enque(source);
    source->state2=0;       //waiting state

    source->state=-1;       //setting initial values 
    source->parent=NULL;    //setting initial values
    
    struct Cities *temp;
    struct Cities *p; //represents parent level of current level

    while(isEmpty())
    {
        p=dequeue();
        p->state2=1;
        
        p->state =-1; //setting initial values
        p->parent=NULL;     
        
        printf("%s ---> ",p->cityname);  
       
        struct ConnectedCities *trav;
        trav = p->firstEdge;

        while(trav!=NULL)
        {
            temp= trav->destinationloc;

            if(temp->state2 == -1)       //if in initial state then enqueue thema
            {
                 enque(temp);
                 temp->state2=0;

                 temp->state=-1;
                 temp->parent=NULL;
            }
            trav=trav->next;
               
                
        }
        
        
        
    }

    printf("\n\n");
    if(!isEmpty())
    {
        printf("No path exists \n");
        return ;
    }

}

void printRoute(struct Cities *dest)
{
    struct Cities *temp = dest;

    while(temp!=NULL)
    {
        printf("%s <---",temp->cityname);
        temp=temp->parent;
    }

    printf(" Source City\n\n");
}
