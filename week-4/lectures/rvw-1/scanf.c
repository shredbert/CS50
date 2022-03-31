#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    printf("Enter int: ");
    scanf("%i", &i);
    printf("Int val: %i\n", i);
    printf("Int location: %p\n", &i);

    char *s = malloc(4);
    printf("Enter 3 char string: ");
    scanf("%s", s);
    printf("String val: %s\n", s);
    printf("String starting location: %p\n", &s);

    char c[4];
    printf("Enter 3 char string: ");
    scanf("%s", c);
    printf("String val: ");
    printf("%s\n", c);
    printf("String location: %s\n", &c[0]);
}
