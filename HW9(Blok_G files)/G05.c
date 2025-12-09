#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *in, *out;
	char str[1001];
	
	in = fopen("input.txt", "r");
	fgets(str, sizeof(str), in);
	fclose(in);
	
	for(int i = 0; str[i] != '\0'; i++)
	{
		switch(str[i])
		{
			case 'a': str[i] = 'b'; break;
			case 'b': str[i] = 'a'; break;
			case 'A': str[i] = 'B'; break;
			case 'B': str[i] = 'A'; break;
		}
	}
	
	out = fopen("output.txt", "w");
	fprintf(out, "%s", str);
	fclose(out);
	
	return 0;
}

