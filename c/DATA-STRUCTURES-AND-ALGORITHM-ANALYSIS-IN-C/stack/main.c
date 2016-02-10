#include <stdio.h>
#include "arr_stack.h"

int main() {
    Stack s = CreateStack(100);
    int arr[] = {1, 5, 6, 7, 8, 9};
    int size = 6;
    int i;
    for (i = 0; i < size; ++i) {
        Push(arr[i], s);
        printf("Push %d\n", Top(s));
    }

    while (!IsEmpty(s)) {
        printf("Pop %d\n", TopAndPop(s));
    }
    DisposeStack(s);

    return 0;
}
