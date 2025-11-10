#include <stdio.h>

int main()
{
	int x, max = 0, min = 9;
	scanf("%d", &x);
	
	while (x > 0)
	{
		int i = x % 10;
		
		if (i < min)
		{
			min = i;
		}
		
		if(i > max)
		{
			max = i;
		}
		
		x /= 10;
	}
	printf("%d %d", min, max);
	return 0;
}

