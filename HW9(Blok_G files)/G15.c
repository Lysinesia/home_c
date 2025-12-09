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
		if(str[i] == 'C' && str[i+1] == 'a' && str[i+2] == 'o')
		{
			result_str[index++] = 'L';
			result_str[index++] = 'i';
			result_str[index++] = 'n';
			result_str[index++] = 'g';
			i += 3;
		}
		else result_str[index++] = str[i++];
	}
	result_str[index] = '\0';
	
	out = fopen("output.txt", "w");
	fprintf(out, "%s", result_str);
	fclose(out);
	
	
	
	return 0;
	
}

