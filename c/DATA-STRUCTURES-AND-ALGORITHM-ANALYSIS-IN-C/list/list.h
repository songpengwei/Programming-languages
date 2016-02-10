#ifndef _List_H
#define _List_H

typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(ElementType X, List L);
ElementType Retrieve(Position P);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
void Delete(ElementType X, List L);
void DeleteList(List L);
void Insert(ElementType X, List L, Position P);
Position FindPrevious(ElementType X, List L);

#endif
