#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_palindrom(char *str)
{
	int len = strlen(str);
	
	for(int i = 0; i < len/2; i++)
	{
		if(str[i] != str[len - 1 - i]) return 0;
	}
	return 1;
}

int main(void)
{
	FILE *in, *out;
	char str[1001];
	
	in = fopen("input.txt", "r");
	fgets(str, sizeof(str), in);
	fclose(in);
	
	str[strcspn(str, "\n")] = '\0';
	
	out = fopen("output.txt", "w");
	if(is_palindrom(str)) fprintf(out, "YES");
	else fprintf(out, "NO");
	fclose(out);
	
	return 0;
}

