#include <stdio.h>

void print_simple(int n)
{
	for(int i = 2; n > 1; i++)
	{
		while (n % i == 0)
		{
			printf("%d ", i);
			n /= i;
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	print_simple(n);
	
	return 0;
}

