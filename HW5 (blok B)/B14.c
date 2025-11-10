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
		
		count ++;
	}
	printf("%d", count);
	return 0;
}

