#include <stdio.h>

int count_between(int from, int to, int size, int a[])
{
	int count = 0;
	
	for(int i = 0; i < size; i++)
	{
		if(a[i] >= from && a[i] <= to) count++;
	}
	return count;
}

int main(int argc, char **argv)
{
	int size;
	int from;
	int to;
	scanf("%d %d %d", &size, &from, &to);
	
	int arr[size];
	for(int i = 0; i < size; i++) scanf("%d", &arr[i]);
	
    int result = count_between(from, to, size, arr);
    printf("%d\n", result);
	
	return 0;
}

