#ifndef CDEFS_IMPL_H
#define CDEFS_IMPL_H

#ifndef cds_inline
#ifdef _MSC_VER
#define cds_inline __inline
#else
#define cds_inline inline
#endif
#endif /* cds_inline */

#ifndef cds_unused
#if (defined __clang__ && __clang_major__ >= 3) || \
    (defined __GNUC__ && __GNUC__ >= 3)
#define cds_unused __attribute__((__unused__))
#else
#define cds_unused
#endif
#endif /* cds_unused */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef HAVE_SSIZE
#if defined (_MSC_VER)
#if defined(_WIN64)
typedef __int64 ssize_t;
#else
typedef long ssize_t;
#endif
#endif
#else 
#include <sys/types.h>
#endif

#ifndef CDS_CALLOC
#define CDS_CALLOC(N,Z) calloc(N, Z)
#endif

#define kcalloc CDS_CALLOC

#ifndef CDS_REALLOC
#define CDS_REALLOC realloc
#endif

#define krealloc CDS_REALLOC

#ifndef CDS_MALLOC
#define CDS_MALLOC malloc
#endif

#define kmalloc CDS_MALLOC

#ifndef CDS_FREE
#define CDS_FREE free
#endif

#define kfree CDS_FREE



static cds_inline void cds_free_func(void *ptr) {
    
    if (ptr) {
        CDS_FREE(ptr);
    }
}

static cds_inline void *cds_alloc_func(size_t sz) {
    return (sz > 0 ? CDS_CALLOC(1, sz) : NULL);
}

static cds_inline void *cds_realloc_func(void *ptr, size_t oldSize, size_t newSize) {

    void *pNew = NULL;
    pNew = CDS_REALLOC(ptr, newSize);
    if (newSize > oldSize && pNew) {
        size_t diff = newSize - oldSize;
        void *pStart = ((char *)pNew) + oldSize;
        memset(pStart, 0, diff);
    }
    return pNew;
};


static cds_inline int cds_compare_pvoid(const void *a, const void *b) {
    
    if (a < b) {
        return -1;
    }
    return a > b;
}


static cds_inline int cds_compare_double(const void *a, const void *b) {
    
    if (*(const double*)a < *(const double*)b) {
        return -1;
    }
    return *(const double*)a > *(const double*)b;
}

static cds_inline int cds_compare_float(const void* a, const void* b) {

    if(*(const float*)a < *(const float*)b) {
        return -1;
    }
    return *(const float*)a > *(const float*)b;
}

static cds_inline int cds_compare_int(const void* a, const void* b) {

    if(*(const int*)a < *(const int*)b) {
        return -1;
    }
    return *(const int*)a > *(const int*)b;
};



#endif // CDEFS_IMPL_H

