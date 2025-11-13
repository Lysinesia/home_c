#include <stdio.h>
int sum(int x)
{
	return x * (x + 1) / 2;
}
int main()
{
	int x;
	scanf("%d", &x);
	printf("%d", sum(x));
	return 0;
}
