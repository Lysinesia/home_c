#include <stdio.h>
#define SIZE 10

int main()
{
    int arr[SIZE];
    
    for(int i = 0; i < SIZE; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    int most_frequent = arr[0];
    int max_count = 1;
    
    for(int i = 0; i < SIZE - max_count; i++)
    {
        int current_count = 1;
        
        for(int j = i + 1; j < SIZE; j++)
        {
            if(arr[j] == arr[i])
            {
				current_count++;
			}
        }
        
        if(current_count > max_count)
        {
            max_count = current_count;
            most_frequent = arr[i];
            
            if(max_count > SIZE / 2)
            {
				break;
			}
        }
    }
    
    printf("%d", most_frequent);
    return 0;
}
