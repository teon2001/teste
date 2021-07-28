    //functia de comparare: 0 = egalitate
void *l_create();
int l_insert_first(void **list, void *val);
int l_insert_last(void **list, void* val);
int l_delete(void **list, int idx, void (*free_info)(void *));
void *l_remove(void **list, int idx);
void *l_remove_info(void **list, void *val, int (*comp)(void*, void*));
int l_contains(void *list, void *val, int (*comp)(void *, void*));
    // 1-lista contine val
    // 0-lista nu contine val
void l_print(void *list, void(*print)(void*));
int l_length(void *list);
void l_free(void **list, void (*free_info)(void *));
int l_empty(void *list);