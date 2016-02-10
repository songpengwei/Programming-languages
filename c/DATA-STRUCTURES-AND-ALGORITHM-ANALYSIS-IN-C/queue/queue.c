#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

struct QueueRecord {
    int Capacity;
    int Size;
    int Front;
    int Rear;
    ElementType *Array;
};

int IsEmpty(Queue Q) {
    assert(Q);
    return Q->Size == 0;
}

int IsFull(Queue Q) {
    assert(Q);
    return Q->Size == Q->Capacity;
}

Queue CreateQueue(int MaxElements) {
    assert(MaxElements > 0);
    Queue Q = (Queue) malloc(sizeof(struct QueueRecord));
    Q->Array = (ElementType *) malloc(sizeof(ElementType) * MaxElements);
    Q->Size = 0;
    Q->Capacity = MaxElements;
    Q->Rear = 0;
    Q->Front = 1;

    return Q;
}

void DisposeQueue(Queue Q) {
    assert(Q);
    free(Q->Array);
    free(Q);
}

void MakeEmpty(Queue Q) {
    assert(Q);
    Q->Size = 0;
    Q->Rear = 0;
    Q->Front = 1;
}

static int Succ(int Value, Queue Q) {
    assert(Q);

    if (++Value == Q->Capacity) {
        Value = 0;
    }
    return Value;
}

void Enqueue(ElementType X, Queue Q) {
    assert(Q);

    if (IsFull(Q)) {
        fprintf(stderr, "Queue is full!\n");
        exit(-1);
    }

    Q->Size++;
    Q->Rear = Succ(Q->Rear, Q);
    Q->Array[Q->Rear]= X;
}

ElementType Front(Queue Q) {
    assert(Q);
    if (IsEmpty(Q)) {
        fprintf(stderr, "Queue is empty!\n");
        exit(-1);
    }
    return Q->Array[Q->Front];
}

void Dequeue(Queue Q) {
    assert(Q);

    if (IsEmpty(Q)) {
        fprintf(stderr, "Queue is empty, can't dequeue!");
        exit(-1);
    }

    Q->Size--;
    Q->Front = Succ(Q->Front, Q);
}

ElementType FrontAndDequeue(Queue Q) {
    assert(Q);

    ElementType result = Front(Q);
    Dequeue(Q);

    return result;
}
