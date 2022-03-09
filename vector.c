#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

//constants ============================================================================================================

const int the_int_zero = 0;
const int the_int_one = 1;

const double the_double_zero = 0;
const double the_double_one = 1;

// base (это база) =====================================================================================================

struct Vector{
    struct RingInfo* ringInfo;
    void* x;
    void* y;
    void* z;
};

// complex =============================================================================================================

struct Complex{
    double* r;
    double* im;
};

double* getR(struct Complex* v){
    return v->r;
}

double* getIm(struct Complex* v){
    return v->im;
}

// ring ================================================================================================================

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

struct RingInfo* Create(void* (*one)(),
        void* (*zero)(),
        void* (*read)(),
        void* (*sum)(void*, void*),
        void* (*minus)(void*),
        void* (*multiply)(void*, const int),
        void* (*numbers_multiply)(void*, void*),
        void (*free)(void*),
        void (*print)(void*))
{
    struct RingInfo* ringInfo = malloc(sizeof(struct RingInfo));
    ringInfo->one = one;
    ringInfo->zero = zero;
    ringInfo->read = read;
    ringInfo->sum = sum;
    ringInfo->minus = minus;
    ringInfo->numbers_multiply = numbers_multiply;
    ringInfo->multiply = multiply;
    ringInfo->free = free;
    ringInfo->print = print;
    return ringInfo;
}

// vector ==============================================================================================================

void* getX(struct Vector* v){
    return v->x;
}

void* getY(struct Vector* v){
    return v->y;
}

void* getZ(struct Vector* v){
    return v->z;
}

struct RingInfo* getRingInfo(struct Vector* v){
    return v->ringInfo;
}

struct Vector* E1(struct RingInfo* ringInfo){
    struct Vector* vector = malloc(sizeof(struct Vector));
    vector->x = ringInfo->one();
    vector->y = ringInfo->zero();
    vector->z = ringInfo->zero();
    vector->ringInfo = ringInfo;
    return vector;
}

struct Vector* E2(struct RingInfo* ringInfo){
    struct Vector* vector = malloc(sizeof(struct Vector));
    vector->x = ringInfo->zero();
    vector->y = ringInfo->one();
    vector->z = ringInfo->zero();
    vector->ringInfo = ringInfo;
    return vector;
}

struct Vector* E3(struct RingInfo* ringInfo){
    struct Vector* vector = malloc(sizeof(struct Vector));
    vector->x = ringInfo->zero();
    vector->y = ringInfo->zero();
    vector->z = ringInfo->one();
    vector->ringInfo = ringInfo;
    return vector;
}

struct Vector* FromKeyboard(struct RingInfo* ringInfo){
    struct Vector* vector = malloc(sizeof(struct Vector));
    vector->x = ringInfo->read();
    vector->y = ringInfo->read();
    vector->z = ringInfo->read();
    vector->ringInfo = ringInfo;
    return vector;
}

void free_vector(struct Vector* v){
    getRingInfo(v)->free(getX(v));
    getRingInfo(v)->free(getY(v));
    getRingInfo(v)->free(getZ(v));
    free(v);
}

// functions ===========================================================================================================

struct Vector* sum(struct Vector* v1, struct Vector* v2) {
    struct Vector* res = malloc(sizeof(struct Vector));
    res->x = getRingInfo(v1)->sum(getX(v1), getX(v2));
    res->y = getRingInfo(v1)->sum(getY(v1), getY(v2));
    res->z = getRingInfo(v1)->sum(getZ(v1), getZ(v2));
    res->ringInfo = getRingInfo(v1);
    return res;
}

struct Vector* minus(struct Vector* v){
    struct Vector* res = malloc(sizeof(struct Vector));
    res->x = getRingInfo(v)->minus(getX(v));
    res->y = getRingInfo(v)->minus(getY(v));
    res->z = getRingInfo(v)->minus(getZ(v));
    res->ringInfo = getRingInfo(v);
    return res;
}

struct Vector* subtraction(struct Vector* v1, struct Vector* v2) {
    struct Vector* res = malloc(sizeof(struct Vector));
    void* temp;
    temp = getRingInfo(v1)->minus(getX(v2));
    res->x = getRingInfo(v1)->sum(getX(v1), temp);
    getRingInfo(v1)->free(temp);

    temp = getRingInfo(v1)->minus(getY(v2));
    res->y = getRingInfo(v1)->sum(getY(v1), temp);
    getRingInfo(v1)->free(temp);

    temp = getRingInfo(v1)->minus(getZ(v2));
    res->z = getRingInfo(v1)->sum(getZ(v1), temp);
    getRingInfo(v1)->free(temp);
    res->ringInfo = getRingInfo(v1);
    return res;
}

struct Vector* multiply(struct Vector* v, const int val){
    struct Vector* res = malloc(sizeof(struct Vector));
    res->x = getRingInfo(v)->multiply(getX(v), val);
    res->y = getRingInfo(v)->multiply(getY(v), val);
    res->z = getRingInfo(v)->multiply(getZ(v), val);
    res->ringInfo = getRingInfo(v);
    return res;
}

void scalar_multiply(struct Vector* v1, struct Vector* v2){
    void* t1; void* t2; void* t3; void* t4;
    void* res;
    t1 = getRingInfo(v1)->numbers_multiply(getX(v1), getX(v2));
    t2 = getRingInfo(v1)->numbers_multiply(getY(v1), getY(v2));
    t3 = getRingInfo(v1)->numbers_multiply(getZ(v1), getZ(v2));
    t4 = getRingInfo(v1)->sum(t1, t2);
    res = getRingInfo(v1)->sum(t3, t4);
    getRingInfo(v1)->free(t1);
    getRingInfo(v1)->free(t2);
    getRingInfo(v1)->free(t3);
    getRingInfo(v1)->free(t4);
    getRingInfo(v1)->print(res);
    getRingInfo(v1)->free(res);
    printf("\n");
}

struct Vector* vector_multiply(struct Vector* v1, struct Vector* v2){
    struct Vector* res = malloc(sizeof(struct Vector));
    void* t1; void* t2; void* t3;
    t1 = getRingInfo(v1)->numbers_multiply(getY(v1), getZ(v2));
    t2 = getRingInfo(v1)->numbers_multiply(getZ(v1), getY(v2));
    t3 = getRingInfo(v1)->minus(t2);
    res->x = getRingInfo(v1)->sum(t3, t1);
    getRingInfo(v1)->free(t1);
    getRingInfo(v1)->free(t2);
    getRingInfo(v1)->free(t3);

    t1 = getRingInfo(v1)->numbers_multiply(getZ(v1), getX(v2));
    t2 = getRingInfo(v1)->numbers_multiply(getX(v1), getZ(v2));
    t3 = getRingInfo(v1)->minus(t2);
    res->y = getRingInfo(v1)->sum(t3, t1);
    getRingInfo(v1)->free(t1);
    getRingInfo(v1)->free(t2);
    getRingInfo(v1)->free(t3);

    t1 = getRingInfo(v1)->numbers_multiply(getX(v1), getY(v2));
    t2 = getRingInfo(v1)->numbers_multiply(getY(v1), getX(v2));
    t3 = getRingInfo(v1)->minus(t2);
    res->z = getRingInfo(v1)->sum(t3, t1);
    getRingInfo(v1)->free(t1);
    getRingInfo(v1)->free(t2);
    getRingInfo(v1)->free(t3);

    res->ringInfo = getRingInfo(v1);
    return res;
}

void print(struct Vector* v){
    getRingInfo(v)->print(getX(v));
    getRingInfo(v)->print(getY(v));
    getRingInfo(v)->print(getZ(v));
    printf("\n");
}

// mas =================================================================================================================

void free_mas(struct Vector** mas, const int* n){
    for (int i = 0; i < *n; i++){
        free_vector(mas[i]);
    }
    free(mas);
}

struct Vector** push_back(struct Vector** mas, int* n, struct Vector* elem){
    struct Vector** res = calloc(*n + 1, sizeof(struct Vector*));
    for (int i = 0; i < *n; i++){
        res[i] = mas[i];
    }
    res[*n] = elem;

    free(mas);
    *n = *n + 1;
    return res;
}

struct Vector** delete(struct Vector** mas, int* n, int num){
    if (num > *n - 1 || num < 0){
        printf("Введен некорректный номер удаляемого элемента\n");
        return mas;
    }else{
        struct Vector** res = calloc(*n - 1, sizeof(struct Vector*));
        for (int i = 0; i < *n - 1; i++){
            if (i < num){
                res[i] = mas[i];
            }else{
                res[i] = mas[i + 1];
            }
        }
        free_vector(mas[num]);
        free(mas);
        *n = *n - 1;
        return res;
    }
}

void print_mas(struct Vector** mas, const int* n){
    for (int i = 0; i < *n; i++){
        print(mas[i]);
    }
}

// intRing =============================================================================================================

void* sumInt(void* a1, void* a2){
    int* ia1 = (int*) a1;
    int* ia2 = (int*) a2;
    int* res = malloc(sizeof(int));
    *res = *ia1 + *ia2;
    return (void*) res;
}

void* minusInt(void* a){
    int* res = malloc(sizeof(int));
    *res = -*(int*) a;
    return (void*) res;
}

void* multiplyInt(void* a, const int val){
    int* res = malloc(sizeof(int));
    *res = val * *(int*) a;
    return (void*) res;
}

void* numbers_multiplyInt(void* a, void* b){
    int* res = malloc(sizeof(int));
    *res = *(int*) a * *(int*) b;
    return (void*) res;
}

void printInt(void* v){
    printf("%d ", *(int*) v);
}

void* readInt(){
    int* a = malloc(sizeof(int));
    int check;
    do {
        printf("Введите целое число: ");
        check = scanf("%d", a);
        my_flush();
    } while ((check != 1) || (*a < -100000000 || *a > 100000000));
    return (void*) a;
}

void freeInt(void* a){
    free(a);
}

void* intOne(){
    int* a = malloc(sizeof(int));
    *a = the_int_one;
    return (void*) a;
}

void* intZero(){
    int* a = malloc(sizeof(int));
    *a = the_int_zero;
    return (void*) a;
}

// doubleRing ==========================================================================================================

void* sumDouble(void* a1, void* a2){
    double* ia1 = (double*) a1;
    double* ia2 = (double*) a2;
    double* res = malloc(sizeof(double));
    *res = *ia1 + *ia2;
    return (void*) res;
}

void* minusDouble(void* a){
    double* res = malloc(sizeof(double));
    *res = -*(double*) a;
    return (void*) res;
}

void* multiplyDouble(void* a, const int val){
    double* res = malloc(sizeof(double));
    *res = val * *(double*) a;
    return (void*) res;
}

void* numbers_multiplyDouble(void* a, void* b){
    double* res = malloc(sizeof(double));
    *res = *(double*) a * *(double*) b;
    return (void*) res;
}

void printDouble(void* v){
    printf("%lf ", *(double*) v);
}

void* readDouble(){
    double* a = malloc(sizeof(double));
    int check;
    do {
        printf("Введите вещественное число: ");
        check = scanf("%lf", a);
        my_flush();
    } while ((check != 1) || (*a < -100000000 || *a > 100000000));
    return (void*) a;
}

void freeDouble(void* a){
    free(a);
}

void* doubleOne(){
    double* a = malloc(sizeof(double));
    *a = the_double_one;
    return (void*) a;
}

void* doubleZero(){
    double* a = malloc(sizeof(double));
    *a = the_double_zero;
    return (void*) a;
}

// complexRing =========================================================================================================

void* sumComplex(void* a1, void* a2){
    struct Complex* ia1 = (struct Complex*) a1;
    struct Complex* ia2 = (struct Complex*) a2;
    struct Complex* res = malloc(sizeof(struct Complex)); res->r = malloc(sizeof(double)); res->im = malloc(sizeof(double));
    *getR(res) = *getR(ia1) + *getR(ia2);
    *getIm(res) = *getIm(ia1) + *getIm(ia2);
    return (void*) res;
}

void* minusComplex(void* a){
    struct Complex* res = malloc(sizeof(struct Complex)); res->r = malloc(sizeof(double)); res->im = malloc(sizeof(double));
    *getR(res) = -*getR((struct Complex*) a);
    *getIm(res) = -*getIm((struct Complex*) a);
    return (void*) res;
}

void* multiplyComplex(void* a, const int val){
    struct Complex* res = malloc(sizeof(struct Complex)); res->r = malloc(sizeof(double)); res->im = malloc(sizeof(double));
    *getR(res) = *getR((struct Complex*) a) * val;
    *getIm(res) = *getIm((struct Complex*) a) * val;
    return (void*) res;
}

void* numbers_multiplyComplex(void* a, void* b){
    struct Complex* res = malloc(sizeof(struct Complex)); res->r = malloc(sizeof(double)); res->im = malloc(sizeof(double));
    struct Complex* ai = (struct Complex*) a;
    struct Complex* bi = (struct Complex*) b;
    *getR(res) = *getR(ai) * *getR(bi) - *getIm(ai) * *getIm(bi);
    *getIm(res) = *getR(ai) * *getIm(bi) + *getIm(ai) * *getR(bi);
    return (void*) res;
}

void printComplex(void* a){
    struct Complex* ai = (struct Complex*) a;
    printf("(%lf %lf) ", *getR(ai), *getIm(ai));
}

void* readComplex(){
    struct Complex* a = malloc(sizeof(struct Complex)); a->r = malloc(sizeof(double)); a->im = malloc(sizeof(double));
    int check;
    do {
        printf("Введите вещественную часть числа: ");
        check = scanf("%lf", getR(a));
        my_flush();
    } while ((check != 1) || (*getR(a) < -100000000 || *getR(a) > 100000000));

    do {
        printf("Введите мнимую часть числа: ");
        check = scanf("%lf", getIm(a));
        my_flush();
    } while ((check != 1) || (*getIm(a) < -100000000 || *getIm(a) > 100000000));

    return (void*) a;
}

void freeComplex(void* a){
    struct Complex* ai = (struct Complex*) a;
    free(getR(ai));
    free(getIm(ai));
    free(a);
}

void* complexOne(){
    struct Complex* a = malloc(sizeof(struct Complex)); a->r = malloc(sizeof(double)); a->im = malloc(sizeof(double));
    *getR(a) = the_double_one;
    *getIm(a) = the_double_one;
    return (void*) a;
}

void* complexZero(){
    struct Complex* a = malloc(sizeof(struct Complex)); a->r = malloc(sizeof(double)); a->im = malloc(sizeof(double));
    *getR(a) = the_double_zero;
    *getIm(a) = the_double_zero;
    return (void*) a;
}
