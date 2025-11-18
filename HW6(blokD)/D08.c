#include <stdio.h>

void recursionN_to_N(int a, int b)
{
    printf("%d ", a);
    
    if (a == b) return;
    
    if (a < b) recursionN_to_N(a + 1, b);

    else recursionN_to_N(a - 1, b);

}

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	recursionN_to_N(a, b);
	return 0;
}


