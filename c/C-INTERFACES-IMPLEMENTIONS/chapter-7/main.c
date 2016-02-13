#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

#define T List_T

void free_element(void **x, void *cl) {
    free(*x);
}

void print_element(void **x, void *cl) {
    const char *str = (char *)*x;
    FILE *fp = cl;

    fprintf(fp, "%s\n", str);
}

int main() {
    T name = List_list("song", "peng", "wei", NULL);
    List_map(name, print_element, stdout);
    name = List_append(name, List_list("is", NULL ));
    List_map(name, print_element, stdout);
    name = List_reverse(name);
    List_map(name, print_element, stdout);
    char *x;
    name = List_pop(name, (void **)&x);
    printf("%s has been poped!\n", x);
    name = List_push(name, x);
    printf("%s has been pushed back!\n", x);
    name = List_reverse(name);
    List_map(name, print_element, stdout);



    List_free(&name);
    return 0;
}
