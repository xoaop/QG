#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Headers/rand.h"


/*
    * Function to generate array of random numbers
    * @param size: size of the array
    * @param min: minimum value of the random number
    * @param max: maximum value of the random number
*/
int* generate_testdata(int size, int min, int max)
{
    int *arr = (int *)malloc(size * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++) 
    {   
        //@param (max - min) is the maximum value that can be generated 
        arr[i] = min + rand() % (max - min + 1);
    }
    return arr;
}

void save_data(int *arr, int size,char* filename,int c)
{
    FILE *fptr=NULL;

    if(c==0)
    {
        fptr=fopen(filename, "w+");
    }
    else
    {
        fptr=fopen(filename, "a+");
    }

    if(fptr==NULL)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(fptr, "%d ", arr[i]);
    }

    fclose(fptr);

    free(arr);

}

void generate_and_save(int size,int min,int max,char* filename,int c)
{   
    int *arr=generate_testdata(size,min,max);
    save_data(arr,size,filename,c);
}


int* read_data(int size,char* filename)
{
    FILE *fptr=NULL;
    fptr=fopen(filename, "r");

    if(fptr==NULL)
    {
        return NULL;
    }

    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        fscanf(fptr, "%d ", &arr[i]);
    }
    
    fclose(fptr);
    return arr;
}






