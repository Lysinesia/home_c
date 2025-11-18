#include <stdio.h>

void binary_recursion(int num)
{
	if(num <= 0) return;
	
	binary_recursion(num / 2);
	
	printf("%d", num % 2);
}

int main()
{
	int x;
	
	scanf("%d", &x);
	
	if(x == 0) printf("%d", x);
	else binary_recursion(x);
	
	return 0;
}
