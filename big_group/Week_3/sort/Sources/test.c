#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Headers/sort.h"
#include "../Headers/rand.h"

/*
    * Function to test the sorting algorithms
    * @param selection: the selection of the sorting algorithm
    * @param numofdata: the num of a data
    * @param datas: the sum of datas
*/

void test_sort(int selection,int numofdata)
{
    int *arr;
    arr=generate_testdata(numofdata,_MIN,_MAX);
    save_data(arr,numofdata,"test.txt",0);
    arr=read_data(numofdata,"test.txt");

    if(selection==1)
    {
        bubblesort(arr,numofdata);
    }
    else if(selection==2)
    {
        insertsort(arr,numofdata);
    }
    else if(selection==3)
    {
        quicksort(arr,0,numofdata-1);
    }
    else if(selection==4)
    {
        mergesort(arr,0,numofdata-1);
    }
    else if(selection==5)
    {
        radixcountsort(arr,numofdata);
    }
    else if(selection==6)
    {
        countsort(arr,numofdata);
    }

    save_data(arr,numofdata,"result.txt",1);

}

/*
    * Main function to test the sorting algorithms
*/
int main()  
{
    int selection;
    int datas;
    int numofdata;

    while (1)
    {
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Quick Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Radix Count Sort\n");
        printf("6. Count Sort\n");
        printf("7. Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &selection);
        
        if(selection==8)
        {
            
        }
        else if(selection==9)
        {

        }
        else if(selection==7)
        {
            break;
        }
        
        printf("Enter the number of a testdata: \n");
        scanf("%d", &numofdata);
        printf("Enter the sum of datas: \n");
        scanf("%d", &datas);

        FILE* fptr=fopen("result.txt","w+");
        fclose(fptr);

        clock_t start, end;
        double cpu_time_used;

        start = clock();
        for(int i=0;i<datas;i++)
        {
            test_sort(selection,numofdata);
        }
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Time taken: %f\n\n\n\n",cpu_time_used);

    }
  
}

