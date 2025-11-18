#include <stdio.h>
void recurs1_to_N(int n)
{
	if(n <= 0) return;
	
	recurs1_to_N(n - 1);
	printf("%d ", n);
}

int main()
{
	int x;
	scanf("%d", &x);
	recurs1_to_N(x);
	return 0;
}

