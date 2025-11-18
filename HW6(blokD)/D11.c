#include <stdio.h>

int sum_number(int x)
{
	if(x == 0) return 0;
	return (x % 2) + sum_number(x / 2);
}

int main()
{
	int x;
	scanf("%d", &x);
	printf("%d", sum_number(x));
	return 0;
}

