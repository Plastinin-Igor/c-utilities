#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#define STACK_SIZE 1000

static struct option longopts[] = {
    {"push",  required_argument, nullptr, 'a'}, // add
    {"pop",   no_argument,       nullptr, 'r'}, // remove
    {"peek",  no_argument,       nullptr, 'p'}, // peek
    {"empty", no_argument,       nullptr, 'e'}, // is empty
    {"size",  no_argument,       nullptr, 's'}, // count
    {"clear", no_argument,       nullptr, 'c'}, // clear stack
    {"help",  no_argument,       nullptr, 'h'}, // help
    {nullptr, 0, 0}
};

int stack[STACK_SIZE];
int tos = -1;

void print_err_overflow() {
    printf("[ERROR] Stack over flow\n");
}

void print_err_underflow() {
    printf("[ERROR] Stack underflow\n");
}

int push(int c) {
    if (tos >= STACK_SIZE - 1) {
        print_err_overflow();
        return -1;
    }
    stack[++tos] = c;
    return 0;
}

int pop() {
    if (tos < 0) {
        print_err_underflow();
        return -1;
    }
    return stack[tos--];
}

int is_empty() {
    return tos == -1;
}

int peek() {
    if (tos < 0) {
        print_err_underflow();
        return -1;
    }
    return stack[tos];
}

int size() {
    return tos + 1;
}

void clear() {
  tos = -1;
}

void print_help(){
    printf("\n");
    printf("  You can use long arguments:\n");
    printf("  --push 10 # Add an element (multiple addition 10, 11, 12, ... n)\n");
    printf("  --pop     # Remove and show top\n");
    printf("  --peek    # Show top element\n");
    printf("  --empty   # Check if stack is empty\n");
    printf("  --size    # Show current size\n");
    printf("  --clear   # Clear stack\n");
    printf("\n");
    printf("  Usage: stack [--push VALUE1,VALUE2,... | --pop | --peek | --empty | --size]\n");
    printf("\n\n");
    printf("  You can use short arguments:\n");
    printf("  -a 10 # Add an element (multiple addition 10, 11, 12, ... n)\n");
    printf("  -r    # Remove and show top\n");
    printf("  -p    # Show top element\n");
    printf("  -e    # Check if stack is empty\n");
    printf("  -s    # Show current size\n");
    printf("  -c    # Clear stack\n");

}

int main(int argc, char *argv[]) {
    int optc;

    while((optc = getopt_long(argc, argv, "a:rpesch", longopts, nullptr)) != -1) {
        switch(optc) {
            case 'a': {
                char *token = strtok(optarg, ",");
                while (token != nullptr) {
                    int value = atoi(token);
                    if (push(value) == 0) {
                        printf("Pushed: %d\n", value);
                    }
                    token = strtok(nullptr, ",");
                }
                break;
            }
            case 'r': {
                int value = pop();
                if (value != -1) {
                    printf("Popped: %d\n", value);
                }
                break;
            }
            case 'p': {
                int value = peek();
                if (value != -1) {
                    printf("Top element: %d\n", value);
                }
                break;
            }
            case 'e': {
                printf("Stack is %s\n", is_empty() ? "empty" : "not empty");
                break;
            }
            case 's': {
                int value = size();
                if (value != -1) {
                    printf("Stack size: %d\n", value);
                }
                break;
            }
            case 'c': {
                clear();
                printf("Stack cleared");
                break;
            }
            case 'h':{
                print_help();
                break;
            }

            default:
                printf("Usage: %s [--push VALUE1,VALUE2,... | --pop | --peek | --empty | --size]\n", argv[0]);
        }
    }
    return 0;
}
