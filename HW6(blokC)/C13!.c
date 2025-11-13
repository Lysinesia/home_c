#include <stdio.h>
#include <math.h>

float cosinus(float x) 
{
    float rad = x * M_PI / 180.0;
    
    float result = 1.0; 
    float term = 1.0;
    int n = 2;
    
    for (int i = 2; fabs(term) > 0.001; i += 2) 
    {
        term = -term * rad * rad / (i * (i - 1));
        result += term;
        n += 2;
    } 
    return result;
}

int main() {
    float x;
    scanf("%f", &x);
    printf("%.3f\n", cosinus(x));
    return 0;
}
