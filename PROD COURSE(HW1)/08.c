#include <stdio.h>
int main()
{
    unsigned int N;
    unsigned int result = 0;
    scanf("%u", &N);

    for(int i = 0; i < N; i++)
    {
        unsigned int K;
        scanf("%u", &K);
        result = result ^ K;
    }
    printf("%u", result);
    return 0;
}