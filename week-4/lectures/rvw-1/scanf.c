#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a;
    printf("int a: ");
    scanf("%i", &a);
    printf("You entered %i & stored it at %p\n", a, &a);

    char *b = malloc(sizeof(char) * 3);
    printf("3 chars b: ");
    scanf("%s", b);
    printf("You entered %s & stored it at %p\n", b, b);
    free(b);

    char c[3];
    printf("3 chars c: ");
    scanf("%s", c);
    printf("You entered %s & stored it at %p\n", c, c);
}
