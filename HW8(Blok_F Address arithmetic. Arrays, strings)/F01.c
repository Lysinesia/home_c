#include <stdio.h>

void sort_array(int size, int a[])
{
	for(int i = 0; i < size - 1; i++)
	{
		for(int j = 0; j < size -i -1; j++)
		{
			if(a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}

int main (int argc, char **argv)
{
	int size = 0;
	scanf("%d", &size);
	int a[size];

	for(int i = 0; i < size; i++) scanf("%d", &a[i]);
	
	sort_array(size, a);

	for(int i = 0; i < size; i++) printf("%d ", a[i]);
	
	return 0;
	
}

