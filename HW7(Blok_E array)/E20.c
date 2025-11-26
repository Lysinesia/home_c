#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int digits[10];
    int count = 0;
	int result = 0;

    while (N > 0)
    {
        digits[count++] = N % 10;
        N /= 10;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (digits[j] < digits[j + 1]) 
            {
                int temp_digit = digits[j];
                digits[j] = digits[j + 1];
                digits[j + 1] = temp_digit;
            }
        }
    }

    for (int i = 0; i < count; i++) result = result * 10 + digits[i];
    
    printf("%d", result);
    return 0;
}
