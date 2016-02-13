1. 结构体赋值
通过花括号可以进行逐字段赋值。
static struct descriptor {
    struct descriptor *free;
    struct descriptor *link;
    const void *ptr;
    long size;
    const char *file;
    int line;
} *htab[2048];

static struct descriptor freelist = {&freelist};
所以上述语句很好理解，就是定义一个描述符，并且将其地址赋值给其第一个字段。
也可以：static struct descriptor freelist = {&freelist, NULL, NULL, 1};   
即：可以用花括号组织各个字段的值，一起赋值给该结构体的变量。并且不能跳过某些字段，只能连续的对前面一些字段赋值。后面字段自动初始化为NULL/0/\0/0.0
另外，数组也可以通过类似方式进行赋值，这说明一段连续的内存都可以通过这种方式赋值。

2. 链表头初始化
struct List{
     struct List *next;
     int val;
};
对于一个在头部插入的链表，我们通常做法是
struct List *head = NULL;
然后，每次通过如下操作进行插入，可保证该链表尾部是一个空指针。
new_node->next = head;
head = new_node;

上条提供了另一种方法：
struct List head = {&head};
然后每次插入：
new_node->next = head.next;
head.next = new_node;
这样就是多用了一个结构体的空间，并用其作为头，其地址作为结尾。
好吧，并没有看出什么优越性；

3. assert执行效果：
a.out: test.c:5: test: Assertion `a > 0' failed.
已放弃 (core dumped)

4. 申请内存的时候：
struct descriptor *avail  = NULL;
avail = malloc(NDESCRPTORS * sizeof(struct descriptor));
和
avail = malloc(NDESCRPTORS * sizeof(*avail ));
是等价的。

5.地址对齐：
// round nbytes up to an alignments boundary     
 nbytes = (nbytes + sizeof(union align) - 1) / sizeof(union align) * sizeof(union align);
union align{
      int i;
      long l;
      long *lp;
      void *p;
      void (*fp)(void);
      float f;
      double d;
  };
使分配的地址可以容纳各种地址。

6. 手动内存管理总结
利用一个内存句柄描述符数组作为全局变量htab，辅以一个合适的hash函数进行散列。

主干函数：
Mem_alloc(nbytes)：遍历freelist，寻找大于nbytes的空闲内存块，如果有那么就切割下来一块，并且为其新申请一个描述符。如果没有呢，就新申请一块内存放入freelist表中。有个疑问：好像并没有和htab关联，只有在切分的时候才会被关联。
Mem_calloc(count, bytes)：检查参数（必须都大于0），然后调用Mem_alloc并且进行初始化。利用memset。
Mem_resize(ptr, nbytes)：利用ptr和哈希函数，在htab中找到该描述符，如果不存在报错。否则，调用Mem_alloc重新分配nbytes，并且将旧内容拷贝入新内容，注意内存尺寸（我们默认新建的内存可能会大点，但是万一人家就想要小的呢，所以需要判断）。
Mem_free(ptr)：利用ptr和哈希函数，在htab中找到该描述符，如果不存在就报错。否则，将该描述符插入freelist链表中。如果NULL，不进行处理。

内置函数：
find(ptr)：根据ptr和哈希函数找到对应描述符。
dalloc(ptr, size) ：为内存描述符分配空间，注意用到了static，每次分配时候，直接分配很多（比如512）个描述符空间，然后每次返回一个。不足后继续分配。这样避免过于频繁调用malloc。

一些宏：
#define hash(p, t) (((unsigned long)(p)>>3) &  ( (sizeof(t)/sizeof(t[0]) - 1)
散列函数，后面&是进行取模，我盘算着只有当sizeof(t)/sizeof(t[0])为2的整数次方的时候才能取正好（譬如100000-1=11111），否则取的肯定小于其应有的模。
#define NALLOC ((4096 + sizeof (union align) - 1)/ (sizeof (union align)))*(sizeof (union align))
每次多出4K空间是干啥，是为了减少对malloc的调用？

BUG：
while (bp && bp->ptr != ptr)
        bp = bp->link;  
bp->ptr != ptr写成bp->link != ptr了，不能手顺啊。

(bp = find(ptr)) == NULL
写成不等于了。

int *a = (int *)Mem_alloc(sizeof(int) * 512, __FILE__, __LINE__);
    a[8] = 9;
    printf("a[8]=%d, a[10]=%d\n", a[8], a[10]);
    a = Mem_resize(a, 1, __FILE__, __LINE__);
    a[8] = 9;
    printf("a[8]=%d, a[10]=%d\n", a[8], a[10]);
    return 0;
不会报错，因为没有利用free真正释放过内存。


