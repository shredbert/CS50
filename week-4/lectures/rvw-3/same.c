#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    char *s1 = get_string("Enter dat string: ");
    char *s2 = get_string("Enter dat other string: ");
    
    if (strcmp(s1, s2) == 0)
    {
        printf("Same same!!!\n");
    }
    else
    {
        printf("Different...\n");
    }
}
