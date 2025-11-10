#include <stdio.h>

int main() {
    int x;
    scanf("%d", &x);
    
    while (x >= 10) {
        if (x % 10 == (x / 10) % 10) {
            printf("YES");
            return 0;
        }
        x /= 10;
    }
    
    printf("NO");
    return 0;
}
