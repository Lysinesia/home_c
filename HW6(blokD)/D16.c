#include <stdio.h>

int degree(int n)
{
    if (n == 1) return 1;
    
    if (n % 2 != 0 || n == 0) return 0;

    return degree(n / 2);
}

int main()
{
    int n;
    scanf("%d", &n);
    
	printf(degree(n) ? "YES" : "NO");
    
    return 0;
}
