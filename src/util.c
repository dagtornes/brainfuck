#include "util.h"
#include <stdlib.h>
#include <string.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a < b ? b : a;
}

int clamp(int v, int a, int b)
{
    return max(a, min(v, b));
}

char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if (dup) {
        strcpy(dup, str);
    }
    return dup;
}
