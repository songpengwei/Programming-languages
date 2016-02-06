#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define NELEMS(x) ((sizeof((x))) / (sizeof((x[0]))))
#define MAXLEN 1024

static unsigned long scatter[128];
static struct atom {
    struct atom *link;
    int len;
    char *str;
} *buckets[2048];
int Atom_length(const char *str);
const char *Atom_new(const char *str, int len);
const char *Atom_string(const char *str);
const char *Atom_int(long n);


int getword(FILE *fp, char *buf, int len);
int index_tmp[100];
int ii = 0;

void init() {
    int i;
    for (i = 0; i < 128; ++i) {
        scatter[i] = rand();
    }
}

int main()
{
    init();
    char word[MAXLEN];
    while (getword(stdin, word, MAXLEN) != 0) {
        Atom_string(word);
    }

    int i;
    for (i = 0; i < 2048; ++i) {
        struct atom *p = buckets[i];
        int line = 0;
        while (p) {
            line = i;
            printf("%s ", p->str);
            p = p->link;
        }
        if (line) printf("\n");
    }

    return 0;
}

int getword(FILE *fp, char *buf, int len) {
    int i;
    char c;
    for (c = getc(fp); c != EOF && isspace(c); c = getc(fp)) ;

    ungetc(c, fp);

    for (i = 0; i < len-1 && (c = getc(fp)) != EOF && !isspace(c); ++i)
        buf[i] = c;
    if (i < len)
        buf[i] = '\0';

    //printf("%s ", buf);
    return buf[0] != '\0';
}

const char* Atom_string(const char *str) {
    assert(str);
    return Atom_new(str, strlen(str));
}

const char* Atom_int(long n) {
    char str[43];
    unsigned long m;

    if (n == LONG_MIN) {
        m = LONG_MAX + 1UL;
    } else if (n < 0) {
        m = -n;
    } else {
        m = n;
    }

    char *s = str + sizeof(str);
    do
        *--s = m % 10 + '0';
    while ((m / 10) > 0);

    if (n < 0)
        *--s = '-';
    return Atom_new(str, str + sizeof(str) - s);
}

const char *Atom_new(const char *str, int len) {
    struct atom *p;

    assert(str);
    assert(len >= 0);

    int i;
    unsigned long h;// the type!!
    for (h = 0, i = 0; i < len; ++i) {
         h = (h << 1) + scatter[(unsigned char)str[i]];
    }
    h %= NELEMS(buckets);
    for (p = buckets[h]; p; p = p->link) {
        if (p->len == len) {
            for (i = 0; i < len && p->str[i] == str[i]; ++i) ;
            if (i == len)
                return p->str;
        }
    }

    // warn for the address addition
    p = (struct atom*)malloc(sizeof(p) + sizeof(char) * (len + 1));
    //p->str = malloc(sizeof(char) * (len + 1));
    p->len = len;
    // warn!! add sizeof(p) instead of 1
    p->str = (char *) (p + sizeof(p));
    if (len > 1)
        memcpy(p->str, str, len);
    p->str[len] = '\0';

    p->link = buckets[h];
    buckets[h] = p;

    //printf("h = %d ", h);
    //printf("word = %s\n", buckets[h]->str);
    index_tmp[ii++] = h;

    return p->str;
}

int Atom_length(const char *str) {
    assert(str);

    int i;
    struct atom *p;
    unsigned long h;// the type!!
    for (h = 0, i = 0; i < len; ++i) {
         h = (h << 1) + scatter[(unsigned char)str[i]];
    }
    h %= NELEMS(buckets);
    for (p = buckets[h]; p; p = p->link) {
        if (p->str == str)
            return p->len;
    }
    assert(0);
    return 0;
}
