#include <stdio.h>

int main(int argc, char **argv)
{
	int x, i;
	scanf("%d", &x);
	
	if (x < 2)
	{
		printf("NO");
		return 0;
	}
	
	for(i = 2; i * i <= x; i ++)
	{
		if (x % i == 0)
		{
			printf("NO");
			return 0;
		}
	}
	
	printf("YES");
	return 0;
}

