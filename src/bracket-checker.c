#include <stdio.h>
 int tos; /*Top of the stack*/

/*Push an element onto a stack*/
int push(int lim, char item, char s[]) {
    if (tos == lim - 1) {
        printf("Error: stack overflow");
        return -1;
    } else {
        s[++tos] = item;
        return 0;
    }
}

/*Pop an element from the stack*/
char pop(char s[]) {
    if (tos < 0) {
        printf("The stack is not loaded.");
        return '\0';
    } else {
        return s[tos--];
    }
}

/*Is the stack empty?*/
int is_empty() {
    return tos == -1;
}

/*Matching pair*/
int is_matching_pair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int main () {
    int c;
    int line;
    int stack_size;
    stack_size = 1000;
    char stck[stack_size + 1]; /*Stack array*/
    tos = -1; /*Initialization of the top of the stack*/

    line = 1;
    while((c = getchar()) != EOF) {
        if (c == '\n')
            ++line;
        if (c == '(' || c == '{' || c == '[') {
            push(stack_size, c, stck);
        } else if (c == ')' || c == '}' || c == ']' ) {
            if (is_empty()) {
                printf("Error: Opening element not found for element \"%c\" on line %d\n", c, line);
                return -1;
            } else {
                char opened = pop(stck);
                if (!is_matching_pair(opened, c)) {
                    printf("Error: The closing element \"%c\" on the line #%d does not match the opening one.\n", c, line);
                    return -1;
                }
            }
        }
    }

    if (!is_empty()) {
        printf("There are unclosed elements:\n");
        for(int i = 0; i <= tos; i++) {
            printf("    Open element has no pair: %c\n", stck[i]);
        }
        return -1;
    }

    printf("The test was completed successfully.");
    return 0;
}
