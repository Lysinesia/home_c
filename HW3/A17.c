#include <stdio.h>

int main()
{
	int x;
	scanf("%d", &x);
	if (x == 12 || x < 3) {
		printf("winter");
	} else if (x > 2 && x < 6) {
		printf("spring");
	} else if (x > 5 && x < 9) {
		printf("summer");
	} else if (x > 8 && x < 12) {
		printf("autumn");
	}
	return 0;
}

