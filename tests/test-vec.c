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



void test_string_vec(void) {

    int r = 0;
    vec_string_t* vec = NULL;

    char keys[VECS_LENGTH][ELEMENT_LENGTH + 1] = { 0, 0 };

    for(size_t i = 0; i < ARRAY_SIZE(keys); ++i) {
        TEST_CHECK(random_string(keys[i], ELEMENT_LENGTH) == 0);
    }

    TEST_CHECK(vec_string_init(&vec) == 0);

    TEST_CHECK(vec_string_size(NULL) == -1);

    TEST_CHECK(vec_string_capacity(NULL) == -1);

    TEST_CHECK(vec_string_empty(vec));


    for(size_t i = 0; i < ARRAY_SIZE(keys); i++) {
        char* key = keys[i];
        TEST_CHECK(vec_string_push(vec, key) != -1);
    }

    char* data = NULL;
    TEST_CHECK(vec_string_pop(vec, &data) == 0);

    TEST_CHECK(vec_string_indexOf(vec, data) == -1);

    TEST_CHECK(vec_string_push(vec, data) == 0);

    TEST_CHECK(vec_string_contains(vec, data));
    TEST_CHECK(vec_string_at(vec, 24, &data) != -1);

    TEST_CHECK(vec_string_size(vec) != -1);

    vec_string_free(vec);
}



void test_int_vec(void) {

    int r = 0;
    vec_int_t* vec = NULL;

    int keys[VECS_LENGTH] = { 0 };


    TEST_CHECK(vec_int_init(&vec) == 0);

    for(size_t i = 0; i < ARRAY_SIZE(keys); i++) {
        int key = keys[i] = rand();
        TEST_CHECK(vec_int_push(vec, key) == 0);
    }

    TEST_CHECK(vec_int_indexOf(vec, 1) != 0);

    TEST_CHECK(vec_int_size(vec) != -1);
    int key;

    vec_foreach(vec, key, {

    });

    vec_int_free(vec);
}


TEST_LIST = {
    { "string-vector", test_string_vec },
    { "int-vector", test_int_vec },
    { NULL, NULL }
};