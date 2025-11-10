#include <stdio.h>

int main() 
{
    int x;
    scanf("%d", &x);
    
    for (int num = 10; num <= x; num++)
    {
        int temp = num;
        int sum = 0;
        int multiplication = 1;
        int flag_zero = 0;
          
        while (temp > 0)
        {
            int i = temp % 10;
            
            if (i == 0)
            {
                flag_zero = 1;
                break;
            }
            
            sum += i;
            multiplication *= i;
            temp /= 10;
        }
        
        if (!flag_zero && sum == multiplication)
        {
            printf("%d ", num);
        }
    }
    
    return 0;
}
