#include <stdlib.h>
#include "vector.h"
#include "functions.h"

struct RingInfo{
    void* (*one)();
    void* (*zero)();
    void* (*read)();
    void* (*sum)(void*, void*);
    void* (*minus)(void*);
    void* (*multiply)(void*, const int);
    void* (*numbers_multiply)(void*, void*);
    void (*free)(void*);
    void (*print)(void*);
};

void intRingTest(struct RingInfo* intRing){
    int* a = malloc(sizeof(int)); int* b = malloc(sizeof(int));
    *a = 1; *b = 2;
    if (*(int*) (intRing->sum((void*) a, (void*) b)) == *a + *b)
        printf("OK\n");

    if (*(int*) (intRing->minus(a)) == -*a)
        printf("OK\n");

    if (*(int*) (intRing->multiply(a, 5)) == -*a * 5)
        printf("OK\n");

    if (*(int*) (intRing->numbers_multiply(a, b)) == *a * *b)
        printf("OK\n");
    free(a); free(b);
}

void doubleRingTest(struct RingInfo* doubleRing){
    double* a = malloc(sizeof(double)); double* b = malloc(sizeof(double));
    *a = 1; *b = 2;
    if (*(double*) (doubleRing->sum((void*) a, (void*) b)) == *a + *b)
        printf("OK\n");

    if (*(double*) (doubleRing->minus(a)) == -*a)
        printf("OK\n");

    if (*(double*) (doubleRing->multiply(a, 5)) == -*a * 5)
        printf("OK\n");

    if (*(double*) (doubleRing->numbers_multiply(a, b)) == *a * *b)
        printf("OK\n");
    free(a); free(b);
}

int main(){
    struct RingInfo* intRing = Create(&intOne, &intZero, &readInt, &sumInt,
                                      &minusInt, &multiplyInt, &numbers_multiplyInt, &freeInt, &printInt);

    struct RingInfo* doubleRing = Create(&doubleOne, &doubleZero, &readDouble, &sumDouble,
                                         &minusDouble, &multiplyDouble, &numbers_multiplyDouble, freeDouble, &printDouble);

    struct RingInfo* complexRing = Create(&complexOne, &complexZero, &readComplex, &sumComplex,
                                          &minusComplex, &multiplyComplex, &numbers_multiplyComplex, &freeComplex, &printComplex);


    intRingTest(intRing);
    doubleRingTest(doubleRing);
}