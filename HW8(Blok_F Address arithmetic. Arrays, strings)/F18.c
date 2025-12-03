#include <stdio.h>

int main()
{
    int matrix[10][10];
    int total_sum = 0;
    
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    for (int i = 0; i < 10; i++) 
    {
        int max_in_row = matrix[i][0];
        for (int j = 1; j < 10; j++)
        {
            if (matrix[i][j] > max_in_row)
            {
                max_in_row = matrix[i][j];
            }
        }
        
        total_sum += max_in_row;
    }
    
    printf("%d\n", total_sum);
    
    return 0;
}
