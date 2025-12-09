#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *in, *out;
	int N;
	char letter = 'A';
	int digit = 2;
	
	
	in = fopen("input.txt", "r");
	fscanf(in, "%d", &N);
	fclose(in);
	
	out = fopen("output.txt", "w");
	for(int i = 1; i < N + 1; i++)
	{
		if((i % 2) != 0) fprintf(out, "%c", letter++);
		
		else
		{
			 fprintf(out, "%d", digit);
			 digit += 2;
			 if(digit > 8) digit = 2;
		 }
		 
	}
	fclose(out);

	return 0;
}

