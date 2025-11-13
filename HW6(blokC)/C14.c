#include <stdio.h>

int bool_sum(int x)
{
	int result = 0;
	while(x > 0)
	{
		int num = x % 10;
		result += num;
		x /= 10;
	}
	if(result % 2 == 0) return printf("YES");
	else return printf("NO");

	
}

int main()
{
	int x;
	scanf("%d", &x);
	bool_sum(x);
	return 0;
}

