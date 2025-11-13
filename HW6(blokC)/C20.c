#include <stdio.h>
int main() {
    char c; int b = 0;
    while ((c = getchar()) != '.') {
        if (c == '(') b++;
        else if (c == ')') if (--b < 0) break;
    }
    printf(b ? "NO" : "YES");
    return 0;
}

