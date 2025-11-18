#include <stdio.h>
#include <limits.h>

int max_find(int max) 
{
    int num;
    scanf("%d", &num);
    
    if (num == 0)
    {
        return max;
    }
    
    if (num > max)
    {
        return max_find(num);
    } 
      
    else
    {
        return max_find(max);
    }
}

int main() 
{
    int result = max_find(INT_MIN);
    printf("%d", result);
    return 0;
}
