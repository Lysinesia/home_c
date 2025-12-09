#include <stdio.h>

int main()
{
    FILE *in, *out;
    
    int stars = 0;
    char c;
   
    in = fopen("input.txt", "r");
    while ((c = fgetc(in)) != EOF)
    {
        if (c == '*') stars++;
    }
    fclose(in);
    
    
    int n = 0;
    int sum = 0;
    while (sum < stars)
    {
        n++;
        sum = n * (n + 1) / 2;
    }
    
    out = fopen("output.txt", "w");
    if (sum != stars || stars == 0) fprintf(out, "NO");
    else
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < n - i; j++) fputc(' ', out);

            for (int j = 0; j < i; j++)
            {
                fputc('*', out);
                if (j < i - 1) fputc(' ', out);
            }
            if (i < n) fputc('\n', out);
        }
    }
    fclose(out);
    return 0;
}
