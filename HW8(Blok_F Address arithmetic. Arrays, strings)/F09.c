#include <stdio.h>

void swap_negmax_last(int size, int a[])
{
    int negmax_index = -1;
    
    for (int i = 0; i < size; i++)
    {
        if (a[i] < 0)
        {
            if (negmax_index == -1 || a[i] > a[negmax_index])
            {
                negmax_index = i;
            }
        }
    }
    if (negmax_index != -1 && negmax_index != size - 1)
    {
        int temp = a[size - 1];
        a[size - 1] = a[negmax_index];
        a[negmax_index] = temp;
    }
}


int main(int argc, char **argv)
{
	int size;
	scanf("%d", &size);
	int a[size];
	for(int i = 0; i < size; i++) scanf("%d", &a[i]);
	
	swap_negmax_last(size, a);
	
	return 0;
}

