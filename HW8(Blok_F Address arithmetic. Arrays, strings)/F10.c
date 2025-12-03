#include <stdio.h>

void compress_string(char *str, char *result)
{
	while(*str != '.')
	{
		char temp = *str;
		int count = 0;
		
		while(*str == temp)
		{
			count++;
			str++;
		}
		
		*result = temp;
		result++;
		
		if(count >=10)
		{
			*result = (count / 10) + '0';
			 result++;
			*result = (count % 10) + '0';
			 result++;
		 }
		else
		{
			*result = count + '0';
			result++;
		}
	}
	*result = '\0';
}

int main(int argc, char **argv)
{
	char str[1001];
	char result[1001 * 2];
	scanf("%s", str);
	
	compress_string(str, result);
    printf("%s\n", result);
	return 0;
}

