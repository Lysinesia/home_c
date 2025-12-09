#include <stdio.h>
#include <string.h>

void open_and_redact(char *letters, int *index, int *count)
{
	FILE *in;
	in = fopen("input.txt", "r");
	fgets(letters, 1002, in);
	fclose(in);
	
	size_t len = strlen(letters);
	if(len > 0 && letters[len-1] == '\n')
	{
		letters[len-1] = '\0';
		len--;
	}
	if(len > 0 && letters[len-1] == '\r')
	{
		letters[len-1] = '\0';
		len--;
	}
	char last_char = letters[len-1];
	*count = 0;
	
	for(int i = 0; i < len; i++)
	{
		if(letters[i] == last_char && i != len-1)
		{
			index[*count] = i;
			(*count)++;
		}
	}
}

void write_new_file(int *index, int count)
{
	FILE *out;
	out = fopen("output.txt", "w");
	for(int i = 0; i < count; i++) fprintf(out, "%d ", index[i]);

	fclose(out);
}


int main(int argc, char **argv)
{
	char letters[1002];
	int index[1000];
	int count = 0;
	
	open_and_redact(letters, index, &count);
	write_new_file(index, count);


	return 0;
}

