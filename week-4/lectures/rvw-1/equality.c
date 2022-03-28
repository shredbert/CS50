#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    char *s1 = get_string("s1: ");
    char *s2 = get_string("s2: ");

    if (strcmp(s1, s2) == 0)
    {
        printf("Same same!!!\n");
    }
    else
    {
        printf("Diff diff!!!\n");
    }
}
