#include <stdio.h>
void recurs_sum1_to_N(int n, int sum)
{
	sum += n;
	
	if(n <= 0)
	{
		printf("%d ", sum);
		 return;
	 }	
	recurs_sum1_to_N(n - 1, sum);
}

int main()
{
	int x;
	int sum = 0;
	scanf("%d", &x);
	recurs_sum1_to_N(x, sum);
	return 0;
}



