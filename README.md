
# c-data-structures

Header only based macros for generic data structures. Current data structures are

    map - hashmap using khash as backend
    vec - dynamic array of generic types
    double linked list 
    singly linked list

Vec, double linked list and singly linked list structures all have predefined types for the following

    void*
    char*
    int 
    char
    float
    double


## Defining a Type

#### dlist, slist and vec
    
    CDS_VEC_INIT(vec_u8, unsigned char, CMP_FUNC)
    CDS_SLIST_INIT(slist_u8, unsigned char, CMP_FUNC)
    CDS_DLIST_INIT(dlist_u8, unsigned char, CMP_FUNC)

#### Maps

You can use one of the following defs for maps, note CDS_MAP_INIT must have a hash and cmp function passed
   
    CDS_MAP_INIT_STR(map_string_pvoid, void *)
    
    CDS_MAP_INIT_INT(map_int_pvoid, void *)

    CDS_MAP_INIT_INT64(map_int_pvoid, void *)

    CDS_MAP_INIT(map_pvoid_pvoid, void *, void *, HASH_FUNC, CMP_FUNC)




