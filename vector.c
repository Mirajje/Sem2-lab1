#include <stdlib.h>
#include <stdio.h>

// base (это база) =====================================================================================================

struct Vector{
    struct RingInfo* ringInfo;
    void* x;
    void* y;
    void* z;
};

struct Complex{
    double* r;
    double* im;
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
    void* (*numbers_multiply)(void*, void*);
    void (*free)(void*);
    void (*print)(void*);
};

struct RingInfo* Create(size_t size,
        void* (*one)(), void* (*zero)(),
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
    ringInfo->size = size;
    ringInfo->sum = sum;
    ringInfo->minus = minus;
    ringInfo->numbers_multiply = numbers_multiply;
    ringInfo->multiply = multiply;
    ringInfo->free = free;
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
    v->ringInfo->free(v->x);
    v->ringInfo->free(v->y);
    v->ringInfo->free(v->z);
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
    res->x = v->ringInfo->minus(v->x);
    res->y = v->ringInfo->minus(v->y);
    res->z = v->ringInfo->minus(v->z);
    res->ringInfo = v->ringInfo;
    return res;
}

struct Vector* subtraction(struct Vector* v1, struct Vector* v2) {
    struct Vector* res = malloc(sizeof(struct Vector));
    void* temp;
    temp = v1->ringInfo->minus(v2->x);
    res->x = v1->ringInfo->sum(v1->x, temp);
    v1->ringInfo->free(temp);

    temp = v1->ringInfo->minus(v2->y);
    res->y = v1->ringInfo->sum(v1->y, temp);
    v1->ringInfo->free(temp);

    temp = v1->ringInfo->minus(v2->z);
    res->z = v1->ringInfo->sum(v1->z, temp);
    v1->ringInfo->free(temp);
    res->ringInfo = v1->ringInfo;
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

void scalar_multiply(struct Vector* v1, struct Vector* v2){
    void* t1; void* t2; void* t3; void* t4;
    void* res;
    t1 = v1->ringInfo->numbers_multiply(v1->x, v2->x);
    t2 = v1->ringInfo->numbers_multiply(v1->y, v2->y);
    t3 = v1->ringInfo->numbers_multiply(v1->z, v2->z);
    t4 = v1->ringInfo->sum(t1, t2);
    res = v1->ringInfo->sum(t3, t4);
    v1->ringInfo->free(t1); v1->ringInfo->free(t2); v1->ringInfo->free(t3); v1->ringInfo->free(t4);
    v1->ringInfo->print(res);
    v1->ringInfo->free(res);
    printf("\n");
}

struct Vector* vector_multiply(struct Vector* v1, struct Vector* v2){
    struct Vector* res = malloc(sizeof(struct Vector));
    void* t1; void* t2; void* t3;
    t1 = v1->ringInfo->numbers_multiply(v1->y, v2->z);
    t2 = v1->ringInfo->numbers_multiply(v1->z, v2->y);
    t3 = v1->ringInfo->minus(t2);
    res->x = v1->ringInfo->sum(t3, t1);
    v1->ringInfo->free(t1); v1->ringInfo->free(t2); v1->ringInfo->free(t3);

    t1 = v1->ringInfo->numbers_multiply(v1->z, v2->x);
    t2 = v1->ringInfo->numbers_multiply(v1->x, v2->z);
    t3 = v1->ringInfo->minus(t2);
    res->y = v1->ringInfo->sum(t3, t1);
    v1->ringInfo->free(t1); v1->ringInfo->free(t2); v1->ringInfo->free(t3);

    t1 = v1->ringInfo->numbers_multiply(v1->x, v2->y);
    t2 = v1->ringInfo->numbers_multiply(v1->y, v2->x);
    t3 = v1->ringInfo->minus(t2);
    res->z = v1->ringInfo->sum(t3, t1);
    v1->ringInfo->free(t1); v1->ringInfo->free(t2); v1->ringInfo->free(t3);

    res->ringInfo = v1->ringInfo;
    return res;
}

void print(struct Vector* v){
    v->ringInfo->print(v->x);
    v->ringInfo->print(v->y);
    v->ringInfo->print(v->z);
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
    printf("Введите целое число: ");
    scanf("%d", a);
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
    printf("Введите дробное число: ");
    scanf("%lf", a);
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

void* sumComplex(void* a1, void* a2)
{
    struct Complex* ia1 = (struct Complex*) a1;
    struct Complex* ia2 = (struct Complex*) a2;
    struct Complex* res = malloc(sizeof(struct Complex)); res->r = malloc(sizeof(double)); res->im = malloc(sizeof(double));
    *res->r = *ia1->r + *ia2->r;
    *res->im = *ia1->im + *ia2->im;
    return (void*) res;
}

void* minusComplex(void* a){
    struct Complex* res = malloc(sizeof(struct Complex)); res->r = malloc(sizeof(double)); res->im = malloc(sizeof(double));
    *res->r = -*((struct Complex*) a)->r;
    *res->im = -*((struct Complex*) a)->im;
    return (void*) res;
}

void* multiplyComplex(void* a, const int val){
    struct Complex* res = malloc(sizeof(struct Complex)); res->r = malloc(sizeof(double)); res->im = malloc(sizeof(double));
    *res->r = *((struct Complex*) a)->r * val;
    *res->im = *((struct Complex*) a)->im * val;
    return (void*) res;
}

void* numbers_multiplyComplex(void* a, void* b){
    struct Complex* res = malloc(sizeof(struct Complex)); res->r = malloc(sizeof(double)); res->im = malloc(sizeof(double));
    struct Complex* ai = (struct Complex*) a;
    struct Complex* bi = (struct Complex*) b;
    *res->r = *ai->r * *bi->r - *ai->im * *bi->im;
    *res->im = *ai->r * *bi->im + *ai->im * *bi->r;
    return (void*) res;
}

void printComplex(void* a){
    struct Complex* ai = (struct Complex*) a;
    printf("(%lf %lf) ", *ai->r, *ai->im);
}

void* readComplex(){
    struct Complex* a = malloc(sizeof(struct Complex)); a->r = malloc(sizeof(double)); a->im = malloc(sizeof(double));
    printf("Введите вещественную часть комплексного числа: ");
    scanf("%lf", a->r);
    printf("Введите мнимую часть комплексного числа: ");
    scanf("%lf", a->im);
    return (void*) a;
}

void freeComplex(void* a){
    struct Complex* ai = (struct Complex*) a;
    free(ai->r);
    free(ai->im);
    free(a);
}

void* complexOne(){
    struct Complex* a = malloc(sizeof(struct Complex)); a->r = malloc(sizeof(double)); a->im = malloc(sizeof(double));
    *a->r = the_double_one;
    *a->im = the_double_one;
    return (void*) a;
}

void* complexZero(){
    struct Complex* a = malloc(sizeof(struct Complex)); a->r = malloc(sizeof(double)); a->im = malloc(sizeof(double));
    *a->r = the_double_zero;
    *a->im = the_double_zero;
    return (void*) a;
}