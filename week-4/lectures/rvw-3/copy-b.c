#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char *s1 = get_string("String to modify: ");
    char *s2 = malloc(strlen(s1) + 1);
    
    if (!s2)
    {
        printf("No memory\n");
        return 1;
    }

    strcpy(s2, s1);

    s2[0] = toupper(s2[0]);

    printf("OG: %s\n", s1);
    printf("Nu: %s\n", s2);

    free(s2);
}
