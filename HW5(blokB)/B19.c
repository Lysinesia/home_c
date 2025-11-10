#include <stdio.h>

int main(int argc, char **argv)
{
	int x, flag = 1, count = 0;
	scanf("%d", &x);
	
	while (x > 0)
	{
		int i = x % 10;
		count += i;
		x /= 10;
	}
	if (count != 10)
	{
		flag = 0;
	}
	
	printf(flag ? "YES" : "NO");
	return 0;
}

