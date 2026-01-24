#include <stdio.h>

int main()
{
    unsigned int N;
    scanf("%u", &N);
    int count = 0;
    
    while(N)
    {
        N &= (N - 1);
        count++;
    }
    printf("%d\n", count);
    return 0;
}