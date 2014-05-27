#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bfscan.h"

#define MAX_CELLS 30000

void test_program_back(const char *program, int start_ip, int expect_ip)
{
    int found_ip = scan_back(start_ip, program);
    if (found_ip == expect_ip) {
        printf("PASS\n");
    } else {
        printf("FAIL Found ip = %d, expect_ip = %d\n", found_ip, expect_ip);
    }
}

void test_programs_back()
{
    test_program_back("[]", 1, 0);
    test_program_back("[[]]", 3, 0);
    test_program_back("[[]]", 2, 1);
    test_program_back("[1[34]678]", 9, 0);
}

void test_program_fwd(const char *program, int start_ip, int expect_ip)
{
    int found_ip = scan_fwd(start_ip, program);
    if (found_ip == expect_ip) {
        printf("PASS\n");
    } else {
        printf("FAIL Found ip = %d, expect_ip = %d\n", found_ip, expect_ip);
    }
}

void test_programs_fwd()
{
    test_program_fwd("[]", 0, 1);
    test_program_fwd("[[]]", 0, 3);
    test_program_fwd("[.]", 0, 2);
    test_program_fwd("[.[].]", 0, 5);
    test_program_fwd("[[]]", 1, 2);
}

void test_programs()
{
    test_programs_fwd();
    test_programs_back();
}

void print_args(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
}

int main(int argc, char *argv[])
{
    const char *program = NULL;
    if (argc == 3 && strcmp(argv[1], "-s") == 0) {
        program = argv[2];
    } else {
        program = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    }

    char cells[MAX_CELLS];
    memset(cells, 0, MAX_CELLS * sizeof(char));
    int cp = 0;

    int program_length = strlen(program);
    int ip = 0;

    while (ip < program_length) {
        char instruction = program[ip];
        switch (instruction) {
        case '<':
            if (cp > 0) {
                cp--;
            } else {
                printf("Tried to move cell-pointer beyond left edge\n");
            }
            break;
        case '>':
            if (cp < MAX_CELLS) {
                cp++;
            } else {
                printf("Tried to move cell-pointer beyond right edge\n");
            }
            break;
        case '+':
            cells[cp]++;
            break;
        case '-':
            cells[cp]--;
            break;
        case '.':
            putchar(cells[cp]);
            break;
        case ',':
            printf("> ");
            cells[cp] = getchar();
            getchar(); // Chomp EOL
            break;
        case '[':
            if (cells[cp] == 0) {
                ip = scan_fwd(ip, program);
            } 
            break;
        case ']':
            if (cells[cp] != 0) {
                ip = scan_back(ip, program);
            }
            break;
        default:
            ; // Ignore any other character
        }
        ip++;
    }

    printf("\n");

    return 0;
}
