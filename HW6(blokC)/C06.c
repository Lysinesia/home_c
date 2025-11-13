#include <stdio.h>

unsigned long long quantity(int x)
{
	int point_chek = 1;
	unsigned long long sum = 1;
	while(point_chek < x)
	{
		sum *= 2;
		point_chek++;
	}
	return sum;
}
	

int main()
{
	int point;
	scanf("%d", &point);
	printf("%llu", quantity(point));
	return 0;
}

