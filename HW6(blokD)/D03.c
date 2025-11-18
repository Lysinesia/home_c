#include <stdio.h>
void recurs_numbers(int n)
{
    printf("%d ", n % 10);
    
    if (n / 10 != 0) 
    {
        recurs_numbers(n / 10);
    }
}

int main()
{
	int x;
	scanf("%d", &x);
	recurs_numbers(x);
	return 0;
}


