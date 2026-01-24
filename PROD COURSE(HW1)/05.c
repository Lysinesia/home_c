#include <stdio.h>

int main()
{
    unsigned int N = 0;
    unsigned int K = 0;
    scanf("%u %u", &N, &K);
    unsigned max_value = 0;
    unsigned int mask = (1u << K) - 1;

    for(int i = 0; i <= 32 - K; i++)
    {
        unsigned int bitz = (N >> i) & mask;
        if(bitz > max_value) max_value = bitz;
    }
printf("%u\n", max_value);
    return 0;
}