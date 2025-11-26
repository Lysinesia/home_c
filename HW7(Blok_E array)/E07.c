#include <stdio.h>
#define SIZE 10

void reverse_sec(int arr[], int start, int end)
{
    for(int i = 0; i < (end - start + 1) / 2; i++)
    {
        int temp = arr[start + i];
        arr[start + i] = arr[end - i];
        arr[end - i] = temp;
    }
}

int main()
{
    int arr[SIZE];
    
    for(int i = 0; i < SIZE; i++) scanf("%d", &arr[i]);
    
    reverse_sec(arr, 0, SIZE/2 - 1);
    reverse_sec(arr, SIZE/2, SIZE - 1);
    
    for(int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    
    return 0;
}

