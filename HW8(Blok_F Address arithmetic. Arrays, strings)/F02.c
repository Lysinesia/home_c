#include <stdio.h>

void sort_even_odd(int n, int a[])
{
	int per_index = 0;
	for(int i = 0; i < n; i++)
	{
		if(a[i] % 2 == 0)
		{
			int temp = a[i];
			
			for(int j = i; j > per_index; j--)
			{
				a[j] = a[j - 1];
			}
			
			a[per_index] = temp;
			per_index++;
		}
	}
}

int main(int argc, char **argv)
{
	int size = 0;
	scanf("%d", &size);
	int a[size];
	
	for(int i = 0; i < size; i++) scanf("%d", &a[i]);
	
	sort_even_odd(size, a);
	
	for(int i = 0; i < size; i++) printf("%d ", a[i]);
	
	return 0;
}

