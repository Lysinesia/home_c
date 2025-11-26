#include <stdio.h>
#define SIZE 10

void calculate_sum_positiv(int arr[], int *sum)
{
	for(int i=0; i < SIZE; i++)
	{
		if(arr[i] > 0) *sum += arr[i];
	}
}

int main(int argc, char **argv)
{
	int arr[SIZE];
	int sum = 0;
	
	for(int i=0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}
	calculate_sum_positiv(arr, &sum);
	
	printf("%d", sum);
	return 0;
}
