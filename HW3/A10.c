#include <stdio.h>

int main()
{
	int values[5];
	//printf("enter five values: ");
	for (int x = 0; x < 5; x++) {
		scanf("%d", &values[x]);
	}
	
	int max = values[0];
	for(int x = 1; x < 5; x++) {
		if (values[x] < max) {
			max = values[x];
		}
	}
	
	printf("%d", max);
	return 0;
}
