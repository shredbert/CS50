#include <stdio.h>

int main(void)
{
    char *s = "HI!!!";
    printf("location of string: %p\n", s);
    printf("location of string's 1st char: %p\n", &s[0]);
    printf("location of string's 2nd char: %p\n", &s[1]);
    printf("location of string's 3rd char: %p\n", &s[2]);
    printf("location of string's 4th char: %p\n", &s[3]);
    printf("location of string's 5th char: %p\n", &s[4]);
    printf("location of string's 6th char: %p\n", &s[5]);
}
