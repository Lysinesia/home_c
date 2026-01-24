#include <stdio.h>
#include <stdint.h>

int extractExp(float x) 
{
    union { float f; uint32_t u; } conv = {x};
    return (conv.u >> 23) & 0xFF;
}

int main() 
{
    float x;
    scanf("%f", &x);
    printf("%d\n", extractExp(x));
    return 0;
}