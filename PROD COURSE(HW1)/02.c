#include <stdio.h>

int main()
{

    int N = 0;
    int c;
    scanf("%d", &N);
    while ((c = getchar()) != '.')
    {
        if(c == ' ') putchar(' ');
        else if(c >= 'a' && c <= 'z') putchar('a' + (c - 'a' + N) % 26);
        else if(c >= 'A' && c <= 'Z') putchar('A' + (c - 'A' + N) % 26);
    }
    putchar('.');
    return 0;
}
