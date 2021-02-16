#ifndef CVEC_IMPL_H
#define CVEC_IMPL_H

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "defs.h"

#ifndef CVEC_INIT_CAPACITY
#define CVEC_INIT_CAPACITY 64
#endif



#define __CVEC_TYPE(name, type)     \
    typedef struct vec_##name##_s { \
        size_t size;                \
        size_t cap;                 \
        size_t length;              \
        type* data;                 \
    } vec_##name##_t;

#define __CVEC_IMPL(name, SCOPE, type, alloc_func, realloc_func, free_func, cmp_func)     \
    SCOPE int vec_##name##_init(vec_##name##_t **vec) {                                   \
        *vec = (vec_##name##_t *)alloc_func(sizeof(vec_##name##_t));                      \
        if (*vec == NULL) {                                                               \
            return -1;                                                                    \
        };                                                                                \
        (*vec)->cap = CVEC_INIT_CAPACITY;                                                 \
        (*vec)->size = sizeof(type);                                                      \
        (*vec)->data = (type *)alloc_func((*vec)->cap * (*vec)->size);                    \
        if ((*vec)->data == NULL) {                                                       \
            free_func(*vec);                                                              \
            *vec = NULL;                                                                  \
            return -1;                                                                    \
        }                                                                                 \
        (*vec)->length = 0;                                                               \
        return 0;                                                                         \
    }                                                                                     \
    SCOPE ssize_t vec_##name##_size(vec_##name##_t* vec) {                                \
        return (vec == NULL) ? -1 : vec->length;                                          \
    }                                                                                     \
    SCOPE ssize_t vec_##name##_capacity(vec_##name##_t* vec) {                            \
        return (vec == NULL) ? -1 : vec->cap;                                             \
    }                                                                                     \
    SCOPE int vec_##name##_at(vec_##name##_t* vec, size_t index, type* out) {             \
        if(vec == NULL || index > vec->length) {                                          \
            return -1;                                                                    \
        }                                                                                 \
        *out = vec->data[index];                                                          \
        return 0;                                                                         \
    }                                                                                     \
    SCOPE int vec_##name##_empty(vec_##name##_t* vec) {                                   \
        return (vec_##name##_size(vec) < 1) ? !0 : 0;                                     \
    }                                                                                     \
    SCOPE int vec_##name##_push(vec_##name##_t* vec, type val) {                          \
        type* data = NULL;                                                                \
        size_t oldSize;                                                                   \
        if (vec == NULL) {                                                                \
            return -1;                                                                    \
        }                                                                                 \
        if (vec->length >= vec->cap) {                                                    \
            oldSize = vec->cap * vec->size;                                                           \
            vec->cap *= 2;                                                                \
            data = realloc_func(vec->data, oldSize, vec->size * vec->cap);                \
            if (data == NULL) {                                                           \
                return -1;                                                                \
            }                                                                             \
            vec->data = data;                                                             \
        }                                                                                 \
        vec->data[vec->length] = val;                                                     \
        vec->length++;                                                                    \
        return 0;                                                                         \
    }                                                                                     \
                                                                                          \
    SCOPE int vec_##name##_pop(vec_##name##_t *vec, type *data) {                         \
        if (vec == NULL || vec->length == 0) {                                            \
            return -1;                                                                    \
        }                                                                                 \
        vec->length--;                                                                    \
        *data = vec->data[vec->length];                                                   \
        vec->data[vec->length] = 0;                                                       \
        return 0;                                                                         \
    }                                                                                     \
                                                                                          \
    SCOPE int vec_##name##_indexOf(vec_##name##_t* vec, type data) {                      \
        ssize_t index = -1;                                                               \
        if (vec == NULL || vec->length == 0) {                                            \
            return index;                                                                 \
        }                                                                                 \
        for (size_t i = 0; i < vec->length; i++) {                                        \
            if (vec->data[i] == data) {                                                   \
                index = i;                                                                \
                break;                                                                    \
            }                                                                             \
        }                                                                                 \
        return index;                                                                     \
    }                                                                                     \
                                                                                          \
    SCOPE int vec_##name##_contains(vec_##name##_t* vec, type data) {                     \
        return (vec_##name##_indexOf(vec, data) >= 0) ? !0 : 0;                           \
    }                                                                                     \
                                                                                          \
    SCOPE int vec_##name##_bsearch(vec_##name##_t* vec, type key, type* data) {           \
        if (vec == NULL || vec->length == 0) {                                            \
            return -1;                                                                    \
        }                                                                                 \
        data = (type*)bsearch(&key, vec->data, vec->length, sizeof(type), cmp_func);      \
        if (data == NULL) {                                                               \
            return -1;                                                                    \
        }                                                                                 \
        return 0;                                                                         \
    }                                                                                     \
                                                                                          \
    SCOPE void vec_##name##_free(vec_##name##_t* vec) {                                   \
        free_func(vec->data);                                                             \
        free_func(vec);                                                                   \
    }

#define vec_foreach(vec, val, code)                                                       \
    for (size_t i = 0; i < vec->length; i++) {                                            \
        val = vec->data[i];                                                               \
        code;                                                                             \
    }

#define CVEC_INIT2(name, SCOPE, type, alloc_func, realloc_func, free_func, cmp_func) \
    __CVEC_TYPE(name, type)                                                            \
    __CVEC_IMPL(name, SCOPE, type, alloc_func, realloc_func, free_func, cmp_func)

#define CVEC_INIT(name, type, cmp_func) \
    CVEC_INIT2(name, static cds_inline cds_unused, type, cds_alloc_func, cds_realloc_func, cds_free_func, cmp_func)


#define CDS_VEC_INIT(name, type, cmp_func) \
  CVEC_INIT(name, type, cmp_func)



CDS_VEC_INIT(pvoid, void*, cds_compare_pvoid)
CDS_VEC_INIT(string, char*, strcmp)
CDS_VEC_INIT(int, int, cds_compare_int)
CDS_VEC_INIT(char, char, cds_compare_int)
CDS_VEC_INIT(float, float, cds_compare_float)
CDS_VEC_INIT(double, double, cds_compare_double)





#endif
