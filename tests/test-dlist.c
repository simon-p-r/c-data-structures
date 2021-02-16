#include <stdio.h>
#include <stdlib.h>

#include "acutest.h"

#include "cds.h"


#define VECS_LENGTH (8192)
#define ELEMENT_LENGTH (64)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))



static int random_string(char *buf, size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    if(length == 0) {
        return -1;
    } 
    if(buf == NULL) {
        return -1;
    }

    int l = (int) (sizeof(charset) -1);
    for (size_t n = 0; n < length; n++) {
        int key = rand() % l;          // per-iteration instantiation
        buf[n] = charset[key];
    }

    buf[length] = '\0';
    return 0;
}




void test_dlist_strings(void) {
    
    int r = 0;
    dlist_string_t* dlist = NULL;

    char keys[VECS_LENGTH][ELEMENT_LENGTH + 1] = { 0, 0 };

    for(size_t i = 0; i < ARRAY_SIZE(keys); ++i) {
        TEST_CHECK(random_string(keys[i], ELEMENT_LENGTH) == 0);
    }

    TEST_CHECK(dlist_string_init(&dlist) == 0);

    for(size_t i = 0; i < ARRAY_SIZE(keys); i++) {
        char* key = keys[i];
        TEST_CHECK(dlist_string_insert_head(dlist, key) == 0);
    }


    dlist_string_free(dlist);

}

void test_dlist_int(void) {
    
    int r = 0;
    dlist_int_t* dlist = NULL;

    int keys[VECS_LENGTH] = { 0 };


    TEST_CHECK(dlist_int_init(&dlist) == 0);

    for(size_t i = 0; i < ARRAY_SIZE(keys); i++) {
        int key = keys[i] = rand();
        TEST_CHECK(dlist_int_insert_head(dlist, key) == 0);
    }


    // TEST_CHECK(dlist_int_size(dlist) != 0);

    dlist_int_free(dlist);

}




TEST_LIST = {
    { "dlist-strings", test_dlist_strings },
    { "dlist-int",     test_dlist_int },
    { NULL, NULL }
};







