#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() 
{
    FILE *in, *out;   
    char str[1001];
    
    in = fopen("input.txt", "r");
    fgets(str, 1000, in);
    fclose(in);
    
    int numbers[500];
    int num_count = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) 
    {
        if (isdigit(str[i])) 
        {
            int num = 0;
            
            while (i < len && isdigit(str[i]))
            {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            
            numbers[num_count] = num;
            num_count++;
            i--;
        }
    }
    
    for (int i = 0; i < num_count - 1; i++) 
    {
        for (int j = 0; j < num_count - i - 1; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
    
    out = fopen("output.txt", "w");
    for (int i = 0; i < num_count; i++)
    {
        fprintf(out, "%d", numbers[i]);
        if (i < num_count - 1) fprintf(out, " ");
    }
    fclose(out);
    
    return 0;
}
