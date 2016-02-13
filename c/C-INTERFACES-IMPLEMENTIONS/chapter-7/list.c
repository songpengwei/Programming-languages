#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"
#define T List_T

#define NEW(x) (x = malloc(sizeof(*x)))
#define FREE(x) (free(x))

void error_exit(const char *msg, const char *file, int line) {
    fprintf(stderr, "[ERROR] [%s:%d] %s\n", file, line, msg);
    exit(-1);
}

T List_push(T list, void *x) {
    T p;

    NEW(p);
    if (p == NULL)
        error_exit("Allocate space when push error.", __FILE__, __LINE__);
    p->first = x;
    p->rest = list;

    return p;
}

T List_list(void *x, ...) {
    va_list ap;
    T list, *p = &list;

    va_start(ap, x);
    for ( ; x; x = va_arg(ap, void*)) {
        NEW(*p);
        (*p)->first = x;
        p = &(*p)->rest;
    }
    *p = NULL;
    va_end(ap);

    return list;
}

T List_append(T list, T tail) {
    T *p = &list;

    while (*p) {
        p = &(*p)->rest;
    }
    *p = tail;

    return list;
}

T List_copy(T list) {
    T head, *p = &head;

    while (list) {
        NEW(*p);
        (*p)->first = list->first;

        list = list->rest;
        p = &(*p)->rest;
    }
    *p = NULL;

    return head;
}

T List_pop(T list, void **x) {
    if (list == NULL)
        error_exit("List is empty, can't pop!", __FILE__, __LINE__);

    T head = list->rest;

    *x = list->first;
    FREE(list);
    return head;
}

T List_reverse(T list) {
    T head = NULL;

    while (list) {
        T node = list;
        list = list->rest;

        node->rest = head;
        head = node;
    }

    return head;
}

int List_length(T list) {
    int n;
    for (n = 0; list; list = list->rest) {
        ++n;
    }

    return n;
}

void List_free(T *list) {
    assert(list);

    T node;
    while (*list) {
        node = *list;
        list = &(*list)->rest;

        FREE(node);
    }
}

void List_map(T list,
        void apply(void **x, void *cl), void *cl) {
    assert(apply);
    for ( ; list; list = list->rest) {
        apply(&list->first, cl);
    }
}

void **List_toArray(T list, void *end) {
    int i, n = List_length(list);

    void **array = (void *)malloc(sizeof(*array) * (n + 1));
    for (i = 0; i < n; ++i) {
        array[i] = list->first;
        list = list->rest;
    }
    array[i] = end;

    return array;
}
