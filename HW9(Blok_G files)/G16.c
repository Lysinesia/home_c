#include <stdio.h>
#include <string.h>

int main()
{
	FILE *in, *out;
	char str[1001];
	char result_str[2001];
	int index = 0;

	
	in = fopen("input.txt", "r");
	fgets(str, sizeof(str), in);
	fclose(in);
	
	str[strcspn(str, "\n")] = '\0';
	
	
	int len = strlen(str);
	
	for(int i = 0; i < len; )
	{
		if(str[i] == 'L' && str[i+1] == 'i' && str[i+2] == 'n' && str[i+3] == 'g')
		{
			result_str[index++] = 'C';
			result_str[index++] = 'a';
			result_str[index++] = 'o';
			i += 4;
		}
		else result_str[index++] = str[i++];
	}
	result_str[index] = '\0';
	
	out = fopen("output.txt", "w");
	fprintf(out, "%s", result_str);
	fclose(out);
	
	
	
	return 0;
	
}
