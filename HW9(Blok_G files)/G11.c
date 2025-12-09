#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() 
{
    FILE *in, *out;
    char str[1001];
    int result = 0;
    
    in = fopen("input.txt", "r");
    fgets(str, sizeof(str), in);
    fclose(in);
    
    int len = strlen(str);
    
     for (int i = 0; i <= len; i++)
    {
        if (i == len || !isalpha(str[i]))
        {
            if (i > 0 && isalpha(str[i - 1]))
            {
                char last_char = str[i - 1];
                if (last_char == 'a' || last_char == 'A') result++;
            }
        }
	}
    
    
    out = fopen("output.txt", "w");
    fprintf(out, "%d", result);
    fclose(out);
    
    return 0;
}
