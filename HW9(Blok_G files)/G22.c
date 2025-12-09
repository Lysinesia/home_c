#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *in, *out;
    
    char word[21];
    in = fopen("input.txt", "r");
    fscanf(in, "%s", word);
    fclose(in);
    
    char soundex[5] = {word[0], '0', '0', '0', '\0'};
    int idx = 1;
    int prev_code = 0;
    
    for (int i = 1; word[i] != '\0' && idx < 4; i++)
    {
        char c = tolower(word[i]);
        int code = 0;
        
        if (c == 'b' || c == 'f' || c == 'p' || c == 'v') code = 1;
        else if (c == 'c' || c == 'g' || c == 'j' || c == 'k' || c == 'q' || c == 's' || c == 'x' || c == 'z') code = 2;
        else if (c == 'd' || c == 't') code = 3;
        else if (c == 'l') code = 4;
        else if (c == 'm' || c == 'n') code = 5;
        else if (c == 'r') code = 6;
        
        if (code != 0 && code != prev_code)
        {
            soundex[idx] = '0' + code;
            idx++;
            prev_code = code;
        } 
	}

	out = fopen("output.txt", "w");
    fprintf(out, "%s", soundex);   
    fclose(out);
    
    return 0;
}
