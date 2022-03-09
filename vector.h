#include <stdio.h>

const int the_int_zero;
const int the_int_one;
const double the_double_zero;
const double the_double_one;

struct Complex;
double* getR(struct Complex* v);
double* getIm(struct Complex* v);

struct RingInfo;
struct RingInfo* Create(void* (*one)(), void* (*zero)(),
                        void* (*read)(),
                        void* (*sum)(void*, void*),
                        void* (*minus)(void*),
                        void* (*multiply)(void*, const int),
                        void* (*numbers_multiply)(void*, void*),
                        void (*free)(void*),
                        void (*print)(void*));

struct Vector;
void* getX(struct Vector* v);
void* getY(struct Vector* v);
void* getZ(struct Vector* v);
struct RingInfo* getRingInfo(struct Vector* v);
struct Vector* E1(struct RingInfo*);
struct Vector* E2(struct RingInfo*);
struct Vector* E3(struct RingInfo*);
struct Vector* FromKeyboard(struct RingInfo*);
void free_vector(struct Vector*);


struct Vector* sum(struct Vector*, struct Vector*);
struct Vector* minus(struct Vector*);
struct Vector* subtraction(struct Vector*, struct Vector*);
struct Vector* multiply(struct Vector*, int);
void scalar_multiply(struct Vector*, struct Vector*);
struct Vector* vector_multiply(struct Vector*, struct Vector*);
void print(struct Vector*);


void free_mas(struct Vector**, int*);
struct Vector** push_back(struct Vector**, int*, struct Vector*);
struct Vector** delete(struct Vector**, int*, int);
void print_mas(struct Vector**, int*);


void* sumInt(void*, void*);
void* minusInt(void*);
void* multiplyInt(void*, int);
void* numbers_multiplyInt(void*, void*);
void printInt(void*);
void* readInt();
void freeInt(void*);
void* intOne();
void* intZero();

void* sumDouble(void*, void*);
void* minusDouble(void*);
void* multiplyDouble(void*, int);
void* numbers_multiplyDouble(void*, void*);
void printDouble(void*);
void* readDouble();
void freeDouble(void*);
void* doubleOne();
void* doubleZero();

void* sumComplex(void*, void*);
void* minusComplex(void*);
void* multiplyComplex(void*, int);
void* numbers_multiplyComplex(void*, void*);
void printComplex(void*);
void* readComplex();
void freeComplex(void*);
void* complexOne();
void* complexZero();