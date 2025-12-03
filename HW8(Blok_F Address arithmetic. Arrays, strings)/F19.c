#include <stdio.h>

int main()
{
    int matrix[5][5];

    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 5; j++) 
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    int diag_sum = 0;
    for (int i = 0; i < 5; i++) 
    {
        diag_sum += matrix[i][i];
    }
    float avg = diag_sum / 5.0;

    int count = 0;
    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 5; j++) 
        {
            if (matrix[i][j] > 0 && matrix[i][j] > avg)
            {
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}
