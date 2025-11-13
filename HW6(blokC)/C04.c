#include <stdio.h>

int f(int x)
{
	return x >= 2 ? x*x+4*x+5 : (x >= -2 ? x*x : 4);
}
int main()
{
	int x, max = -1;
	
	while (scanf("%d", &x) == 1 && x != 0)
	{
		int value = f(x);
		if (value > max) max = value;
	}
	printf("%d", max);
	return 0;
}

