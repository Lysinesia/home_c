#include <stdio.h>

void print_seq(int num, int count, int total, int n) 
{

    if (total >= n) return;

    printf("%d ", num);
    
    total++;
    
    if (count + 1 >= num) 
    {
        print_seq(num + 1, 0, total, n);    
    }
    
    else 
    {
        print_seq(num, count + 1, total, n);
    }
}

int main() 
{
    int n;
    scanf("%d", &n);
    
    print_seq(1, 0, 0, n);
    
    return 0;
}

