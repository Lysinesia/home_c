#include <stdio.h>

int is_happy_number(int n)
{
	int sum = 0, product = 1;
	while(n > 0)
	{
		int num = n % 10;
		sum += num;
		product *= num;
		n /= 10;
	}
	if(sum == product) return printf("YES");
	else return printf("NO");

	
}

int main()
{
	int n;
	scanf("%d", &n);
	is_happy_number(n);
	return 0;
}


