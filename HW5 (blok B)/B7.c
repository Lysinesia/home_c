#include <stdio.h>

int main() {
    int x;          
    scanf("%d", &x); 
    
    int counter = 0;  
    
    while (x > 0) { 
        int digit = x % 10;    
        int mask = 1 << digit; 
        
        if (counter & mask) {  
            printf("YES");     
            return 0;          
        }
        
        counter = counter | mask; 
        x = x / 10;           
    }
    
    printf("NO");  
    return 0;
}
