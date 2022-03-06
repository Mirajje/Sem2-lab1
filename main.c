#include <stdio.h>
#include <stdlib.h>
#include "vector.c"

int main(){
    struct RingInfo* intRing = Create(sizeof(int), &intOne, &intZero, &intSum, &intMinus, &intMultiply, &intPrint);
    //struct RingInfo* doubleRing = Create(sizeof(double), &doubleOne, &doubleZero, &doubleSum, &doubleMinus, &doubleMultiply, &doublePrint);
    struct Vector* v1 = E1(intRing);
    struct Vector* v2 = E2(intRing);
    struct Vector* v3 = E3(intRing);
    struct Vector* v4;
    v4 = minus(v1);
    //v4 = sum(v3, v4);
    print(v4);
    //v4 = minus(v4);
    print(v4);

    free_vector(v3);
    free_vector(v1);
    free_vector(v2);
    free_vector(v4);
    free(intRing);
    //free(doubleRing);
}
