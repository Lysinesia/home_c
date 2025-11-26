#include <stdio.h>
#define SIZE 10

int main(int argc, char **argv)
{
    int arr[SIZE];
    for(int i = 0; i < SIZE; i++) scanf("%d", &arr[i]);
    
    int midle = SIZE / 2;
    
    
    for(int i = 0; i < midle - 1; i++)
    {
        for(int j = 0; j < midle - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    for(int i = 0; i < midle - 1; i++)
    {
        for(int j = midle; j < SIZE - i - 1; j++)
        {
            if(arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    for(int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    
    return 0;
}

