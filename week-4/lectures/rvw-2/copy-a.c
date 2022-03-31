#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char *s1 = get_string("s1: ");

    int l = strlen(s1) + 1;
    char *s2 = malloc(l);

    for (int i = 0; i < l; i++)
    {
        s2[i] = s1[i];
    }

    s2[0] = toupper(s2[0]);

    printf("string 1: %s\n", s1);
    printf("string 2: %s\n", s2);

    free(s2);
}
