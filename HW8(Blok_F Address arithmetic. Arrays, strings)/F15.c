#include <stdio.h>

int count_bigger_abs(int n, int a[])
{
    int count = 0;
    int max = a[0];
    
    for (int i = 1; i < n; i++)
    {
        if (a[i] > max) max = a[i];
    }
    
    for (int i = 0; i < n; i++) 
    {
        int abs_val = a[i];
        if (abs_val < 0) abs_val = -abs_val;
        
        if (abs_val > max) count++;
    }   
    return count;
}

int main()
{
    int size;
	scanf("%d", &size);
	int arr[size];
	for(int i = 0; i < size; i++) scanf("%d", &arr[i]);
	
	int result = count_bigger_abs(size, arr);
    printf("%d\n", result);
    
    return 0;
}
