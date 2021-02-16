#ifndef CMAP_IMPL_H
#define CMAP_IMPL_H


#include "internal/khash.h"
#include "defs.h"

#define map_foreach(map, key, val, block) {                             \
    for (khiter_t k = kh_begin(map); k < kh_end(map); ++k) {            \
        if (!kh_exist(map, k)) continue;                                \
        key = kh_key(map, k);                                           \
        val = kh_value(map, k);                                         \
        block;                                                          \
    }                                                                   \
}



#define __CMAP_TYPE(name)                                  \
   typedef khash_t(name) map_##name##_t;


#define __CMAP_IMPL(name, SCOPE, K, V)                                              \
                                                                                    \
	SCOPE int map_##name##_init(map_##name##_t** map) {					            \
        *map = kh_init(name);                                                       \
        if(*map == NULL) {                                                          \
            return -1;                                                              \
        }                                                                           \
		return 0;                                                           		\
	}																	            \
                                                                                    \
    SCOPE void map_##name##_free(map_##name##_t* map) {                             \
        kh_destroy(name, map);                                                      \
        map = NULL;                                                                 \
    }                                                                               \
                                                                                    \
    SCOPE int map_##name##_set(map_##name##_t* map, K key, V val) {                 \
        int ret;                                                                    \
        khiter_t k = kh_put(name, map, key, &ret);                                  \
        kh_value(map, k) = val;                                                     \
        return ret;                                                                 \
    }                                                                               \
                                                                                    \
    SCOPE int map_##name##_get(map_##name##_t* map, K key, V* val) {                \
        khiter_t k = kh_get(name, map, key);                                        \
        if(k == kh_end(map)) {                                                      \
            return -1;                                                              \
        }                                                                           \
        *val = kh_value(map, k);                                                    \
        return 0;                                                                   \
    }                                                                               \
                                                                                    \
    SCOPE int map_##name##_has(map_##name##_t* map, K key) {                        \
        khiter_t k = kh_get(name, map, key);                                        \
        return k != kh_end(map);                                                    \
    }                                                                               \
                                                                                    \
    SCOPE size_t map_##name##_size(map_##name##_t* map) {                           \
        return map->size;                                                           \
    }                                                                               \
                                                                                    \
    SCOPE void map_##name##_delete(map_##name##_t* map, K key) {                    \
        khiter_t k = kh_get(name, map, key);                                        \
        kh_del(name, map, k);                                                       \
    }                                                                               \
                                                                                    \
    SCOPE void map_##name##_foreach(map_##name##_t* map, void(*F)(K, V)) {          \
        khint_t __i;                                                                \
        for (__i = kh_begin(map); __i != kh_end(map); ++__i) {                      \
            if (!kh_exist(map,__i)) continue;                 						\
            F(kh_key(map,__i), kh_val(map,__i));                                    \
        }                                                                           \
    }


#define CDS_MAP_INIT_STR(name, V)             \
  KHASH_MAP_INIT_STR(name, V)              \
  __CMAP_TYPE(name)                        \
  __CMAP_IMPL(name, static cds_inline cds_unused, const char*, V)


#define CDS_MAP_INIT_INT(name, V)             \
  KHASH_MAP_INIT_INT(name, V)              \
  __CMAP_TYPE(name)                        \
  __CMAP_IMPL(name, static cds_inline cds_unused, khint32_t, V)


#define CDS_MAP_INIT_INT64(name, V)             \
  KHASH_MAP_INIT_INT64(name, V)              \
  __CMAP_TYPE(name)                          \
  __CMAP_IMPL(name, static cds_inline cds_unused, khint64_t, V)

#define CDS_MAP_INIT(name, K, V, __hash_func, __hash_equal)                       \
  KHASH_INIT(name, K, V, 1, __hash_func, __hash_equal)




#endif