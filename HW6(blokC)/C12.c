#include <stdio.h>
#include <math.h>

float sinus(float x) 
{
    float rad = x * M_PI / 180.0;
    
    float result = 0.0;
    float term = rad;  
    int n = 1;         
    
    for (int i = 1; fabs(term) > 0.001; i += 2) 
    {
        result += term;
        term = -term * rad * rad / ((i + 1) * (i + 2));
        n += 2;
    }
    return result;
}

int main() {
    float x;
    scanf("%f", &x);
    printf("%.3f\n", sinus(x));
    return 0;
}
