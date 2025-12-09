#include <stdio.h>
#include <string.h>

void removeSpaces(char *input, char *output)
{
    int i = 0;
    int j = 0;
    
    while (input[i] == ' ') i++;
    
    while (input[i] != '\0')
    {
        if (input[i] != ' ') output[j++] = input[i];
        else
        {
            if (j > 0 && output[j-1] != ' ') output[j++] = ' ';
        }
        i++;
    }
	output[j] = '\0';
}

int main()
{
    FILE *in, *out;
    char str[1001];
    char str2[1001];
    
    in = fopen("input.txt", "r");
    fgets(str, sizeof(str), in);
    fclose(in);
    
    str[strcspn(str, "\n")] = '\0';
    removeSpaces(str, str2);
    
    out = fopen("output.txt", "w");
    fprintf(out, "%s", str2);
    fclose(out);
    
    return 0;
}
