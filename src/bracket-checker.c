#include <stdio.h>
#define IN  1
#define OUT 0

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

void print_error_heade(int line, int column) {
    printf("\n[ERROR] Line %d, column %d:\n", line, column);
}

void print_success() {
    printf("\n[OK] All brackets are properly balanced!\n");
}

int is_state(int c) {
    int state = OUT;
    if (c == '\'' ) {
        return -1; // TODO
    } else return 0;
}

char get_pair(char bracket) {
  switch(bracket) {
      case '(': return ')';
      case ')': return '(';
      case '{': return '}';
      case '}': return '{';
      case '[': return ']';
      case ']': return '[';
      default: return bracket;
  }
}

int main () {
    int c;
    int line;
    int column;
    int stack_size;
    stack_size = 1000;
    char stck[stack_size + 1]; /*Stack array*/
    tos = -1; /*Initialization of the top of the stack*/

    line = 1;
    column = 1;
    while((c = getchar()) != EOF) {
        ++column;
        if (c == '\n') {
            ++line;
            column = 0;
        }
        if (c == '(' || c == '{' || c == '[') {
            push(stack_size, c, stck);
        } else if (c == ')' || c == '}' || c == ']' ) {
            if (is_empty()) {
                print_error_heade(line, column);
                printf("    Unmatched closing \"%c\"\n", c);
                printf("    -> No opening \"%c\" found\n", get_pair(c));
                return -1;
            } else {
                char opened = pop(stck);
                if (!is_matching_pair(opened, c)) {
                    print_error_heade(line, column);
                    printf("    Mismatch of elements:\n");
                    printf("    -> Found \"%c\", but expected  %c\n", c, opened);
                    return -1;
                }
            }
        }
    }

    if (!is_empty()) {
        printf("\n[ERROR] Unclosed brackets found:\n\n");
        for(int i = 0; i <= tos; i++) {
            printf("    Open element has no pair: %c\n", stck[i]);
        }
        return -1;
    }

    print_success();
    return 0;
}
