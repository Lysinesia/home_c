#include <stdio.h>
#include <string.h>

int main() 
{
    char s[1000001];
    scanf("%s", s);
    int len = strlen(s);
    
    int s1[10] = {0};
    int s2[100] = {0};
    int s3[1000] = {0};
    
    for (int i = 0; i < len; i++) 
    {
        int d = s[i] - '0';
        for (int num = 0; num < 100; num++) 
        {
            if (s2[num]) 
            {
                int new_num = num * 10 + d;
                s3[new_num] = 1;
            }
        }

        for (int num = 0; num < 10; num++) 
        {
            if (s1[num]) 
            {
                int new_num = num * 10 + d;
                s2[new_num] = 1;
            }
        }
        s1[d] = 1;
    }

    int count = 0;
    for (int num = 100; num <= 999; num++) 
    {
        if (s3[num]) count++;
    }
    printf("%d\n", count);
    return 0;
}