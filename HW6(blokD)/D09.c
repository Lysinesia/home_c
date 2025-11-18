#include <stdio.h>

int sum_digits(int n)
{
    if (n == 0) 
    {
        return 0;
    }
    
    return n % 10 + sum_digits(n / 10);
}

int main()
{
	int x;
	scanf("%d", &x);
	printf("%d", sum_digits(x));

	return 0;
}

