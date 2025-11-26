#include <stdio.h>
#define SIZE 5

int calculate_min(int arr[])
{
	int min = arr[0];
	for(int i=1; i < SIZE; i++)
	{
		if(arr[i] < min) min = arr[i];
	}
	return min;
}
		

int main(int argc, char **argv)
{
	int arr[SIZE];
	for(int i=0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	int min = calculate_min(arr);
	
	printf("%d", min);
	return 0;
}

