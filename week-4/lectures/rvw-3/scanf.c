#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    printf("Int: ");
    scanf("%i", &i);
    printf("%i is stored %p\n", i, &i);

    char *s = malloc(sizeof(char) * 3);
    printf("3 chars: ");
    scanf("%s", s);
    printf("%s is located %p\n", s, s);

    char a[3];
    printf("3 chars: ");
    scanf("%s", a);
    printf("%s is located %p\n", a, a);
}
