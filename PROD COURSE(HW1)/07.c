#include <stdio.h>

int main()
{
    unsigned int N;
    unsigned int mask = 0xFF000000;
    scanf("%u", &N);
    N = N ^ mask;
    printf("%u", N);
    return 0;
}