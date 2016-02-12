#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

union align{
    int i;
    long l;
    long *lp;
    void *p;
    void (*fp)(void);
    float f;
    double d;
};

static struct descriptor {
    struct descriptor *free;
    struct descriptor *link;
    const void *ptr;
    long size;
    const char *file;
    int line;
} *htab[2048];

static struct descriptor freelist = {&freelist};

void print_error(const char *msg, const char *file, int line) {
    fprintf(stderr, "[ERROR][%s:%d] %s\n", file, line, msg);
    exit(-1);
}

#define hash(p, t)  (((unsigned long)(p) >> 3) & (sizeof(t) / sizeof(t[0]) - 1))
static struct descriptor *find(const void *ptr) {
    struct descriptor *bp = htab[hash(ptr, htab)];

    while (bp && bp->ptr != ptr)
        bp = bp->link;
    return bp;
}

#define NDESCRPTORS 512
static struct descriptor *dalloc(void *ptr, long size,
        const char *file, int line) {
    static struct descriptor *avail;
    static int nleft;

    // apply for descriptors of NDESCRPTORS every time.
    // to avoid generate too many memory segments
    if (nleft <= 0) {
        avail = malloc(NDESCRPTORS * sizeof(struct descriptor));
        if (avail == NULL) {
            return NULL;
        }
        nleft = NDESCRPTORS;
    }
    avail->ptr = ptr;
    avail->size = size;
    avail->file = file;
    avail->line = line;
    avail->free = avail->link = NULL;
    nleft--;

    return avail++;
}

void Mem_free(void *ptr, const char *file, int line) {
    if (ptr) {
        struct descriptor *bp;
        if (((unsigned long)ptr) % sizeof(union align) != 0 ||
                (bp = find(ptr)) == NULL || bp->free != NULL)
            print_error("the pointer is not in the address table!", file, line);
        bp->free = freelist.free;
        freelist.free = bp;
    }
}

#define NALLOC ((4096 + sizeof(union align) - 1) / \
    sizeof(union align) * sizeof(union align))
void *Mem_alloc(long nbytes, const char *file, int line) {
    assert(nbytes > 0);

    // round nbytes up to an alignments boundary
    nbytes = (nbytes + sizeof(union align) - 1) /
            sizeof(union align) * sizeof(union align);

    struct descriptor *bp;
    void *ptr;
    for (bp = freelist.free; bp; bp = bp->free) {
        if (bp->size > nbytes) {
            //  cut nbytes memory and allocate a new descriptor
            bp->size -= nbytes;
            ptr = (char *)bp->ptr + bp->size;
            if ((bp = dalloc(ptr, nbytes, file, line)) != NULL) {
                unsigned h = hash(ptr, htab);
                bp->link = htab[h];
                htab[h] = bp;
                return ptr;
            } else {
                print_error("Allocate memory for descriptor error!", __FILE__, __LINE__);
            }
        }

        if (bp == &freelist) {
            struct descriptor *newptr;
            if ((ptr = malloc(nbytes + NALLOC)) == NULL ||
                    (newptr = dalloc(ptr, nbytes + NALLOC,
                                      __FILE__, __LINE__)) == NULL)
                print_error("Allocate memory for descriptor error!", __FILE__, __LINE__);
            newptr->free = freelist.free;
            freelist.free = newptr;
        }
    }

    assert(0);
    return NULL;
}

void *Mem_resize(void *ptr, long nbytes, const char *file, int line) {
    assert(ptr);
    assert(nbytes > 0);

    struct descriptor *bp;
    if (((unsigned long)ptr) % sizeof(union align) != 0 ||
            (bp = find(ptr)) == NULL || bp->free != NULL)
        print_error("the pointer is not in the address table!", file, line);

    void *newptr = Mem_alloc(nbytes, file, line);
    memcpy(newptr, ptr,
            nbytes < bp->size ? nbytes : bp->size);
    Mem_free(ptr, file, line);
    return newptr;
}

void *Mem_calloc(long count, long nbytes, const char *file, int line) {
    assert(count > 0);
    assert(nbytes > 0);

    void *ptr = Mem_alloc(count*nbytes, file, line);
    memset(ptr, '\0', count*nbytes);
    return ptr;
}

int main()
{
    int *a = (int *)Mem_alloc(sizeof(int) * 512, __FILE__, __LINE__);
    a[8] = 9;
    printf("a[8]=%d, a[10]=%d\n", a[8], a[10]);
    a = Mem_resize(a, 1, __FILE__, __LINE__);
    a[8] = 9;
    printf("a[8]=%d, a[10]=%d\n", a[8], a[10]);
    return 0;
}



