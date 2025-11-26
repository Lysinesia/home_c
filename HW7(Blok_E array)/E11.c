#include <stdio.h>
#define SIZE 10
int main(int argc, char **argv)
{
	int arr[SIZE];
	for(int i =0; i < SIZE; i++) scanf("%d", &arr[i]);
	
	
	for(int i =0; i < SIZE -1; i++)
	{
		for(int j =0; j < SIZE -i -1; j++)
		{
			if(arr[j] % 10 > arr[j + 1] % 10)
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	
	for(int i =0; i < SIZE; i++) printf("%d ", arr[i]);
	
	return 0;
}

