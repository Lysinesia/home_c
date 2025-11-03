#include <stdio.h>
int main()
{
	int value, a, b, c, max;
	scanf("%d", &value);
	a = (value/100);
	b = (value/10%10);
	c = (value%10);
	
	if (a > b && a > c) {
	max = a;
} else if (b > a && b > c) {
	max = b;
} else {
	max = c;
}
	printf("%d", max);
	
	return 0;
}
	


