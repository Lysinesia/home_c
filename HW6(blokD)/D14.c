#include <stdio.h>

void numbers() 
{
    int num;
    scanf("%d", &num);
    
    if (num == 0) return;
    
    if (num % 2 != 0) 
    {
        printf("%d ", num);
    }
    
    numbers();
}

int main() 
{
    numbers();
    return 0;
}
