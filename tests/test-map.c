#include <stdio.h>
#include <stdlib.h>

#include "acutest.h"

#include "cds.h"


#define KEYS_LENGTH (8192)
#define KEY_LENGTH (64)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

CDS_MAP_INIT_STR(pvoid, void*)
CDS_MAP_INIT_INT(int, char*)

static void forEach(const char* key, void* val) {

}


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



void test_string_keys(void) {

    int r = 0;
    map_pvoid_t* map = NULL;
    int val = 10;

    char keys[KEYS_LENGTH][KEY_LENGTH + 1] = { 0, 0 };

    for(size_t i = 0; i < ARRAY_SIZE(keys); ++i) {
        char* key = keys[i];
        TEST_CHECK(random_string(key, KEY_LENGTH) == 0);
    }

    TEST_CHECK(map_pvoid_init(&map) == 0);

    for(size_t i = 0; i < ARRAY_SIZE(keys); i++) {
        const char* key = keys[i];
        TEST_CHECK(map_pvoid_set(map, key, (void*)val) == 1);
        val++;
    }


    for(size_t i = 0; i < ARRAY_SIZE(keys); i++) {
        const char* key = keys[i];
        void* data = NULL;
        TEST_CHECK(map_pvoid_get(map, key, &data) == 0);
    }

    const char* key;
    void* v;
    map_foreach(map, key, v, {
        TEST_CHECK(key != NULL);
        TEST_CHECK(v != NULL);
    });


    TEST_CHECK(map_pvoid_size(map) != 0);

    map_pvoid_free(map);
}

void test_int_keys(void) {

    int r = 0;
    int count = 0;
    map_int_t* map = NULL;

    int keys[KEYS_LENGTH] = { 0 };
    char vals[KEYS_LENGTH][KEY_LENGTH + 1] = { 0, 0 };

    for(size_t i = 0; i < ARRAY_SIZE(keys); ++i) {
        TEST_CHECK(random_string(vals[i], KEY_LENGTH) == 0);
        keys[i] = count++;
    }


    TEST_CHECK(map_int_init(&map) == 0);

    for(size_t i = 0; i < ARRAY_SIZE(keys); i++) {
        int key = keys[i];
        char* val = vals[i];
        TEST_CHECK((r = map_int_set(map, key, val)) == 1);
    }

    count = 0;
    for(size_t i = 0; i < ARRAY_SIZE(keys); i++) {
        int key = count++;
        char* data = NULL;
        TEST_CHECK(map_int_get(map, key, &data) == 0);
    }

    int key;
    char* val;
    map_foreach(map, key, val, {
        TEST_CHECK(val != NULL);
    });


    TEST_CHECK(map_int_size(map) != 0);

    map_int_free(map);
}


TEST_LIST = {
    { "string-keys", test_string_keys },
    { "int-keys", test_int_keys },
    { NULL, NULL }
};
