#ifndef OPERATOR_H
#define OPERATOR_H
#include <stdlib.h>
void *operator new(size_t size);
void operator delete(void *ptr);
#endif