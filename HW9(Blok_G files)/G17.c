#include <stdio.h>
#include <string.h>

int main() 
{
    FILE *in, *out;
    char str[1001];
    char without_spaces[1001];
    int indices[1001];
    int count = 0;
    
    in = fopen("input.txt", "r");
    fgets(str, sizeof(str), in);
    fclose(in);
    
	str[strcspn(str, "\n")] = '\0';
	int len = strlen(str);
    
    for (int i = 0; i < len; i++)
    {
        if (str[i] != ' ')
        {
            without_spaces[count] = str[i];
            indices[count++] = i;
        }
    }

    for (int i = 0; i < count - 1; i += 2)
    {
        char temp = without_spaces[i];
        without_spaces[i] = without_spaces[i+1];
        without_spaces[i+1] = temp;
    }
    
    for (int i = 0; i < count; i++)
    {
        str[indices[i]] = without_spaces[i];
    }
    
    out = fopen("output.txt", "w");
    fprintf(out, "%s", str);
    fclose(out);
    
    return 0;
}
