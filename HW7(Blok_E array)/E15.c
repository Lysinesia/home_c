#include <stdio.h>
#define SIZE 10

int main(int argc, char **argv)
{
	int arr[SIZE];
	int arr2[SIZE];
	int positiv_count = 0;
	int negativ_count = 0;
	
	for(int i = 0; i < SIZE; i++)
	{
		int temp;
		scanf("%d", &temp);
		
		if(temp > 0 && temp < 500) arr[positiv_count ++] = temp;
		if(temp < 0 && temp > -500) arr2[negativ_count ++] = temp;
	}
	

	for(int i = 0; i < positiv_count; i++) printf("%d ", arr[i]);
	for(int i = 0; i < negativ_count; i++) printf("%d ", arr2[i]);
	return 0;
}

