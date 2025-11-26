#include <stdio.h>
#define SIZE 12
#define PARTS 3

void reverse_sec(int arr[], int START, int END)
{
	for(int i =0; i < (END - START + 1) / 2; i++)
	{
		int temp = arr[START + i];
		arr[START + i] = arr[END - i];
		arr[END - i] = temp;
	}
}

int main(int argc, char **argv)
{
	int arr[SIZE];
	int part_size = SIZE / PARTS; 
	
	for(int i =0; i < SIZE; i++) scanf("%d", &arr[i]);
	
	for(int i =0; i < PARTS; i++)
	{
		int START = i * part_size;
		int END = (i + 1) * part_size - 1;
		reverse_sec(arr, START, END); 
	}
	
	for(int i =0; i <SIZE; i++) printf("%d ", arr[i]);
	
	return 0;
}

