#include <stdio.h>

int main(int argc, char **argv)
{
	int x, max = 10;
	scanf("%d", &x);
	
	while (x > 0)
	{
		int i = x % 10;
		
		if (i >= max)
		{
			printf("NO");
			return 0;
		}
		
		max = i;
		x /= 10;
	}
	
	printf("YES");
		
	return 0;
}

