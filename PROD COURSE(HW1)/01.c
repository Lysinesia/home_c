#include <stdio.h>

int main()
{
    int N = 0;
    scanf("%d", &N);
    int max = 0;
    int count = 0;

    if(N > 0)
    {
        scanf("%d", &max);
        count = 1;
    }

    for(int i = 0; i < N - 1; i++)
    {
        int curent = 0;
        scanf("%d", &curent);
        if(curent > max)
        {
            max = curent;
            count = 1;
        }
        else if(curent == max) count++;
    }
    printf("%d\n", count);
    return 0;
}