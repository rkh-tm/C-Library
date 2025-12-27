#ifndef DYNAMIC_ARRAY_H

#define DYNAMIC_ARRAY_H
#include <stdlib.h>

typedef enum DataType{
    INT, LLONG, CHAR, DYNAMIC_ARRAY
} DataType;

typedef struct DynamicArray{
    void *array;
    size_t element_size, size, capacity;
    DataType type;
} DynamicArray;

DynamicArray *initDynamicArray(const DataType type);
void pushDynamicArray(DynamicArray *ptr, const void *val);
// void *getDynamicArray(const DynamicArray *ptr, int len, int *arr, int idx);
DynamicArray *freeDynamicArray(const DynamicArray *ptr);

#endif