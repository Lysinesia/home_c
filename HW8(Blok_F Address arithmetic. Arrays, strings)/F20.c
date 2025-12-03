#include <stdio.h>

int product_digits(int n, int parity)
{
    int num = (n < 0) ? -n : n;
    int product = 1;
    int has_digits = 0;
    
    while (num > 0) {
        int digit = num % 10;
        if ((digit % 2 == 0 && parity == 0) || (digit % 2 != 0 && parity == 1))
        {
            product *= digit;
            has_digits = 1;
        }
        num /= 10;
    }
    return has_digits ? product : 0;
}

int main()
{
    int arr[10];

    for (int i = 0; i < 10; i++) scanf("%d", &arr[i]);
    
    int even_count = 0, odd_count = 0;
    for (int i = 0; i < 10; i++) 
    {
        if (arr[i] % 2 == 0) even_count++;
        else odd_count++;
    }
    
    if (even_count > odd_count) 
    {
        for (int i = 0; i < 10; i++) 
        {
            if (arr[i] % 2 != 0) 
            {
                arr[i] = product_digits(arr[i], 1);
            }
        }
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (arr[i] % 2 == 0)
            {
                arr[i] = product_digits(arr[i], 0);
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}
