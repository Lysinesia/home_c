#include <stdio.h>
#define SIZE 12

void calculate_sr_arif(int arr[], float *sum)
{
	for(int i=0; i < SIZE; i++)
	{
		*sum += arr[i];
	}
}

int main(int argc, char **argv)
{
	int arr[SIZE];
	float sum = 0;
	
	for(int i=0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}
	calculate_sr_arif(arr, &sum);
	
	printf("%.2f", sum / SIZE);
	return 0;
}
