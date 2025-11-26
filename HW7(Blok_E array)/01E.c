#include <stdio.h>
#define SIZE 5

float calculate_average(int arr[])
{
	int sum = 0;
	for(int i=0; i < SIZE; i++)
	{
		sum += arr[i];
	}

    
    return (float)sum / SIZE;
}

int main(int argc, char **argv)
{
	int arr[SIZE];
	
	for(int i=0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	float average = calculate_average(arr);
	printf("%.3f", average);
	
	
    return 0;
}
