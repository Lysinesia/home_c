#include <stdio.h>

int main()
{
	int x, result = 0;
	scanf("%d", &x);
	while (x > 0)
	{
		x /= 10;
		result ++;
	}
		if (result != 3)
		{
		printf("NO");
	}
		else
		{
		printf("YES");
	}
		
	return 0;
}

