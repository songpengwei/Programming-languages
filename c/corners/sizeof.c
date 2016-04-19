/**
 * (0)sizeof是运算符，不是函数；
 * (1)sizeof不能求得void类型的长度；
 * (2)sizeof能求得void类型的指针的长度；
 * (3)sizeof能求得静态分配内存的数组的长度!
 * (4)sizeof不能求得动态分配的内存的大小!
 * (5)sizeof不能对不完整的数组求长度；
 * (6)当表达式作为sizeof的操作数时，它返回表达式的计算结果的类型大小，但是它不对表达式求值！
 * (7)sizeof可以对函数调用求大小，并且求得的大小等于返回类型的大小，但是不执行函数体！
 * (8)sizeof求得的结构体(及其对象)的大小并不等于各个数据成员对象的大小之和！
 * (9)sizeof不能用于求结构体的位域成员的大小，但是可以求得包含位域成员的结构体的大小！
 */
#include <stdio.h>
#include <stdlib.h>

#define dim(a) (sizeof(a)/sizeof(a[0]))
int main()
{
    int A[3][4][5];
    printf("A[3][4][5]; sizeof(A)=%d\n", sizeof(A));
    printf("dim(A)=%d\n", dim(A));

    char s[] = "12345";
    printf("s[] = \"12345\"; sizeof(s)=%d\n", sizeof(s));

    short sh[4];
    printf("short sh[4]; sizeof(sh)=%d\n", sizeof(sh));
    return 0;
}
