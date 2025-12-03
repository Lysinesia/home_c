#include <stdio.h>

int sum_between_ab(int from, int to, int size, int a[])
{
	int sum = 0;
	if(from > to)
	{
		int temp = from;
		from = to;
		to = temp;
	}

	
	for(int i = 0; i < size; i++)
	{
		if(a[i] >= from && a[i] <= to)
		{
			sum += a[i];
		}
	}
	return sum;
}

int main(int argc, char **argv)
{
	int size;
	int from;
	int to;
	scanf("%d %d %d", &size, &from, &to);
	
	int arr[size];
	for(int i = 0; i < size; i++) scanf("%d", &arr[i]);
	
    int result = sum_between_ab(from, to, size, arr);
    printf("%d\n", result);
	
	return 0;
}
