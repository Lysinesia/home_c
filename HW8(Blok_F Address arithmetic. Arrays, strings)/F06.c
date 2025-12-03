#include <stdio.h>

int is_two_same(int size, int a[])
{
	for(int i = 0; i < size; i++)
	{
		for(int j = i + 1; j < size; j++)
		{
			if(a[j] == a[i]) return 1;
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	int size = 0;
	scanf("%d", &size);
	int a[size];
	for(int i = 0; i < size; i++) scanf("%d", &a[i]);
	
	if (is_two_same(size, a)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
	//is_two_same(size, a);
	
	return 0;
}

