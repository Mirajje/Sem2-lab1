#include <stdlib.h>
#include "vector.c"
#include "functions.h"

void intRingTest(struct RingInfo* intRing){
    int* a = malloc(sizeof(int)); int* b = malloc(sizeof(int));
    *a = 3; *b = 4;
    if (*(int*) (intRing->sum(a, b)) == 7)
        if (*(int*) (intRing->minus(a)) == -3)
            if (*(int*) (intRing->multiply(a, 5)) == 15)
                if (*(int*) (intRing->numbers_multiply(a, b)) == 12)
                    printf("intRing OK\n");
    free(a); free(b);
}

void doubleRingTest(struct RingInfo* doubleRing){
    double* a = malloc(sizeof(int)); double* b = malloc(sizeof(int));
    *a = 3; *b = 4;
    if (*(double*) (doubleRing->sum(a, b)) == 7)
        if (*(double*) (doubleRing->minus(a)) == -3)
            if (*(double*) (doubleRing->multiply(a, 5)) == 15)
                if (*(double*) (doubleRing->numbers_multiply(a, b)) == 12)
                    printf("doubleRing OK\n");
    free(a); free(b);
}

int complexEqual(struct Complex* a, struct Complex* b){
    if (*a->r == *b->r && *a->im == *b->im)
        return 1;
    else
        return 0;
}

void complexRingTest(struct RingInfo* complexRing){
    struct Complex* a = malloc(sizeof(struct Complex)); struct Complex* b = malloc(sizeof(struct Complex));
    a->r = malloc(sizeof(double)); a->im = malloc(sizeof(double));
    b->r = malloc(sizeof(double)); b->im = malloc(sizeof(double));
    *a->r = 3; *a->im = 5; *b->r = 4; *b->im = 6;

    struct Complex* c = malloc(sizeof(struct Complex));
    c->r = malloc(sizeof(double)); c->im = malloc(sizeof(double));

    *c->r = 7; *c->im = 11;
    if (complexEqual((struct Complex*) (complexRing->sum(a, b)), c)) {

        *c->r = -3; *c->im = -5;
        if (complexEqual((struct Complex*) (complexRing->minus(a)), c)) {

            *c->r = 15; *c->im = 25;
            if (complexEqual((struct Complex*) (complexRing->multiply(a, 5)), c)) {

                *c->r = -18; *c->im = 38;
                if (complexEqual((struct Complex*) (complexRing->numbers_multiply(a, b)), c)){
                    printf("complexRing OK\n");
                }
            }
        }
    }
    freeComplex(a); freeComplex(b); freeComplex(c);
}

int intVectorEqual(struct Vector* v1, struct Vector* v2){
    if (*(int*) getX(v1) == *(int*) getX(v2) && *(int*) getY(v1) == *(int*) getY(v2) && *(int*) getZ(v1) == *(int*) getZ(v2))
        return 1;
    else
        return 0;
}

void functionsTest(struct RingInfo* intRing){
    struct Vector* a = E1(intRing);
    struct Vector* b = E3(intRing);

    struct Vector* c = malloc(sizeof(struct Vector));
    c->ringInfo = intRing;
    c->x = malloc(sizeof(int));
    c->y = malloc(sizeof(int));
    c->z = malloc(sizeof(int));

    *(int*) getX(c) = 1; *(int*) getY(c) = 0; *(int*) getZ(c) = 1;

    if (intVectorEqual(sum(a, b), c)){

        *(int*) getX(c) = -1; *(int*) getY(c) = 0; *(int*) getZ(c) = 0;
        if (intVectorEqual(minus(a), c)){

            *(int*) getX(c) = 1; *(int*) getY(c) = 0; *(int*) getZ(c) = -1;
            if (intVectorEqual(subtraction(a, b), c)){

                *(int*) getX(c) = 5; *(int*) getY(c) = 0; *(int*) getZ(c) = 0;
                if (intVectorEqual(multiply(a, 5), c)){

                    *(int*) getX(c) = 0; *(int*) getY(c) = -1; *(int*) getZ(c) = 0;
                    if (intVectorEqual(vector_multiply(a, b), c)){
                        printf("functions OK\n");
                    }
                }
            }
        }
    }
    free_vector(a); free_vector(b); free_vector(c);
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
    complexRingTest(complexRing);
    functionsTest(intRing);

    free(intRing);
    free(doubleRing);
    free(complexRing);
}