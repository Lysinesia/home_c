#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *in, *out;
	char surname[150];
	char name[150];
	char patr[150];
	
	in = fopen("input.txt", "r");
	fscanf(in, "%s %s %s", surname, name, patr);
	fclose(in);
	
	out = fopen("output.txt", "w");
	fprintf(out, "Hello, %s %s!", name, surname);
	fclose(out);
	return 0;
}

