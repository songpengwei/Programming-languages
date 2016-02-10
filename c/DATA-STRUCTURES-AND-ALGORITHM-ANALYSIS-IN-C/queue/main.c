#include <stdio.h>

#include "queue.h"

struct QueueRecord {
    int Capacity;
    int Size;
    int Front;
    int Rear;
    ElementType *Array;
};
int main()
{
    Queue q = CreateQueue(10);

    int size = 7;
    int arr[] = {1, 3, 4, 6, 7, 2, 11};

    int i;
    for (i = 0; i < size; ++i) {
        Enqueue(arr[i], q);
        printf("Enqueue %d\n", arr[i]);
    }
    printf("The size of queue is %d\n", q->Size);
    for (i = 0; i < size; ++i) {
        printf("Dequeue %d\n", FrontAndDequeue(q));
    }
    printf("The size of queue is %d\n", q->Size);
    printf("The front position of queue is %d\n", q->Front);
    printf("The rear position of queue is %d\n", q->Rear);

    DisposeQueue(q);
    return 0;
}
