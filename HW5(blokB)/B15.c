#include <stdio.h>

int main()
{
	int x, count = 0;
	
	while(1)
	{
		scanf("%d", &x);
		
		if (x == 0)
		{
			break;
		}
		
		if(x % 2 == 0)
		{
			count ++;
		}
	}
	printf("%d", count);
	return 0;
}

