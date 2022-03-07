#include <stdlib.h>
#include <stdio.h>

// base (это база) =====================================================================================================

struct Vector{
    struct RingInfo* ringInfo;
    void* x;
    void* y;
    void* z;
};

//constants ============================================================================================================

const int the_int_zero = 0;
const int the_int_one = 1;

const double the_double_zero = 0;
const double the_double_one = 1;

// ring ================================================================================================================

struct RingInfo{
    size_t size;
    void* (*one)();
    void* (*zero)();
    void* (*read)();
    void* (*sum)(void*, void*);
    void* (*minus)(void*);
    void* (*multiply)(void*, const int);
    void (*print)(struct Vector*);
};

struct RingInfo* Create(size_t size,
        void* (*one)(), void* (*zero)(),
        void* (*read)(),
        void* (*sum)(void*, void*),
        void* (*minus)(void*),
        void* (*multiply)(void*, const int),
        void (*print)(struct Vector*))
{
    struct RingInfo* ringInfo = malloc(sizeof(struct RingInfo));
    ringInfo->one = one;
    ringInfo->zero = zero;
    ringInfo->read = read;
    ringInfo->size = size;
    ringInfo->sum = sum;
    ringInfo->minus = minus;
    ringInfo->multiply = multiply;
    ringInfo->print = print;
    return ringInfo;
}

// vector ==============================================================================================================

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
    free(v->x);
    free(v->y);
    free(v->z);
    free(v);
}

// functions ===========================================================================================================

struct Vector* sum(struct Vector* v1, struct Vector* v2) {
    struct Vector* res = malloc(sizeof(struct Vector));
    res->x = v1->ringInfo->sum(v1->x, v2->x);
    res->y = v1->ringInfo->sum(v1->y, v2->y);
    res->z = v1->ringInfo->sum(v1->z, v2->z);
    res->ringInfo = v1->ringInfo;
    return res;
}

struct Vector* minus(struct Vector* v){
    struct Vector* res = malloc(sizeof(struct Vector));
    printf("-2\n");
    res->x = v->ringInfo->minus(v->x);
    res->y = v->ringInfo->minus(v->y);
    res->z = v->ringInfo->minus(v->z);
    res->ringInfo = v->ringInfo;
    return res;
}

struct Vector* multiply(struct Vector* v, const int val){
    struct Vector* res = malloc(sizeof(struct Vector));
    res->x = v->ringInfo->multiply(v->x, val);
    res->y = v->ringInfo->multiply(v->y, val);
    res->z = v->ringInfo->multiply(v->z, val);
    res->ringInfo = v->ringInfo;
    return res;
}

void print(struct Vector* v){
    v->ringInfo->print(v);
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

void* sumInt(void* a1, void* a2)
{
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

void printInt(struct Vector* v){
    printf("%d %d %d\n", *(int*) v->x, *(int*) v->y, *(int*) v->z);
}

void* readInt(){
    int* a = malloc(sizeof(int));
    printf("Введите целое число:\n");
    scanf("%d", a);
    return (void*) a;
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

void* sumDouble(void* a1, void* a2)
{
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

void printDouble(struct Vector* v){
    printf("%lf %lf %lf\n", *(double*) v->x, *(double*) v->y, *(double*) v->z);
}

void* readDouble(){
    double* a = malloc(sizeof(double));
    printf("Введите дробное число:");
    scanf("%lf", a);
    return (void*) a;
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

