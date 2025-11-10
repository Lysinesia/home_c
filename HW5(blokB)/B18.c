#include <stdio.h>

int main()
{
	int limit, a = 0, b = 1;
	scanf("%d", &limit);
	
	for(int i = 0; i < limit; i ++)
	{
		printf("%d", b);
		if (i < limit -1)
		{
			printf(" ");
		}
		int temp = a + b;
		a = b;
		b = temp;
	}
	
	return 0;
}

