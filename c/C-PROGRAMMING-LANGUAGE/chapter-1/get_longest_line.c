#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int max;
    int len;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while((len = get_line(line, MAXLINE)) != 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0) {
        printf("The length of longest line is:%d, \n%s\n", max, longest);
    }

    return 0;
}

int get_line(char line[], int maxline)
{
    int c, i;

    for (i = 0; i < maxline-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != EOF)
        ++i;
}
