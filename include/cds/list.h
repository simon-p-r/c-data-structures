#ifndef CLIST_IMPL_H
#define CLIST_IMPL_H

#include "defs.h"



#define __CLIST_TYPE(name, T)                                     \
    typedef struct list_node_##name##_s list_node_##name##_t;    \
    typedef struct list_##name##_s list_##name##_t;              \
                                                                   \
    struct list_##name##_s {                                      \
        list_node_##name##_t* head;                               \
        list_node_##name##_t* tail;                               \
    };                                                             \
                                                                   \
    struct list_node_##name##_s {                                 \
        T data;                                                    \
        list_node_##name##_t* next;                               \
    };                                               



#define __CLIST_IMPL(name, SCOPE, T, alloc_func, free_func, cmp_func)     \
                                                                                \
    SCOPE int list_node_##name##_init(list_node_##name##_t** node, T data) {    \
        *node = alloc_func(sizeof(list_node_##name##_t));                       \
        if(*node == NULL) {                                                     \
            return -1;                                                          \
        }                                                                       \
        (*node)->data = data;                                                   \
        return 0;                                                               \
    }                                                                           \
                                                                                \
    SCOPE int list_##name##_init(list_##name##_t** list) {                      \
        *list = alloc_func(sizeof(list_##name##_t));                            \
        if(*list == NULL) {                                                     \
            return -1;                                                          \
        }                                                                       \
        (*list)->head = NULL;                                                   \
        return 0;                                                               \
    }                                                                           \
                                                                                \
    SCOPE ssize_t list_##name##_indexOf(list_##name##_t* list, T data) {                  \
        ssize_t index = -1, i = -1;                                                       \
        if (list == NULL || list->head == NULL) {                                         \
            return i;                                                                     \
        }                                                                                 \
        for (list_node_##name##_t* node = list->head; node; node = node->next) {          \
            ++index;                                                                      \
            if (node->data == data) {                                                     \
                break;                                                                    \
            }                                                                             \
        }                                                                                 \
        return index;                                                                     \
    }                                                                                     \
                                                                                          \
    SCOPE int list_##name##_contains(list_##name##_t* list, T data) {                     \
        return (list_##name##_indexOf(list, data) >= 0) ? !0 : 0;                         \
    }                                                                                     \
                                                                                \
    SCOPE int list_##name##_insert_head(list_##name##_t* list, T data) {        \
        list_node_##name##_t* node = NULL;                                      \
        if(list == NULL) {                                                      \
            return -1;                                                          \
        }                                                                       \
        if(list_node_##name##_init(&node, data) < 0) {                          \
            return -1;                                                          \
        }                                                                       \
        if(list->head == NULL)  {                                               \
            list->head = list->tail = node;                                     \
        } else {                                                                \
            node->next = list->head;                                            \
            list->head = node;                                                  \
        }                                                                       \
        return 0;                                                               \
    }                                                                           \
                                                                                \
    SCOPE int list_##name##_insert_tail(list_##name##_t* list, T data) {        \
        list_node_##name##_t* node = NULL;                                      \
        if(list == NULL) {                                                      \
            return -1;                                                          \
        }                                                                       \
        if(list_node_##name##_init(&node, data) < 0) {                          \
            return -1;                                                          \
        }                                                                       \
        if(list->head == NULL)  {                                               \
            list->tail = list->head = node;                                     \
        } else {                                                                \
            list->tail->next = node;                                            \
            list->tail = node;                                                  \
        }                                                                       \
        return 0;                                                               \
    }                                                                           \
                                                                                \
    SCOPE T list_##name##_remove_tail(list_##name##_t* list) {                  \
        list_node_##name##_t* node = list->tail;                                \
        T retval = node->data;                                                  \
        free_func(node);                                                        \
        node = NULL;                                                            \
        return retval;                                                          \
    }                                                                           \
                                                                                \
    SCOPE T list_##name##_remove_head(list_##name##_t* list) {                  \
        list_node_##name##_t* node = list->head;                                \
        list->head = list->head->next;                                          \
        T retval = node->data;                                                  \
        free_func(node);                                                        \
        node = NULL;                                                            \
        return retval;                                                          \
    }                                                                           \
                                                                                \
    SCOPE void list_##name##_free(list_##name##_t* list) {                      \
        list_node_##name##_t* node = list->head, *previous = NULL;              \
        while (node) {                                                          \
            previous = node;                                                    \
            node = node->next;                                                  \
            free_func(previous);                                                \
        }                                                                       \
        free_func(list);                                                        \
        list = NULL;                                                            \
    }                                                                                

#define list_foreach(list, name, code)                                          \
	list_node_##name##_t* node;                                                 \
    for (node = list->head; node != NULL; node = node->next) {                  \
        code;                                                                   \
    }

#define CDS_LIST_INIT(name, type, cmp_func)                                   \
    __CLIST_TYPE(name, type)                                        \
    __CLIST_IMPL(name, static cds_inline cds_unused, type, cds_alloc_func, cds_free_func, cmp_func)      
 


CDS_LIST_INIT(pvoid, void*, cds_compare_pvoid)
CDS_LIST_INIT(string, char*, strcmp)
CDS_LIST_INIT(int, int, cds_compare_int)
CDS_LIST_INIT(char, char, cds_compare_int)
CDS_LIST_INIT(float, float, cds_compare_float)
CDS_LIST_INIT(double, double, cds_compare_double)


#endif  // CLIST_IMPL_H

