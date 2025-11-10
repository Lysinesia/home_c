#include <stdio.h>

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	
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
	printf("%d", a);
	return 0;
}

