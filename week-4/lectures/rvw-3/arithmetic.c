#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    printf("chars:\n");
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));
    printf("%c\n", *(s + 3));

    printf("ints:\n");
    int i[4] = { 1, 17, 43, 69 };
    printf("%i\n", *i);
    printf("%i\n", *(i + 1));
    printf("%i\n", *(i + 2));
    printf("%i\n", *(i + 3));
}
