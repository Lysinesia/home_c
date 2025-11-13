#include <stdio.h>

int grow_up(int n)
{
    for (int prev = 10; n > 0; n /= 10)
    {
        int digit = n % 10;
        if (digit >= prev) return 0;
        prev = digit;
    }
    return 1;
}

int main() {
    int n; scanf("%d", &n); 
    printf(grow_up(n) ? "YES" : "NO"); 
    return 0;
}

