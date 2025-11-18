#include <stdio.h>

void recursion_N_to_1(int x)
{
	
	if (x <= 0) return;
	printf("%d ", x);
	recursion_N_to_1(x-1);
	
}

int main()
{
	int x;
	scanf("%d", &x);
	recursion_N_to_1(x);
	return 0;
}

