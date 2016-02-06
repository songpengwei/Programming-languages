#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    int wc = 0;
    int state = OUT;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == '\t' || c == ' ') state = OUT;
        else if (state == OUT) {
            ++wc;
            state = IN;
        }
    }

    printf("The count of the words is %d\n", wc);

    return 0;
}
