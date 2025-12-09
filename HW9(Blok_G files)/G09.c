#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *in, *out;
	char str[1001];
	char str2[1001];
	int str2_index = 0;

	
	in = fopen("input.txt", "r");
	fgets(str, sizeof(str), in);
	fclose(in);
	
	int len = strlen(str);
	
	for(int i = 0; i < len; i++)
	{
		if(str[i] == ' ') continue;
	
		int duble = 0;
		for(int j = 0; j < str2_index; j++)
		{
			if(str2[j] == str[i])
			{
				duble = 1;
				break;
			}
		}
	
		if(!duble)
		{
			str2[str2_index] = str[i];
			str2_index++;
		}
	}
	
	str2[str2_index] = '\0';
		
	
	out = fopen("output.txt", "w");
	fprintf(out, "%s", str2);
	fclose(out);
	return 0;
}
