#include <stdio.h>
#define SIZE 10

void calculate_sum_two_max(int arr[], int *max1, int *max2)
{
	if(arr[0] > arr[1])
	{
		*max1 = arr[0];
		*max2 = arr[1];
	}
	else
	{
		*max1 = arr[1];
		*max2 = arr[0];
	}

	for(int i=2; i < SIZE; i++)
	{
		if(arr[i] > *max1)
		{
			*max2 = *max1;
			*max1 = arr[i];
		}
		else if(arr[i] > *max2)
		{
			*max2 = arr[i];
		}
	}
}
		

int main(int argc, char **argv)
{
	int arr[SIZE];
	int max1;
	int max2;
	
	for(int i=0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	calculate_sum_two_max(arr, &max1, &max2);
	
	printf("%d", max1 + max2);
	return 0;
}
