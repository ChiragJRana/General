#include<stdio.h>
#include<stdlib.h>

struct queue
{
    int n;
    struct queue *next;
};
struct queue *front=NULL;
struct queue *rear=NULL;

void enque(int);
int dequeue();

int main()
{
    int flag=1,choice;
    
        
    while(flag)
    {
        printf("1]enque\n");
        printf("2]deque\n");
        printf("enter choice\n\n");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("enter the value\n");
            scanf("%d",&flag);
            enque(flag);
        }
        else
        {
            flag=dequeue();
            if(flag!= -1)
            printf("value is %d",flag);
            else
            printf("Queu is empty\n");
        }
        
        printf("more?\n\n");
        scanf("%d",&flag);

    }

    return 0;
}

void enque(int n)
{
    struct queue *temp = (struct queue *)malloc(sizeof(struct queue));
    temp->n=n;
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

int dequeue()
{
    if(front!=NULL)
    {
        struct queue *temp = front;
        front=front->next;
        int n = temp->n;
        free(temp);
        return(n);
    }
    else
        return(-1);
}
