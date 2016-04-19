#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[] = {1, 2, 3, 4};

    int *p1 = (int*)(&a + 1);
    int *p2 = (int*)((int *)a + 1);

    // &a是数组指针，其类型为int(*)[5];
    // 不同类型的指针+1之后增加的大小不同
    // but p1 is pointer to int, then -2
    // will be subtracted by 2
    //
    // 就是说，作为一个地址，也就是一个INT内的数值，
    // 计算机不知道怎么理解，得你告诉他，也就是强转
    // 然后指针进行加减运算的时候，按你告诉他的类型
    // 所代表的byte数进行整倍加减。
    printf("p1[-2]=%d\n", p1[-2]);
    printf("*p2=%d\n", *p2);

    return 0;
}
