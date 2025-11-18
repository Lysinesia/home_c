#include <stdio.h>

void easy_multiplier(int n, int base_multiplier)
{
    if (n <= 1)
    {
        return;
    }
    
    if (n % base_multiplier == 0) {
        printf("%d ", base_multiplier);
        easy_multiplier(n / base_multiplier, base_multiplier);
    }
    else 
    {
        easy_multiplier(n, base_multiplier + 1);
    }
}

int main()
{
    int n;
    int base_multiplier = 2;
    scanf("%d", &n);
    easy_multiplier(n, base_multiplier);
    return 0;
}
