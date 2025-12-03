#include <stdio.h>

void change_max_min(int size, int a[])
{
	int max = 0;
	int min = 0;
	
	for(int i = 1; i < size; i++)
	{
		if(a[i] > a[max]) max = i;
		if(a[i] < a[min]) min = i;
	}
	
	int temp = a[max];
	a[max] = a[min];
	a[min] = temp;
}

int main(int argc, char **argv)
{
	int size;
	scanf("%d", &size);
	int arr[size];
	for(int i = 0; i < size; i++) scanf("%d", &arr[i]);
	
	change_max_min(size, arr);
	
	for(int i = 0; i < size; i++) printf("%d ", arr[i]);
	
	return 0;
}

