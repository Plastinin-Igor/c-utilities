#include <stdio.h>

typedef enum status_type {
    CODE,
    STRING,
    CHAR,
    LINE_COMMENT,
    BLOCK_COMMENT
} status_type;

const char* status_to_string(status_type state) {
    switch(state) {
        case CODE: return "CODE";
        case STRING: return "STRING";
        case CHAR: return "CHAR";
        case LINE_COMMENT: return "LINE_COMMENT";
        case BLOCK_COMMENT: return "BLOCK_COMMENT";
        default: return "UNKNOWN";
    }
}


/*Push an element onto a stack*/
int push(int *tos, int lim, char item, char s[]) {
    if (*tos == lim - 1) {
        printf("Error: stack overflow");
        return -1;
    } else {
        s[++(*tos)] = item;
        return 0;
    }
}

/*Pop an element from the stack*/
char pop(int *tos, char s[]) {
    if (*tos < 0) {
        printf("The stack is not loaded.");
        return '\0';
    } else {
        return s[(*tos)--];
    }
}

/*Is the stack empty?*/
int is_empty(int tos) {
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

char get_pair(char bracket) {
  switch(bracket) {
      case ')': return '(';
      case '}': return '{';
      case ']': return '[';
      default: return bracket;
  }
}

int main () {
    int c;
    int line;
    int column;
    int prev_char;
    status_type state;
    int stack_size;
    stack_size = 1000;
    char stck[stack_size + 1]; /*Stack array*/
    int tos = -1; /*Top of the stack*/

    line = 1;
    column = 0;
    state = CODE;
    prev_char = 0;
    while((c = getchar()) != EOF) {
        ++column;
        // Checking a single-line comment
        if (state == CODE && prev_char == '/' && c == '/') {
            state = LINE_COMMENT;
        }
        if (state == LINE_COMMENT && c == '\n') {
            state = CODE;
        }
        // Checking a multi-line comment
        if (state == CODE && prev_char == '/' && c == '*') {
            state = BLOCK_COMMENT;
        }
        if (state == BLOCK_COMMENT && prev_char == '*' && c == '/') {
            state = CODE;
        }
        // Checking a string
        if (state == CODE && prev_char != '"' && c == '"') {
                state = STRING;
        } else if (state == STRING && prev_char != '"' && c == '"') {
            state = CODE;
        }
        // Checking a char
        if (state == CODE && prev_char != '\'' && c == '\'') {
                state = CHAR;
        } else if (state == CHAR && prev_char != '\'' && c == '\'') {
            state = CODE;
        }

        prev_char = c;

        if (c == '\n') {
            ++line;
            column = 0;
        }

        if (state == CODE) {
            if (c == '(' || c == '{' || c == '[') {
                push(&tos, stack_size, c, stck);
            } else if (c == ')' || c == '}' || c == ']' ) {
                if (is_empty(tos)) {
                    print_error_heade(line, column);
                    printf("    Unmatched closing \"%c\"\n", c);
                    printf("    -> No opening \"%c\" found\n", get_pair(c));
                    return -1;
                } else {
                    char opened = pop(&tos, stck);
                    if (!is_matching_pair(opened, c)) {
                        print_error_heade(line, column);
                        printf("    Mismatch of elements:\n");
                        printf("    -> Found \"%c\", but expected \"%c\"\n", c, opened);
                        return -1;
                    }
                }
            }
        }
    }

    if (!is_empty(tos)) {
        printf("\n[ERROR] Unclosed brackets found:\n\n");
        for(int i = 0; i <= tos; i++) {
            printf("    Open element has no pair: %c\n", stck[i]);
        }
        return -1;
    }

    print_success();
    return 0;
}
