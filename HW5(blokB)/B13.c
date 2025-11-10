#include <stdio.h>

int main()
{
	int x, even = 0, not_even = 0;
	scanf("%d", &x);
	
	while(x > 0)
	{
		int i = x % 10;
		
		if (i % 2 != 0)
		{
			not_even ++;
		}
		else
		{
			even ++;
		}
	
		x /= 10;
	}
	printf("%d %d", even, not_even);
	return 0;
}

