#include <stdio.h>

int factorial(int n)
{
	int result = 1;
	while(n > 0)
	{
		result *=n;
		n--;
	 }
	return result;
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d", factorial(n));
	
	return 0;
}

