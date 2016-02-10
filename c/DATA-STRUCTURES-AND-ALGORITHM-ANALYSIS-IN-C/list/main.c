#include <stdio.h>
#include "list.h"

int main(){
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;


    List L = MakeEmpty(NULL);
    int i = 0;
    for (i = 0; i < size; ++i) {
        Insert(arr[i], L, L);
    }

    printf("The result is:");
    for (i = 0; i < size; ++i) {
        Position p = Find(arr[i], L);
        printf("Element %d, Address %x\n", arr[i], p);
    }

    DeleteList(L);
    return 0;
}
