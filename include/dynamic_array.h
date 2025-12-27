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

DynamicArray *initDynamicArray(DataType type);
void pushDynamicArray(DynamicArray *ptr, void *val);
void *getDynamicArray(DynamicArray *ptr, int len, int *arr, int idx);
DynamicArray *freeDynamicArray(DynamicArray *ptr);

#endif