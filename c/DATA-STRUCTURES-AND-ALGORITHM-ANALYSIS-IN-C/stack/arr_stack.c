#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arr_stack.h"

#define  EmptyTOPS (-1)
#define MinStackSize (5)

struct StackRecord{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

int IsEmpty(Stack S) {
    assert(S);
    return S->TopOfStack == EmptyTOPS;
}

int IsFull(Stack S) {
    assert(S);
    return S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack(int MaxElements) {
    if (MaxElements < MinStackSize) {
        fprintf(stderr, "Stack size is too small.\n");
        exit(-1);
    }

    Stack S = malloc(sizeof(struct StackRecord));
    assert(S);
    S->Array = (ElementType *)malloc(sizeof(ElementType) * MaxElements);
    S->Capacity = MaxElements;
    MakeEmpty(S);

    return S;
}

void DisposeStack(Stack S) {
    assert(S);
    free(S->Array);
    free(S);
}

void MakeEmpty(Stack S) {
    assert(S);
    S->TopOfStack = EmptyTOPS;
}

void Push(ElementType X, Stack S) {
    assert(S);
    if (IsFull(S)) {
        fprintf(stderr, "Push error! The stack is full.\n");
        exit(-1);
    } else {
        S->Array[++S->TopOfStack] = X;
    }
}

ElementType Top(Stack S) {
    assert(S);
    if (IsEmpty(S)) {
        fprintf(stderr, "[%s:%d] The stack is empty!\n", __FILE__, __LINE__);
        exit(-1);
    } else {
        return S->Array[S->TopOfStack];
    }
}

void Pop(Stack S) {
    assert(S);
    if (IsEmpty(S)) {
        fprintf(stderr, "[%s:%d] The stack is empty!\n", __FILE__, __LINE__);
        exit(-1);
    } else {
        --S->TopOfStack;
    }
}

ElementType TopAndPop(Stack S) {
    ElementType res = Top(S);
    Pop(S);
    return res;
}
