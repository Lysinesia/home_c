#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    for(int i = 2; i <= 9; i++) {
        int X = N / i;
        printf("%d %d\n", i, X);
    }
    
    return 0;
}
