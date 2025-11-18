#include <stdio.h>

void print_digits(int n)
{
	if (n / 10 == 0)
	{
        printf("%d", n);
        return;
    }
    
    print_digits(n / 10);
    printf(" %d", n % 10);
}

int main()
{
	int n;
    scanf("%d", &n);
	print_digits(n);
 
	return 0;
}

