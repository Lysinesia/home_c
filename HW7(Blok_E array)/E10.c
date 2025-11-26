#include <stdio.h>
#define SHIFT 4
#define SIZE 12

int main(int argc, char **argv)
{
	int arr[SIZE];
	int new_arr[SIZE];
	
	for(int i = 0; i < SIZE; i++) scanf("%d", &arr[i]);
	
	
	for(int i = 0; i < SIZE; i ++)
	{
		new_arr[(i + SHIFT) % SIZE] = arr[i]; 
	}
	
	
	for(int i = 0; i < SIZE; i++) printf("%d ", new_arr[i]);
	
	return 0;
}
