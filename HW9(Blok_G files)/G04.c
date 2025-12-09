#include <stdio.h>
#include <string.h>

int main(void)
{
	FILE *in, *out;
	char word1[101];
	char word2[101];
	int count1[26] = {0};
	int count2[26] = {0};
	int index;
	
	in = fopen("input.txt", "r");
	fscanf(in, "%s %s", word1, word2);
	fclose(in);
	
	for(int i = 0; word1[i] != '\0'; i++) count1[word1[i] - 'a']++;
	for(int i = 0; word2[i] != '\0'; i++) count2[word2[i] - 'a']++;
	
	out = fopen("output.txt", "w");
	int first = 1;
	for(char i = 'a'; i <= 'z'; i++) 
	{
		index = i - 'a';
		if(count1[index] == 1 && count2[index] == 1)
		{
			if(!first) fprintf(out, " ");
			
			fprintf(out, "%c", i);
			first = 0;
		}
	}
	fclose(out);

	return 0;
}
