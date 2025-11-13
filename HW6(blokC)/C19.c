#include <stdio.h>

int digit_to_num(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return 0;
}

int main() {
    char c;
    int sum = 0;
    
    while ((c = getchar()) != '.') {
        sum += digit_to_num(c);
    }
    
    printf("%d\n", sum);
    return 0;
}
