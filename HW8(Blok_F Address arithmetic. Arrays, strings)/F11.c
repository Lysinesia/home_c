#include <stdio.h>

void find_min_sum(int arr[], int size)
{
	int min_sum = arr[0] + arr[1];
	int min_index1 = 0;
	int min_index2 = 1;
	
	for(int i = 0; i < size; i++)
	{
		for(int j = i + 1; j < size; j++)
		{
			int curent_sum = arr[i] + arr[j];
			
			if(curent_sum < min_sum)
			{
				min_sum = curent_sum;
				min_index1 = i;
				min_index2 = j;
			}
		}
	}
	if(min_index1 < min_index2) printf("%d %d", min_index1, min_index2);
	else printf("%d %d", min_index2, min_index1);
}

int main(int argc, char **argv)
{
	int arr[30];
	for(int i = 0; i < 30; i++) scanf("%d", &arr[i]);
	
	find_min_sum(arr, 30);
	return 0;
}

