#include <stdio.h>
#include <string.h>

int main(void)
{
	FILE *input, *output;
	char interim[102];
	int length = 0;

	
	input = fopen("input.txt", "r");
	if(input != NULL)
	{
		fgets(interim, sizeof(interim), input);
		length = strlen(interim);
		while (length > 0 && (interim[length-1] == '\n' || interim[length-1] == '\r'))
		{
			interim[length-1] = '\0';
			length--;
		}
	}
	
	fclose(input);
	
	output = fopen("output.txt", "w");
	
	for (int i = 0; i < 3; i++)
        {
            fprintf(output, "%s", interim);
            if (i < 2) fprintf(output, ", ");
        }
        
        fprintf(output, " %d", length);
        fclose(output);
		
	
	return 0;
}

