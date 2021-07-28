#include <stdio.h>
#include <assert.h>
#include "list.h"
#include "tester.h"

static void print(void* info) {
    printf("%d ", *(int*)info);
}

static void free_int(void *val) {
    ;
}

static int comp(void* a, void* b) {
    //0-egalitate
	if((*(int*)a) > (*(int*)b)) 
        return 1;
	if((*(int*)a) < (*(int*)b)) 
        return -1;
	return 0;
}

void test_insert() {
    void *list = l_create();

    l_insert_last(&list, NULL);
    l_insert_first(&list, NULL);
    assert(list == NULL);
}

void test_remove() {
    void *list = l_create();
    int a = 1, b = 2, c = 3;

    l_insert_first(&list, &a);
    l_insert_first(&list, &b);    
    l_insert_last(&list, &c);

    assert(l_length(list) == 3);
    assert(l_insert_first(&list, &a) == 0);
    assert(l_insert_first(&list, &b) == 0);
    assert(l_insert_first(&list, &c) == 0);

    void* w = l_remove(&list, (l_length(list)-1));
    assert(l_remove(&list, (l_length(list)-1)) != NULL);
}

void test_delete_empty() {
    void *list = l_create();
    int a = 1, b = 2, c = 3, d = 4;
    assert(l_empty(list) == 1);
    assert(l_insert_first(&list, &a) == 0);
    assert(l_insert_first(&list, &b) == 0);
    assert(l_insert_first(&list, &c) == 0);
    assert(l_insert_first(&list, &d) == 0);
    assert(l_empty(list) == 0);

    for(int i = 0; i < 2; i++){
        l_delete(&list, l_length(list)-1, free_int);
    }
    assert(l_delete(&list, 3, free_int) == 1);
    assert(l_length(list) == 2);
}

void test_contains_length() {
    void *list = l_create();
    int a = 1, b = 2, c = 3, d = 4;

    assert(l_insert_first(&list, &a) == 0);
    assert(l_insert_last(&list, &b) == 0);
    assert(l_insert_first(&list, &c) == 0);
    assert(l_insert_first(&list, &d) == 0);

    assert(l_contains(list, &d, comp) == 1);
    assert(l_length(list) == 4);
}