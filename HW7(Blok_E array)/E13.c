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
		if((arr[i] / 10) % 10 == 0)
		{
			arr2[count] = arr[i];
			count++;
		}
	}
	
	for(int i = 0; i < count; i++) printf("%d ", arr2[i]);
	return 0;
}

