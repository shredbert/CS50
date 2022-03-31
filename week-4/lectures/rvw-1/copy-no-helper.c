#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char *s = get_string("First val: ");
    char *t = malloc(strlen(s) + 1);

    for (int i = 0, n = strlen(s) + 1; i < n; i++)
    {
        if (i == 0 && !isupper(s[i]))
        {
            t[i] = toupper(s[i]);
        }
        else
        {
            t[i] = s[i];
        }
    }

    printf("You entered: %s\n", s);
    printf("Modified: %s\n", t);

    free(t);
}
