#include <stdio.h>

int nod(int a, int b)
{
	if (a < b)
	{
		int i = a;
		a = b;
		b = i;
	}
	
	while(b != 0)
	{
		int i = a % b;
		a = b;
		b = i;
	}
	return a;
}

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d", nod(a, b));
	return 0;
}
