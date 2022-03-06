#include <stdio.h>
#include <stdlib.h>
#include "vector.c"

int main(){
    struct RingInfo* intRing = Create(sizeof(int), &intOne, &intZero, &sumInt, &minusInt, &multiplyInt, &printInt);
    struct RingInfo* doubleRing = Create(sizeof(double), &doubleOne, &doubleZero, &sumDouble, &minusDouble, &multiplyDouble, &printDouble);
    struct Vector* v1 = E1(intRing);
    struct Vector* v2 = E2(intRing);
    struct Vector* v3 = E3(intRing);
    struct Vector* v4;
    struct Vector* v5 = E1(doubleRing);
    struct Vector* v6;
    struct Vector* v7;
    v4 = sum(v1, v2);
    print(v4);

    int* a = malloc(sizeof(int));
    *a = 5;

    v6 = multiply(v5, a);
    print(v6);
    v7 = multiply(v2, a);
    print(v7);

    struct Vector* temp = minus(v7);
    free_vector(v7);
    v7 = temp;
    print(v7);

    free_vector(v7);
    free_vector(v3);
    free_vector(v1);
    free_vector(v2);
    free_vector(v4);
    free_vector(v5);
    free_vector(v6);
    free(a);
    free(intRing);
    free(doubleRing);
}
