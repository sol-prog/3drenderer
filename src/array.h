// Simple dynamic C array  - inspired by stb libraries
// code from my blog https://solarianprogrammer.com/2017/01/08/c99-c11-dynamic-array-mimics-cpp-vector-api-improvements/

#pragma once
#include <stdlib.h>

#define ARRAY_CREATE(T, arr) \
    T *arr = NULL;\
    do {\
        size_t *raw = malloc(2 * sizeof(size_t));\
        raw[0] = 0;\
        raw[1] = 0;\
        arr = (void *) &raw[2];\
    } while(0)

#define ARRAY_DESTROY(arr)    \
    do {\
        size_t *raw = ((size_t *) (arr) - 2);\
        free(raw);\
        arr = NULL;\
    } while(0)

#define ARRAY_SIZE(ARR) (*((size_t *) ARR - 2))
#define ARRAY_CAPACITY(ARR) (*((size_t *) ARR - 1))

#define ARRAY_PUSH(arr, value)\
    do {\
        size_t *raw = ((size_t *) (arr) - 2);\
        raw[0] = raw[0] + 1;\
        if(raw[1] == 0) {\
            raw[1] = 1;\
            raw = realloc(raw, 2 * sizeof(size_t) + raw[1] * sizeof((value)));\
            (arr) = (void *) &raw[2];\
        }\
        if(raw[0] > raw[1]) {\
            raw[1] = 2 * raw[1];\
            raw = realloc(raw, 2 * sizeof(size_t) + raw[1] * sizeof((value)));\
            (arr) = (void *) &raw[2];\
        }\
        arr[raw[0] - 1] = (value);\
    } while(0)

// size = capacity, pushing will reallocate
#define ARRAY_RESERVE(arr, reserve_capacity)\
    do {\
        size_t *raw = ((size_t *) (arr) - 2);\
        if(raw[1] == 0) {\
            raw[0] = reserve_capacity;\
            raw[1] = reserve_capacity;\
            raw = realloc(raw, 2 * sizeof(size_t) + raw[1] * sizeof((*arr)));\
            (arr) = (void *) &raw[2];\
        }\
    } while(0)

// size remains 0, so you can use push
#define ARRAY_RESERVE_CAPACITY(arr, reserve_capacity)\
    do {\
        size_t *raw = ((size_t *) (arr) - 2);\
        if(raw[1] == 0) {\
            raw[1] = reserve_capacity;\
            raw = realloc(raw, 2 * sizeof(size_t) + raw[1] * sizeof((*arr)));\
            (arr) = (void *) &raw[2];\
        }\
    } while(0)

// make size 0, capacity stays the same, does not deallocate
#define ARRAY_RESET_SIZE(arr)\
    do {\
        size_t *raw = ((size_t *) (arr) - 2);\
        raw[0] = 0;\
    } while(0)
