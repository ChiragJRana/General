#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// state 
// -1  -----> Not Explored (initial)
//  0  -----> Added to queue(waiting)
//  1  -----> Visited 
struct Cities                   //Represents a vertex 
{
   char cityname[20];
   struct ConnectedCities *firstEdge;  //*first edge of the adjacency list of this vertex
   struct Cities *next;               //*next vertex in the linked list of vertices
   struct Cities *parent;
   int state;
}*start,*end;

struct ConnectedCities          //Represents  an edge
{
    char destinationName[20];
    struct Cites *destinationloc;     //Address of Destination vertex of the edge
    struct ConnectedCities *next;  //next edge of the adjacency list 
};

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

void addCities(char name[]);
struct Cities *searchCity(char name[]);
void print();
void addRoute(char [] ,char []);
void print1(struct ConnectedCities *);
int isEmpty();

int findRoute(struct Cities *, struct Cities *);  //returns 1 if route exists else 0

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
        printf("3] Print\n");
        printf("4] AddRoute\n");
        printf("5] PrintRoute\n");
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
                printf("Path Found \n");
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
                 temp->parent=p;
            }

            trav=trav->next;
               
                
        }
        
        
        
    }

    if(!isEmpty())
    {
        printf("No path exists \n");
        return 0;
    }

}


int isEmpty()
{
    if(front == NULL)
        return 0;
    else
        return 1;
}
