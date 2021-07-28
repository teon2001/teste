#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

typedef struct node {
    void* info;
    struct node *next;
} Node;

void *l_create() {
    return NULL;
}

static Node *conv(void *list) {
    return (Node*)list;
}

static void *create_node(void *val) {
    Node *node = malloc(sizeof(Node));
    node->info = val;
    node->next = NULL;
    return node;
}

static void *reconv(Node *list) {
    return (void*)list;
}

int l_insert_first(void **list, void *val) {
    if(val == NULL) 
        return -EINVAL;
    Node* li = conv(*list);
    Node* node = create_node(val);

    node->next = li;
    li = node;
    *list = li;
    return 0;
}

int l_insert_last(void** list, void* val) {
    if(val == NULL) 
        return -EINVAL;
    Node* li = conv(*list);
    Node* node = create_node(val);
    if(li == NULL) {
        li = node; 
        *list = li;
        return 0; 
    } 

    Node *t = li, *p = li->next;
    while(p != NULL) {
        t = t->next;
        p = p->next;
    }
    node->next = NULL;
    t->next = node;
    *list = li;
    return 0;
}

static void free_node(Node *node, void (*free_info)(void *)) {
    free_info(node->info);
    free(node);
}

static Node *aux(void **list, int idx) {
    if(list == NULL) 
        return NULL;
    Node* li = conv(*list);
    int contor = 0;
    if(idx == 0) {
        Node* s = li;
        *list = li->next;
        li->next = NULL;
        return s;
    }
    for(Node *t = li, *r = li->next; r != NULL; t = t->next, r = r->next) {
        contor++;
        if(contor == idx) {
            Node* w = r;
            t->next = r->next;
            r->next = NULL;
            return w;
        }
    }
}

void *l_remove(void **list, int idx) {
    if(idx >= l_length(*list)) 
        return NULL;
    Node* i =  aux(list, idx);
    void* j = i->info;
    free(i);
    return j;
}


void *l_remove_info(void **list, void *val, int (*comp)(void*, void*)) {
    if(list == NULL) {
        return NULL;
    }
    Node* li = conv(*list);
    int contor = 0;

    if(comp(li->info,  val) == 0) {
        
        void* s = li->info;
        *list = li->next;
        li->next = NULL;
        free(li);
        return s;
    }
    for(Node *iter1 = li, *iter2 = li->next; iter2 != NULL; iter1 = iter1->next, iter2 = iter2->next) {
        if(comp(iter2->info, val) == 0) {
            void *w = iter2->info;
            iter1->next = iter2->next;
            iter2->next = NULL;
            free(iter2);
            return w;
        }
    }
    return NULL;
}

int l_delete(void **list, int idx, void (*free_info)(void *)) {
    if(idx >= l_length(*list)) 
        return 1;
    Node *i = aux(list, idx);
    free_node(i, free_info);
    return 0;
}

void l_print(void *list, void(*print)(void*)) {
    Node *li = conv(list);
    while(li != NULL) {
        print(li->info);
        li = li->next;
    }
    printf("\n");
}

int l_contains(void *list, void *val, int (*comp)(void*, void*)) {
    // 1-lista contine val
    // 0-lista nu contine val
    Node* li = conv(list);
    for(; li != NULL; li = li->next) {
        if(comp(li->info, val) == 0) {
            return 1;
        }
    }
    return 0;
}

int l_length(void *list) {
    Node* li = conv(list);
    int contor = 0;
    while( li != NULL) {
        contor++;
        li = li->next;
    }
    return contor;
}

void l_free(void **list, void (*free_info)(void *)) {
    Node* li= conv(*list);
    while(li != NULL) {
        Node* rm = li;
        li = li->next;
        free_node(rm, free_info);
    }
    *list = NULL;
}

int l_empty(void *list) {
    return list == NULL;
}

/*
free_list   -> list.h
free_node   -> list.c
free_info   -> studenti.h
free        -> stdlib.h
*/