#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#define IN 0
#define OUT 1

static struct option longopts[] = {
      {"bytes",   no_argument, nullptr, 'c'},
      {"symbol",  no_argument, nullptr, 'm'},
      {"lines",   no_argument, nullptr, 'l'},
      {"words",   no_argument, nullptr, 'w'},
      {"help",    no_argument, nullptr, 'h'},
      {"version", no_argument, nullptr, 'v'}
  };

static bool print_bytes, print_symbol, print_lines, print_words, print_help, print_version;
static long bufbytes, bufsymbol, buflines, bufwords;

int main(int argc, char *argv[]) {
    int optc;
    int getc;
    int state;

    /*Arguments handling*/
    print_bytes = print_symbol = print_lines = print_words = print_help = print_version = false;
    while((optc = getopt_long(argc, argv, "cmlwhv", longopts, nullptr)) != -1) {
        switch(optc) {
          case 'c': print_bytes = true; break;
          case 'm': print_symbol = true; break;
          case 'l': print_lines = true; break;
          case 'w': print_words = true; break;
          case 'v': print_version = true; break;
          case 'h': print_help = true; break;
          default:
            fprintf(stderr, "Unknown option '%s'\n", optc);
            return 1;
        }
    }

    if (print_version) {
        printf("\nWord count. Version 1.0.\nBy: igor-plastinin@yandex.ru\n");
        return 0;
    }

    if (print_help) {
        printf("\nWord count. Help:\n-c quantity bytes\n-m quantity char\n-l quantity lines\n-w quantity words\n");
        return 0;
    }

    if (!(print_bytes || print_symbol || print_lines || print_words))
        print_bytes = print_symbol = print_lines = print_words = true;

    /*Handling text*/
    bufbytes = bufsymbol = buflines = bufwords = 0;
    state = OUT;
    while((getc = getchar()) != EOF) {
        bufbytes++;
        bufsymbol++;
        if (getc == '\n') {
            buflines++;
        }
        if (getc == ' ' || getc == '\n' || getc == '\t' || getc == '\r' || getc == '\v' || getc == '\f') {
            state = OUT;
        } else if (state == OUT) {
            bufwords++;
            state = IN;
        }
    }

    /*Print result*/
    if (print_bytes) {
        printf("%ld ", bufbytes);
    }
    if (print_symbol) {
        printf("%ld ", bufsymbol);
    }
    if (print_lines) {
        printf("%ld ", buflines);
    }
    if (print_words) {
        printf("%ld ", bufwords);
    }
    return 0;
}
