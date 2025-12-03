#include <stdio.h>

int find_max_array(int size, int arr[0])
{
	
	int max = arr[0];
	for(int i = 1; i < size; i++)
	{
		if (arr[i] > max) max = arr[i];
	}
	printf("%d", max);
	return max;
}

int main(int argc, char **argv)
{
	int size;
	scanf("%d", &size);
	int arr[size];
	for(int i = 0; i < size; i++) scanf("%d", &arr[i]);
	find_max_array(size, arr);
	
	return 0;
}

