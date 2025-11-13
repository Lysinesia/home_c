#include <stdio.h>

int convert(int n, int p) 
{
    int result = 0;
    int multiplier = 1;
    
    while (n > 0) 
    {
        int digit = n % p;     
        result += digit * multiplier;  
        multiplier *= 10;      
        n /= p;                 
    }
    
    return result;
}

int main() 
{
    int n, p;
    scanf("%d %d", &n, &p);
    printf("%d", convert(n, p));
    
    return 0;
}
