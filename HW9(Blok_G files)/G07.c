#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *in, *out;
	char str[10001];
	int count_small = 0;
	int count_big = 0;
	
	in = fopen("input.txt", "r");
	fgets(str, sizeof(str), in);
	fclose(in);
	
	for(int i = 0; str[i] != '\0'; i++)
	{
		if(str[i] >= 'a' && str[i] <= 'z') count_small++;
		else if(str[i] >= 'A' && str[i] <= 'Z') count_big++;
	}
	
	out = fopen("output.txt", "w");
	fprintf(out, "%d %d", count_small, count_big);
	fclose(out);
	return 0;
}

