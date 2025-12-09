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
    
    int len = strlen(str);
    
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
        len--;
    }
    
    out = fopen("output.txt", "w");
    
    int i = 0;
    while (i < len) 
    {
        while (i < len && str[i] == ' ') i++;
        
        while (i < len && str[i] != ' ') 
        {
            fputc(str[i], out);
            i++;
        }  
        if (i < len) fputc('\n', out);
    }
    
    fclose(out);
    
    return 0;
}
