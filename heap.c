    #include<stdio.h>
    #include<stdlib.h>

    int arraySize,heapSize;

    void insert(int [],int,int);
    void display(int []);
    void heapify(int [],int);
    void swap(int * ,int *);
    void heapSort(int []);
    
    int main()
    {
        int choice,array[100],data,i;
        
        arraySize=heapSize=0;

        while(1)
        {
            printf("1] Insert\n");
            printf("2] Sort\n");
            printf("\nEnter your choice \n");
            scanf("%d",&choice);

            switch(choice)
            {
            
                case 1:
                    printf("\nEnter the value \n");
                    scanf("%d",&data);
                    heapSize++;
                    arraySize++;
                    insert(array,data,arraySize);
                    display(array);
                    break;
                
                case 2:
                    heapSort(array);
                    display(array);
                    exit(0);

                default :
                    printf("\nInvalid Input \n");
            }
        }
         
        return 0;
    }

    void insert(int arr[],int data,int i)
    {
        // here i is the index where value is to be inserted
        if(i==1)
        {
            arr[i]=data;
            return;
        }

        arr[i]=data;
        int parent = i/2 ;
    
        if(!(arr[parent]>arr[i]))
        {
            swap(&arr[parent],&arr[i]);
            insert(arr,arr[parent],parent);
        }

    }

    void heapify(int arr[],int i)
    {
        int left,right,max;
        
        max=i;
        left=2*i;
        right=2*i + 1;
        
        //whenever left or right index becomes greater 
        //than heapSize recursion terminates
        
        //for min heap just change '>' to '<' in heapify i.e and max to min 

        if(left <= heapSize && arr[left]>arr[i])       // arr[left]<arr[i]       
            max = left;
        
        if(right<= heapSize && arr[right]>arr[max])    // arr[right]<arr[max]
            max=right;

        if(i!=max)
        {
            swap(&arr[i],&arr[max]);
            heapify(arr,max);
        }
    }

    void heapSort(int arr[])
    {
        int i =heapSize;

    //when only one element remains in heap sorting is completed
        while(heapSize >1)  
        {
            swap(&arr[1],&arr[i]);
            heapSize--;
            i--;
            heapify(arr,1);
        }
    }

    void swap(int *x,int *y)
    {
        int temp;
        temp = *x;
        *x = *y;
        *y = temp;
    }

    void display(int arr[])
    {
        printf("\nThe heap array is as follows :- \n");

        for(int i=1;i<=arraySize;i++)
            printf("%d  ",arr[i]);
                    
        printf("\n\n");
    }
