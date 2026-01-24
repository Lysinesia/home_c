#include <stdio.h>

int main()
{
    long long N;
    scanf("%lld", &N);
    
    int result = 0;

    if (N > 797161) 
    {
        printf("-1\n");
        return 0;
    }

    while (N)
     {
        if (N % 3 == 2) 
        {
            result++;
            N = N / 3 + 1;
        } 
        else if (N % 3 == 1) 
        {
            result++;
            N = N / 3;
        } 
        else 
        {
            N = N / 3;
        }
    }
    printf("%d\n", result);
    return 0;
}