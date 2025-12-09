#include <stdio.h>
#include <string.h>

int is_palindrome(char *in)
{
    int freq[26] = {0};
    for (int i = 0; in[i]; i++)
    {
        if (in[i] >= 'a' && in[i] <= 'z') freq[in[i] - 'a']++;
    }
    
    int odd = 0;
    
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] % 2 == 1) odd++;
    }
    return (odd <= 1);
}

int main()
{
    FILE *in;
    char str[1001];
    
    in = fopen("input.txt", "r");
    fgets(str, sizeof(str), in);
    fclose(in);
    
    str[strcspn(str, "\n")] = '\0';
    
    if (is_palindrome(str)) printf("YES\n");
    else printf("NO\n");

    
    return 0;
}
