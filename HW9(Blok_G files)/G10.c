#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() 
{
    FILE *in, *out;
    char str[1001];
    
    in = fopen("input.txt", "r");
    fgets(str, sizeof(str), in);
    fclose(in);
    
    char longest[1001] = "";
    char current[1001];
    int max_len = 0;
    int cur_len = 0;
    int j = 0;
    
    int len = strlen(str);
    str[len] = ' ';
    str[len + 1] = '\0';
    
    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (isalpha(str[i])) 
        {
            current[j] = str[i];
            j++;
            cur_len++;
        }
        else 
        {
            if (cur_len > 0)
            {
                current[j] = '\0';
                
                if (cur_len > max_len) 
                {
                    max_len = cur_len;
                    strcpy(longest, current);
                }
                
                cur_len = 0;
                j = 0;
            }
        }
    }
    
    out = fopen("output.txt", "w");
    fprintf(out, "%s", longest);
    fclose(out);
    
    return 0;
}
