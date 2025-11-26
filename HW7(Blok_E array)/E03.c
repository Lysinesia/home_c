#include <stdio.h>
#define SIZE 10

void calculate_min_max(int arr[], int *min, int *max)
{
	*min = 0;
	*max = 0;
	for(int i=1; i < SIZE; i++)
	{
		if(arr[i] < arr[*min]) *min = i;
		if(arr[i] > arr[*max]) *max = i;
	}
}
		

int main(int argc, char **argv)
{
	int arr[SIZE];
	int min;
	int max;
	
	for(int i=0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	calculate_min_max(arr, &min, &max);
	
	printf("%d %d %d %d", max+1, arr[max], min+1, arr[min]);
	return 0;
}

