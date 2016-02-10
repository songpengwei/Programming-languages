#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

struct Node {
    ElementType Element;
    Position Next;
};

int IsEmpty(List L) {
    assert(L);
    return L->Next == NULL;
}

int IsLast(Position P, List L) {
    assert(L);
    assert(P);
    return P->Next == NULL;
}

/**
 * Return: Position p, NULL if not exist
 */
Position Find(ElementType X, List L) {
    assert(L);
    Position p = L->Next;
    while (p != NULL && p->Element != X)
        p = p->Next;

    return p;
}

void Delete(ElementType X, List L) {
    assert(L);
    Position p = FindPrevious(X, L);
    if (!IsLast(p, L)) {
        Position tmp = p->Next;
        p->Next = tmp->Next;
        free(tmp);
    }
}

/**
 * Return: The previous position if found, The last
 * Element if not.
 */
Position FindPrevious(ElementType X, List L) {
    assert(L);

    Position p = L;
    while (p->Next != NULL && p->Next->Element != X)
        p = p->Next;
    return p;
}

/**
 * Warn: In this implement, L is unused, but the invoker
 * should make sure that P is in L.
 */
void Insert(ElementType X, List L, Position P) {
    assert(L);
    assert(P);

    Position tmp = NULL;
    tmp = malloc(sizeof(struct Node));
    if (tmp == NULL) {
        exit(-1);
    }

    tmp->Element = X;
    tmp->Next = P->Next;
    P->Next = tmp;
}

/**
 * Make it an empty list, that is, only header is left
 */
List MakeEmpty(List L) {
    if (L == NULL) {
        L = malloc(sizeof(struct Node));
        if (L == NULL) {
            exit(-1);
        }
        L->Next = NULL;
        L->Element = 0;
        return L;
    }
    Position p = L->Next;
    while (p != NULL) {
        Position tmp = p;
        p = p->Next;
        free(tmp);
    }
    L->Next = NULL;
    return L;
}

/**
 * After delete all the node, the invoker should assign
 * NULL to L.
 */
void DeleteList(List L) {
    assert(L);

    Position p = L->Next;
    while (p != NULL) {
        Position tmp = p;
        p = p->Next;
        free(tmp);
    }
    free(L);
}

Position Header(List L) {
    assert(L);
    return L;
}

Position First(List L) {
    assert(L);

    return L->Next;
}

ElementType Retrieve(Position P) {
    assert(P);
    return P->Element;
}
