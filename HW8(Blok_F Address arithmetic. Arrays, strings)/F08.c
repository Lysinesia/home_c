#include <stdio.h>

int main() 
{
    int num, min = 1001, max = 0, sum = 0, count = 0;
    
    while (scanf("%d", &num) && num != 0)
    {
        sum += num;
        count++;
        if (num < min) min = num;
        if (num > max) max = num;
    }

    int sum_min_to_max = (min + max) * (max - min + 1) / 2;
    
	if (sum == sum_min_to_max) printf("%d\n", (min == 1) ? max + 1 : min - 1);
    
	else printf("%d\n", sum_min_to_max - sum);
    
    return 0;
}

