#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *in, *out;
	char str[1001];
	
	in = fopen("input.txt", "r");
	fgets(str, sizeof(str), in);
	fclose(in);
	
	str[strcspn(str, "\n")] = '\0';
	
	char *last_dot = strrchr(str, '.');
	char *last_slash = strrchr(str, '/');
	
	if(last_dot && (!last_dot || last_dot > last_slash)) *last_dot = '\0';
	
	out = fopen("output.txt", "w");
	fprintf(out, "%s.html", str);
	fclose(out);
	
	
	return 0;
}

