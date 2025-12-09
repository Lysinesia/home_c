#include <stdio.h>
#include <string.h>

void Palindrome(char *in, char *out)
{
    int freq[26] = {0};

    for (int i = 0; in[i]; i++) freq[in[i] - 'a']++;
 
    char left[501];
    int left_len = 0;
    char center = 0;

    for (int i = 0; i < 26; i++)
    {
        while (freq[i] >= 2)
        {
            left[left_len++] = 'a' + i;
            freq[i] -= 2;
        }
        if (freq[i] == 1 && !center) center = 'a' + i;
    }  
    int pos = 0;
    
    for (int i = 0; i < left_len; i++) out[pos++] = left[i];
 
    if (center) out[pos++] = center;

    for (int i = left_len - 1; i >= 0; i--) out[pos++] = left[i]; 
    out[pos] = '\0';
}

int main()
{
    FILE *in, *out;
    char str[1001];
    char palind[1001];
    
    in = fopen("input.txt", "r");
    fgets(str, sizeof(str), in);
    fclose(in);
  
    str[strcspn(str, "\n")] = '\0';
    Palindrome(str, palind);
    
    out = fopen("output.txt", "w");
    fprintf(out, "%s", palind);
    fclose(out);
    
    return 0;
}
