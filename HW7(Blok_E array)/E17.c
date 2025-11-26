#include <stdio.h>
#define SIZE 10

int main()
{
    int arr[SIZE];
    int arr2[SIZE];
    int count = 0;
    
    for(int i = 0; i < SIZE; i++) scanf("%d", &arr[i]);


     for(int i = 0; i < SIZE; i++)
    {
        int is_unique = 1;
        
        for(int j = 0; j < SIZE; j++)
        {
            if( i != j && arr[i] == arr[j])
            {
                is_unique = 0;
                break;
            }
        }

        if(is_unique)
        {
            arr2[count++] = arr[i];
        }
    }

    for(int i = 0; i < count; i++) printf("%d ", arr2[i]);
    return 0;
}
