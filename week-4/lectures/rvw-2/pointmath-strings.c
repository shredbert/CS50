#include <stdio.h>

int main(void)
{
    char *s = "HI!!!";
    printf("%s\n", s);
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));
    printf("%c\n", *(s + 3));
    printf("%c\n", *(s + 4));
}
