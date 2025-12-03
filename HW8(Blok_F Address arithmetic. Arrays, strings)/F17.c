#include <stdio.h>

int main()
{
    int matrix[5][5];
	int trace = 0;
	
    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 5; j++) 
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < 5; i++) trace += matrix[i][i];

    printf("%d\n", trace);
    
    return 0;
}
