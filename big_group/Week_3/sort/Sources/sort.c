#include "../Headers/sort.h"
#include <stdlib.h>

/*
    * Function to sort the array using bubble sort
    * @param arr: array to be sorted
    * @param n: size of the array
*/

void bubblesort(int *arr, int n)
{
    int i, j, temp;
    int flag=0;
    for (i = 0; i < n - 1; i++)
    {   
        flag=0;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {   
                flag=1;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        if (flag==0)
        {
            break;
        }

    }
}

/*
    * Function to sort the array using insertion sort
    * @param arr: array to be sorted
    * @param n: size of the array
*/
void insertsort(int *arr, int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/*
    * Function to sort the array using quick sort
    * @param arr: array to be sorted
    * @param l: left index of the array
    * @param r: right index of the array
*/

void quicksort(int *arr, int l, int r)
{
    if (l < r)
    {
        int pi = partition(arr, l, r);
        quicksort(arr, l, pi - 1);
        quicksort(arr, pi + 1, r);
    }
}


/*
    * Function to partition the array
    * @param arr: array to be partitioned
    * @param l: left index of the array
    * @param r: right index of the array
    * @return: the partition index
*/
int partition(int *arr, int l, int r)
{
    int pivot = arr[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;
    return i + 1;
}


/*
    * Function to sort the array using merge sort
    * @param arr: array to be sorted
    * @param l: left index of the array
    * @param r: right index of the array
*/
void mergesort(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merge(arr, l, m, r);
    }

}

/*
    * Function to merge the array
    * @param arr: array to be merged
    * @param l: left index of the array
    * @param m: middle index of the array
    * @param r: right index of the array
*/
void merge(int *arr, int l, int m, int r)
{   
    int* temp = (int*)malloc((r - l + 1) * sizeof(int));

    int i, j, k;
    i = l;
    j = m + 1;
    k = 0;
    while (i <= m && j <= r)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i <= m)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= r)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for (i = l; i <= r; i++)
    {
        arr[i] = temp[i-l];
    }

    free(temp);
}



/*
    * Function to sort the array using radix count sort
    * @param arr: array to be sorted
    * @param n: size of the array
*/
void radixcountsort(int *arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        count(arr, n, exp);
    }
}


void count(int *arr, int n, int exp)
{
    int *output=(int*)malloc(n*sizeof(int));
    int count[10] = {0};
    for (int i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
    free(output);
}


/*
    * Function to sort the array using count sort
    * @param arr: array to be sorted
    * @param n: size of the array
*/
void countsort(int *arr,int n)
{   
    int max=arr[0];

    for(int i=1;i<n;i++)
    {
        if(arr[i]>max)
        {
            max=arr[i];
        }
    }

    int *output=(int*)malloc(n*sizeof(int));
    int *count=(int*)malloc((max+1)*sizeof(int));

    for (int i = 0; i <= max; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }
    
    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }

    free(output);
    free(count);
}

/*
    * function to sort the array with 0s, 1s and 2s
    * @param arr: array to be sorted
    * @param n: size of the array
*/
void colorsort(int* arr,int n)
{   

    int low = 0, high = n - 1;

    for(int i=0;low<high;i++)
    {
        if(arr[i]==0)
        {
            int temp=arr[i];
            arr[i]=arr[low];
            arr[low]=temp;
            low++;
        }
        else if(arr[i]==2)
        {
            int temp=arr[i];
            arr[i]=arr[high];
            arr[high]=temp;
            high--;
        }
    }
}


/*
    * function to find the kth largest element in the array
    * @param arr: array to be sorted
    * @param n: size of the array
*/
int quickselect(int *nums, int l, int r, int k) 
{
    if (l == r)
        return nums[k];
    int partition = nums[l], i = l - 1, j = r + 1;
    while (i < j)
    {
        do 
            i++; 
        while (nums[i] < partition);
        do 
            j--; 
        while (nums[j] > partition);

        if (i < j) 
        {
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }
    if (k <= j)
        return quickselect(nums, l, j, k);
    else 
        return quickselect(nums, j + 1, r, k);
}

