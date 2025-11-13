#include <stdio.h>

int module_number(int x)
{
	return (x < 0) ? -x : x;
}
	

int main()
{
	int number;
	scanf("%d", &number);
	printf("%d", module_number(number));
	
	return 0;
}

