#ifndef CDLIST_IMPL_H
#define CDLIST_IMPL_H

#include "defs.h"

// Raw unlink operation. Unlinks the two items.
#define dlist_node_break(a) do { \
    if (!a) break; \
    if (a->next) a->next->prev = a->prev; \
    if (a->prev) a->prev->next = a->next; \
    a->prev = NULL; \
    a->next = NULL; \
} while (0)


#define dlist_node_link(a, b) do { \
    if (a) a->next = b; \
    if (b) b->prev = a; \
} while (0)


#define __CDLIST_TYPE(name, T)                                     \
    typedef struct dlist_node_##name##_s dlist_node_##name##_t;    \
    typedef struct dlist_##name##_s dlist_##name##_t;              \
                                                                   \
    struct dlist_##name##_s {                                      \
        dlist_node_##name##_t* head;                               \
        dlist_node_##name##_t* tail;                               \
    };                                                             \
                                                                   \
    struct dlist_node_##name##_s {                                 \
        T data;                                                    \
        dlist_node_##name##_t* next;                               \
        dlist_node_##name##_t* prev;                               \
    };                                               



#define __CDLIST_IMPL(name, SCOPE, T, alloc_func, free_func, cmp_func)     \
                                                                                \
    SCOPE int dlist_node_##name##_init(dlist_node_##name##_t** node, T data) {  \
        *node = alloc_func(sizeof(dlist_node_##name##_t));                      \
        if(*node == NULL) {                                                     \
            return -1;                                                          \
        }                                                                       \
        (*node)->data = data;                                                   \
        return 0;                                                               \
    }                                                                           \
                                                                                \
    SCOPE int dlist_##name##_init(dlist_##name##_t** list) {                    \
        *list = alloc_func(sizeof(dlist_##name##_t));                           \
        if(*list == NULL) {                                                     \
            return -1;                                                          \
        }                                                                       \
        return 0;                                                               \
    }                                                                           \
                                                                                \
    SCOPE int dlist_##name##_insert_head(dlist_##name##_t* list, T data) {      \
        dlist_node_##name##_t* node = NULL;                                     \
        if(list == NULL) {                                                      \
            return -1;                                                          \
        }                                                                       \
        if(dlist_node_##name##_init(&node, data) < 0) {                         \
            return -1;                                                          \
        }                                                                       \
        dlist_node_link(node, list->head);                                      \
        list->head = node;                                                      \
        if (!list->tail) {                                                      \
            list->tail = node;                                                  \
        }                                                                       \
        return 0;                                                               \
    }                                                                           \
                                                                                          \
    SCOPE ssize_t dlist_##name##_indexOf(dlist_##name##_t* list, T data) {                \
        ssize_t index = -1, i = -1;                                                       \
        if (list == NULL || list->head == NULL) {                                         \
            return i;                                                                     \
        }                                                                                 \
        for (dlist_node_##name##_t* node = list->head; node; node = node->next) {         \
            ++index;                                                                      \
            if (node->data = data) {                                                      \
                break;                                                                    \
            }                                                                             \
        }                                                                                 \
        return index;                                                                     \
    }                                                                                     \
    SCOPE int dlist_##name##_contains(dlist_##name##_t* list, T data) {                   \
        return (dlist_##name##_indexOf(list, data) >= 0) ? !0 : 0;                        \
    }                                                                                     \
                                                                                \
    SCOPE int dlist_##name##_insert_tail(dlist_##name##_t* list, T data) {      \
        dlist_node_##name##_t* node = NULL;                                     \
        if(list == NULL) {                                                      \
            return -1;                                                          \
        }                                                                       \
        if(dlist_node_##name##_init(&node, data) < 0) {                         \
            return -1;                                                          \
        }                                                                       \
        dlist_node_link(list->tail, node);                                      \
        list->tail = node;                                                      \
        if (!list->head) {                                                      \
            list->head = node;                                                  \
        }                                                                       \
        return 0;                                                               \
    }                                                                           \
                                                                                \
    SCOPE T dlist_##name##_remove_tail(dlist_##name##_t* list) {                \
        dlist_node_##name##_t* node = list->tail;                               \
        list->tail = list->tail->prev;                                          \
        T retval = node->data;                                                  \
        dlist_node_break(node);                                                 \
        free_func(node);                                                        \
        return retval;                                                          \
    }                                                                           \
                                                                                \
    SCOPE T dlist_##name##_remove_head(dlist_##name##_t* list) {                \
        dlist_node_##name##_t* node = list->head;                               \
        list->head = list->head->next;                                          \
        dlist_node_break(node);                                                 \
        T retval = node->data;                                                  \
        free_func(node);                                                        \
        return retval;                                                          \
    }                                                                           \
                                                                                \
    SCOPE void dlist_##name##_free(dlist_##name##_t* list) {                    \
        dlist_node_##name##_t* node = list->head, *previous = NULL;             \
        while (node) {                                                          \
            previous = node;                                                    \
            node = node->next;                                                  \
            free_func(previous);                                                \
        }                                                                       \
        free_func(list);                                                        \
    }
                                                                                

#define dlist_foreach(list, name, code)                                      \
	dlist_node_##name##_t* node;                                             \
    for (node = list->head; node != NULL; node = node->next) {               \
        code;                                                                \
    }

#define dlist_foreach_rev(list, name, code)                                  \
	dlist_node_##name##_t* node;                                             \
    for (name = list->tail; name != NULL; name = name->prev) {               \
        code;                                                                \
    }

                                                     


#define CDS_DLIST_INIT(name, type, cmp_func)             \
    __CDLIST_TYPE(name, type)                                                \
    __CDLIST_IMPL(name, static cds_inline cds_unused, type, cds_alloc_func, cds_free_func, cmp_func)


CDS_DLIST_INIT(pvoid, void*, cds_compare_pvoid)
CDS_DLIST_INIT(string, char*, strcmp)
CDS_DLIST_INIT(int, int, cds_compare_int)
CDS_DLIST_INIT(char, char, cds_compare_int)
CDS_DLIST_INIT(float, float, cds_compare_float)
CDS_DLIST_INIT(double, double, cds_compare_double)

#endif  // CDLIST_IMPL_H
