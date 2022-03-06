#include <stdlib.h>
#include <stdio.h>

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
    void* (*sum)(void*, void*);
    void* (*minus)(void*);
    void* (*multiply)(void*, const int*);
    void (*print)(void*);
};

struct RingInfo* Create(size_t size,
        void* (*one)(), void* (*zero)(),
        void* (*sum)(void*, void*),
        void* (*minus)(void*),
        void* (*multiply)(void*, const int*),
        void (*print)(void*))
{
    struct RingInfo* ringInfo = malloc(sizeof(struct RingInfo));
    ringInfo->one = one;
    ringInfo->zero = zero;
    ringInfo->size = size;
    ringInfo->sum = sum;
    ringInfo->minus = minus;
    ringInfo->multiply = multiply;
    ringInfo->print = print;
    return ringInfo;
}

// vector ==============================================================================================================

struct Vector{
    struct RingInfo* ringInfo;
    void* x;
    void* y;
    void* z;
};

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

void free_vector(void* v){
    free(((struct Vector*)v)->x);
    free(((struct Vector*)v)->y);
    free(((struct Vector*)v)->z);
    free(v);
}

/*struct Vector* FromKeyboard(void* values, struct RingInfo* ringInfo){
    struct Vector* vector = malloc(sizeof(struct Vector));
    printf()
    vector->x = &values[0];
    vector->y = &values[1];
    vector->z = &values[2];
    vector->ringInfo = ringInfo;
    return vector;
}*/

// single int operations ===============================================================================================

void* numSumInt(void* a1, void* a2)
{
    int* ia1 = (int*) a1;
    int* ia2 = (int*) a2;
    int* res = malloc(sizeof(int));
    *res = *ia1 + *ia2;
    return (void*) res;
}

void* numMinusInt(void* a){
    int* res = malloc(sizeof(int));
    *res = -*(int*) a;
    return (void*) res;
}

// single double operations ============================================================================================

void* numSumDouble(void* a1, void* a2)
{
    double* ia1 = (double*)a1;
    double* ia2 = (double*)a2;
    double* res = malloc(sizeof(double));
    *res = *ia1 + *ia2;
    return (void*) res;
}


void* numMinusDouble(void* a){
    double* res = malloc(sizeof(double));
    *res = -*(double*) a;
    return (void*) res;
}

// functions ===========================================================================================================

void* sum(void* v1, void* v2){
    if (((struct Vector*) v1)->ringInfo == ((struct Vector*) v2)->ringInfo){
        struct Vector* v3 = (struct Vector*) ((struct Vector*) v1)->ringInfo->sum(v1, v2);
        return (void*) v3;
    }else{
        printf("Типы векторов не совпадают");
        return NULL;
    }
}

void print(void* v){
    ((struct Vector*) v)->ringInfo->print(v);
}

void* minus(void* v){
    return ((struct Vector*) v)->ringInfo->minus(v);
}

// intRing =============================================================================================================

void* intSum(void* v1, void* v2){
    struct Vector* res = malloc(sizeof(struct Vector));
    res->x = numSumInt(((struct Vector*)v1)->x, ((struct Vector*)v2)->x);
    res->y = numSumInt(((struct Vector*)v1)->y, ((struct Vector*)v2)->y);
    res->z = numSumInt(((struct Vector*)v1)->z, ((struct Vector*)v2)->z);
    res->ringInfo = ((struct Vector*) v1)->ringInfo;
    return (void*) res;
}

void* intMinus(void* v){
    struct Vector* res = malloc(sizeof(struct Vector));
    res->x = numMinusInt(((struct Vector*) v)->x);
    res->y = numMinusInt(((struct Vector*) v)->y);
    res->z = numMinusInt(((struct Vector*) v)->z);
    res->ringInfo = ((struct Vector*) v)->ringInfo;
    return (void*) res;
}

void* intMultiply(void* v, const int* val){
    int int_x, int_y, int_z;
    int_x = *val * *(int*) ((struct Vector*)v)->x;
    int_y = *val * *(int*) ((struct Vector*)v)->y;
    int_z = *val * *(int*) ((struct Vector*)v)->z;
    ((struct Vector*)v)->x = (void*) &int_x;
    ((struct Vector*)v)->y = (void*) &int_y;
    ((struct Vector*)v)->z = (void*) &int_z;
    return v;
}

void intPrint(void* v){
    printf("%d %d %d\n", *(int*) ((struct Vector*) v)->x, *(int*) ((struct Vector*) v)->y, *(int*) ((struct Vector*) v)->z);
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

void* doubleSum(void* v1, void* v2){
    struct Vector* res = malloc(sizeof(struct Vector));
    res->x = numSumDouble(((struct Vector*)v1)->x, ((struct Vector*)v2)->x);
    res->y = numSumDouble(((struct Vector*)v1)->y, ((struct Vector*)v2)->y);
    res->z = numSumDouble(((struct Vector*)v1)->z, ((struct Vector*)v2)->z);
    res->ringInfo = ((struct Vector*) v1)->ringInfo;
    return (void*) res;
}

void doubleMinus(void* v){
    double double_x, double_y, double_z;
    double_x = -*(double*) ((struct Vector*)v)->x;
    double_y = -*(double*) ((struct Vector*)v)->y;
    double_z = -*(double*) ((struct Vector*)v)->z;
    ((struct Vector*)v)->x = (void*) &double_x;
    ((struct Vector*)v)->y = (void*) &double_y;
    ((struct Vector*)v)->z = (void*) &double_z;
}

void* doubleMultiply(void* v, const int* val){
    double double_x, double_y, double_z;
    double_x = (double) *val * *(double*) ((struct Vector*)v)->x;
    double_y = (double) *val * *(double*) ((struct Vector*)v)->y;
    double_z = (double) *val * *(double*) ((struct Vector*)v)->z;
    ((struct Vector*)v)->x = (void*) &double_x;
    ((struct Vector*)v)->y = (void*) &double_y;
    ((struct Vector*)v)->z = (void*) &double_z;
    return v;
}

void doublePrint(void* v){
    printf("%f %f %f\n", *(double*) ((struct Vector*) v)->x, *(double*) ((struct Vector*) v)->y, *(double*) ((struct Vector*) v)->z);
}

void* doubleOne(){
    return (void*) &the_double_one;
}

void* doubleZero(){
    return (void*) &the_double_zero;
}