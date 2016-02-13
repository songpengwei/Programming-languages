1. extern关键字
在写list.h头文件的时候发现了所有函数声明都用了extern关键字修饰，但之前一直没这么用过，那么extern有什么作用？
extern本身的意思是：我在这引用或者声明一下，定义在其他源文件，所以extern外部是相对于本文件来说的。
用在函数上的确没啥作用，因为编译器可以明确的区分函数的声明（没有函数体）和定义。
但是用于变量上就有用了，因为变量的定义和声明并没有明显的区别（在写法上）。
由于声明（不会引起空间分配）和定义（会引起空间分配）是不一样的，所以需要进行区分。
回到这个问题，extern用在头文件中的函数上可能只是显式标注这是声明而已，一种好的风格。

2. 头文件中define和undef
list.h
#define T List_T
...(some declaration)
#undef T
使其中间的代码在进行实际代码生成的时候，使用List_T生成，而书写的时候 只需要写成T就行了。
所以在list.c中，如果还想用T，那么必须也得在所有用到T之前#define T List_T。

3. 函数不定参数处理
头文件#include <stdarg.h>
用法：
T List_list(void *x, ...) {
    va_list ap; 
    T list, *p = &list;

    va_start(ap, x); 
    for ( ; x; x = va_arg(ap, void*)) {
        NEW(*p);
        (*p)->first = x;
        p = &(*p)->rest;
    }   
    *p = NULL;
    va_end(ap);

    return list;                                                                                                                                     
}
调用：
T name = List_list("song", "peng", "wei", NULL);    
必须以NULL结尾，不然会出现错误，所以肯定还有其他用法，待研究。
4. 双重指针（指向指针的指针）
注意到上面的代码在新增节点的时候用的是双重指针。
而我们一般的写法，是保留对前一个链节的引用（prev），然后通过NEW(prev->rest)来新建节点。但是这么做的话一般需要引入无意义的头节点，或者额外写代码对待第一个节点。

同理适用于所有需要保存前节点的情况，如：
T List_append(T list, T tail) {
    T *p = &list;

    while (*p) {
        p = &(*p)->rest;                                                                                                                             
    }   
    *p = tail;

    return list;
}
但要注意每次迭代的是p本身而非*p.

5. fprintf(stdin, **)突然不管用了不知道为啥。自然不管用，这是in啊。。
好蠢。


