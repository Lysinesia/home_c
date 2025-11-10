#include <stdio.h>

int main()
{
	int x, counter = 0;
	scanf("%d", &x);
	while(x > 0)
	{
		int i = x % 10;
		if (i == 9)
		{
			counter ++;
		}
		x /= 10;
	}
	if (counter == 1)
	{
		printf("YES");
	}
	else 
	{
		printf("NO");
	}
	return 0;
}

