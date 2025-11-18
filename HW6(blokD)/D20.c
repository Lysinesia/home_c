#include <stdio.h>

int recurs_power(int n, int p)
{
   return p == 0 ? 1 : n * recurs_power(n, p - 1);
   
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p);
    
    printf("%d", recurs_power(n, p));
    
    return 0;
}
