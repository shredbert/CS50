#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char *s = get_string("First val: ");
    char *t = malloc(strlen(s) + 1);

    // Check if any memory available -- malloc() won't work if none
    if (t == NULL)
    {
        return 1;
    }

    strcpy(t, s);

    // Check if no chars -- error during copying
    // *DON'T* need to check for blank string -- get_string() does that
    if (islower(t[0]) && strlen(t) > 0)
    {
        t[0] = toupper(s[0]);
    }

    printf("You entered: %s\n", s);
    printf("Modified: %s\n", t);
}
