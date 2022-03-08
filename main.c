#include <stdio.h>
#include <stdlib.h>
#include "vector.c"

int main(){
    struct RingInfo* intRing = Create(sizeof(int), &intOne, &intZero, &readInt, &sumInt,
            &minusInt, &multiplyInt, &numbers_multiplyInt, &freeInt, &printInt);

    struct RingInfo* doubleRing = Create(sizeof(double), &doubleOne, &doubleZero, &readDouble, &sumDouble,
            &minusDouble, &multiplyDouble, &numbers_multiplyDouble, freeDouble, &printDouble);

    struct RingInfo* complexRing = Create(sizeof(struct Complex), &complexOne, &complexZero, &readComplex, &sumComplex,
            &minusComplex, &multiplyComplex, &numbers_multiplyComplex, &freeComplex, &printComplex);

    struct Vector** mas = malloc(0);
    int* n = malloc(sizeof(int));
    *n = 0;

    mas = push_back(mas, n, FromKeyboard(complexRing));
    mas = push_back(mas, n, FromKeyboard(complexRing));

    mas = push_back(mas, n, vector_multiply(mas[0], mas[1]));
    mas = push_back(mas, n, subtraction(mas[0], mas[1]));
    mas = push_back(mas, n, sum(mas[0], mas[1]));
    mas = delete(mas, n, 0);
    print_mas(mas, n);


    free_mas(mas, n);
    free(n);

    free(complexRing);
    free(intRing);
    free(doubleRing);
}
