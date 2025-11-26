#include <stdio.h>
#define SIZE 10

int main(int argc, char **argv)
{
	int arr[SIZE];
	int arr2[SIZE];
	int count = 0;
	
	for(int i = 0; i < SIZE; i++) scanf("%d", &arr[i]);
	
	for(int i = 0; i < SIZE; i++)
	{
		int duplicate = 0;
		for(int j = 0; j < SIZE; j ++)
		{
			if( i != j && arr[i] == arr[j])
			{
				duplicate = 1;
				break;
			}
		}
			
		if(duplicate)
		{
			int is_in_the_arr2 = 0;
			for(int y = 0; y < count; y++)
			{
				if(arr2[y] == arr[i])
				{
					is_in_the_arr2 = 1;
					break;
				}
			}
				
			if(!is_in_the_arr2) arr2[count++] = arr[i];			
		}	
	}
	
	for(int i = 0; i < count; i++) printf("%d ", arr2[i]);
	return 0;
}

