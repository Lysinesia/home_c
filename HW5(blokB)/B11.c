#include <stdio.h>

int main()
{
	int x, rev = 0;
	scanf("%d", &x);
	
	while(x > 0)
	{
		int i = x % 10;
		rev = rev * 10 + i;
		x /= 10;
	}
	printf("%d", rev);
	return 0;
}

