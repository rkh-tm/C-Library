#include "../include/dynamic_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
INSTRUCTIONS

Create DynamicArray as a DynamicArray *
    DynamicArray *vector = malloc(sizeof(DynamicArray));

Initialize DynamicArray using initDynamicArray
    *vector = initDynamicArray(DataType);

Push back new values using pushDynamicArray
    pushDynamicArray(vector, &val)
    pass val by reference to enable multi-variable arguments

Access value similar to arrays
    ((DataType *)vector->array)[index]

Free DynamicArray using freeDynamicArray
    free(vector)
    vector itself must be dynamically allocated because it will be freed



Extras
    ((char *)((DynamicArray **)v->array)[0]->array)[0] to access multi-dimensional arrays
*/

void errorDynamicArray(char *s){
    fprintf(stderr, "ERROR: %s\n", s);
}

DynamicArray initDynamicArray(DataType type){
    DynamicArray arr;
    arr.size = 0;
    arr.capacity = 1;

    switch(type){
        case INT: arr.element_size = sizeof(int); break;
        case LLONG: arr.element_size = sizeof(long long); break;
        case CHAR: arr.element_size = sizeof(char); break;
        case DYNAMIC_ARRAY: arr.element_size = sizeof(DynamicArray *); break;
    }
    arr.type = type;

    arr.array = malloc(arr.element_size);

    return arr;
}

void pushDynamicArray(DynamicArray *ptr, void *val){
    if(!ptr) errorDynamicArray("Missing array");
    if(!val) errorDynamicArray("Missing value");

    if(ptr->size==ptr->capacity){
        ptr->capacity *= 2;
        ptr->array = realloc(ptr->array, ptr->capacity * ptr->element_size);
    }

    memcpy((char *)ptr->array + ptr->size * ptr->element_size, val, ptr->element_size);

    ptr->size++;

    return;
}

void *getDynamicArray(DynamicArray *ptr, int len, int *arr, int idx){
    // returns NULL if error
    if((idx<len && ptr->type!=DYNAMIC_ARRAY) || (idx==len && ptr->type==DYNAMIC_ARRAY)){
        printf("Error: Wrong dimension size\n");
        return NULL;
    }

    if(arr[idx-1]>=ptr->size || arr[idx-1]<0){
        printf("Error: Out of bounds\n");
        return NULL;
    }

    void *res;
	if(ptr->type==DYNAMIC_ARRAY){
        DynamicArray *tmp = ((DynamicArray **)ptr->array)[arr[idx-1]];
        res = getDynamicArray(tmp, len, arr, idx+1);
    }
    else{
        res = (char *)ptr->array + arr[idx-1] * ptr->element_size;
    }

	return res;
}

DynamicArray *freeDynamicArray(DynamicArray *ptr){
    if(!ptr) return NULL;

    if(ptr->type==DYNAMIC_ARRAY){
        for(int i=0; i<ptr->size; i++){
            freeDynamicArray(((DynamicArray **)ptr->array)[i]);
        }
    }

    free(ptr->array);
    free(ptr);

    return NULL;
}