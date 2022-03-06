struct RingInfo;
struct RingInfo* Create(size_t size,
                        void* (*sum)(void* a, void* b),
                        void* zero,
                        void* (*minus)(void*),
                        void* (*multiply)(void*, void*),
                        void* (*print)(void*),
                        void* one);

struct Vector;
struct Vector* From(void* values);
void* GetX(const struct Vector* vector);
void* GetY(const struct Vector* vector);
void* GetZ(const struct Vector* vector);

void* intSum(void* v1, void* v2);
void* intMinus(void* v);
void* intMultiply(void* v, void* val);
void* intPrint(void* v);
void* int_zero();
void* int_one();


