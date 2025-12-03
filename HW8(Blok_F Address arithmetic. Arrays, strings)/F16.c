#include <stdio.h>

int main() 
{
    char letter, digit;
    scanf("%c%c", &letter, &digit);

    int letter_num = letter - 'A' + 1;
    int digit_num = digit - '0';

    if ((letter_num + digit_num) % 2 == 0) printf("BLACK\n");
    else printf("WHITE\n");
   
    return 0;
}
