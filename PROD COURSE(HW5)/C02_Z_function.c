#include <stdio.h>
#include <string.h>

#define MAX_LEN 10004

int main() 
{
    char s1[MAX_LEN], s2[MAX_LEN];
    
    fgets(s1, MAX_LEN, stdin);
    fgets(s2, MAX_LEN, stdin);

    s1[strcspn(s1, "\n")] = '\0';
    s2[strcspn(s2, "\n")] = '\0';
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    int result1 = 0, result2 = 0;
    
    for (int len = 1; len <= len1 && len <= len2; len++) 
    {
        int ok = 1;

        for (int i = 0; i < len; i++) 
        {
            if (s1[i] != s2[len2 - len + i]) 
            {
                ok = 0;
                break;
            }
        }
        if (ok && len > result1) 
        {
            result1 = len;
        }
    }
    
    for (int len = 1; len <= len1 && len <= len2; len++) 
    {
        int ok = 1;
        for (int i = 0; i < len; i++) {
            if (s1[len1 - len + i] != s2[i]) 
            {
                ok = 0;
                break;
            }
        }
        if (ok && len > result2) 
        {
            result2 = len;
        }
    }
    
    printf("%d %d\n", result1, result2);
    
    return 0;
}