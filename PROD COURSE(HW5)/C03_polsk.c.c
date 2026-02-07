#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() 
{
    int stack[1000];
    int top = -1;
    char input[1000];
    
    fgets(input, sizeof(input), stdin);
    
    char* token = strtok(input, " \n\t");
    
    while (token != NULL) 
    {
        if (token[strlen(token)-1] == '.') 
        {
            token[strlen(token)-1] = '\0';
        }
        
        if (strcmp(token, "+") == 0) 
        {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = a + b;
        }
        else if (strcmp(token, "-") == 0) 
        {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = a - b;
        }
        else if (strcmp(token, "*") == 0) 
        {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = a * b;
        }
        else if (strcmp(token, "/") == 0) 
        {
            int b = stack[top--];
            int a = stack[top--];
            if (b != 0) stack[++top] = a / b;
            else stack[++top] = 0;
        }
        else 
        {
            int num;
            if (sscanf(token, "%d", &num) == 1) stack[++top] = num;
        }
        
        token = strtok(NULL, " \n\t");
    }
    
    if (top >= 0) printf("%d\n", stack[top]);
    else printf("0\n");

    
    return 0;
}