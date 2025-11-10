#include <stdio.h>

int main()
{
	int x, flag = 1;
	scanf("%d", &x);
	
	while(x > 0)
	{
		int i = x % 10;
		if (i % 2 != 0)
		{
			flag = 0;
			break;
		}
		x /= 10;
	}
	printf(flag ? "YES" : "NO");
	return 0;
}

