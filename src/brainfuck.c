#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"
#include "bfscan.h"

#define MAX_CELLS 30000

void print_args(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
}

char *read_program(const char *filename)
{
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *contents = malloc(fsize + 1);
    fread(contents, fsize, 1, file);
    fclose(file);

    contents[fsize] = '\0';

    return contents;
}

void print_prog(const char *program, int ip, int program_length)
{
    int from = ip - 5;
    from = clamp(from, 0, program_length);
    printf("\n)%.11s\n", program + from);
    printf(")");
    for (int i = 0; i < ip - from; i++) {
        printf(" ");
    }
    printf("^\n");
}

void print_help()
{
    printf("Usage: \n");
    printf("  ./brainfuck -s [program]\n");
    printf("  ./brainfuck -f [file]\n");
}

int main(int argc, char *argv[])
{
    char *program = NULL;

    if (argc == 3 && strcmp(argv[1], "-s") == 0) {
        program = strdup(argv[2]);
    } else if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        program = read_program(argv[2]);
    } else {
        print_help();
        exit(-1);
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
                print_prog(program, ip, program_length);
                printf("Tried to move cell-pointer beyond left edge\n");
            }
            break;
        case '>':
            if (cp < MAX_CELLS) {
                cp++;
            } else {
                print_prog(program, ip, program_length);
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

    free(program);

    return 0;
}
