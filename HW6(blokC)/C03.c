#include <stdio.h>

int middle(int a, int b)
{
	int result;
	return result = ((a+b) / 2);
}


int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d", middle(a, b));
	return 0;
}

