#include <stdio.h>

int main(int argc, char **argv)
{
	int arr[10];
	int N;
	int count = 0;
	scanf("%d", &N);
	
	while(N > 0)
	{
		int ost = N % 10;
		arr[count++] = ost;
		N /= 10;
	}
	 for(int i = count - 1; i >= 0; i--) printf("%d ", arr[i]); 
	return 0;
}

