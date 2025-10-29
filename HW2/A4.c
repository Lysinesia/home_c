#include <stdio.h>

int main()
{
	int a, b, c, d, x;
	scanf("%d%d%d", &a, &b, &c);
	d = a + b + c;
	x = a * b * c;
	printf("%d+%d+%d=%d\n%d*%d*%d=%d", a, b, c, d, a, b, c, x);
	return 0;
}

