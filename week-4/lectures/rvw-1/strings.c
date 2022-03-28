#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    printf("String %s memory locations:\n", s);
    printf("Location of string itself: %p\n", s);
    printf("Location of first element: %p\n", &s[0]);
    printf("Location of second element: %p\n", &s[1]);
    printf("Location of third element: %p\n", &s[2]);
    printf("Location of fourth element: %p\n", &s[3]);
}
