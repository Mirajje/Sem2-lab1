#include <stdio.h>
#include <stdlib.h>
#include "vector.c"

int main(){
    struct RingInfo* intRing = Create(sizeof(int), &intOne, &intZero, &readInt, &sumInt, &minusInt, &multiplyInt, &printInt);
    struct RingInfo* doubleRing = Create(sizeof(double), &doubleOne, &doubleZero, &readDouble, &sumDouble, &minusDouble, &multiplyDouble, &printDouble);

    struct Vector** mas = malloc(0);
    int* n = malloc(sizeof(int));
    *n = 0;

    mas = push_back(mas, n, FromKeyboard(intRing));
    mas = push_back(mas, n, FromKeyboard(intRing));
    mas = push_back(mas, n, sum(mas[0], mas[1]));

    mas = push_back(mas, n, multiply(mas[2], 8));

    mas = delete(mas, n, 0);
    mas = push_back(mas, n, E1(intRing));

    mas = push_back(mas, n, minus(mas[2]));
    print_mas(mas, n);
    free_mas(mas, n);

    free(n);
    free(intRing);
    free(doubleRing);
}
