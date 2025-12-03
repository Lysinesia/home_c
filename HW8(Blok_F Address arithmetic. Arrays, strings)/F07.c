#include <stdio.h>

int compression(int a[], int b[], int N)
{
	int count = 1;
    int b_index = 0;
    if(a[0] == 1) b[b_index++] = 0;
    
	 for (int i = 1; i < N; i++)
    {
		if(a[i] == a[i - 1]) count++;
		else
		{
			b[b_index++] = count;
			count = 1;
		}
    }
	b[b_index++] = count;
	return b_index;
}

int main(int argc, char **argv)
{
	int N;
	scanf("%d", &N);
	int a[N];
	for(int i = 0; i < N; i++) scanf("%d", &a[i]);
	int b[N + 1];
	compression(a, b, N);
	
	 int b_size = compression(a, b, N);
    
    printf("[");
    for (int i = 0; i < b_size; i++)
    {
        printf("%d", b[i]);
        if (i < b_size - 1) 
            printf(",");
    }
    printf("]\n");
	return 0;
}

