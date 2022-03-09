#include <stdio.h>

void my_flush()
{
    int c;
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}