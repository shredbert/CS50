#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    char *x = get_string("Val 1: ");
    char *y = get_string("Val 2: ");

    if (strcmp(x, y) == 0)
    {
        printf("Same same!!!\n");
    }
    else
    {
        printf("Different!!!\n");
    }
}
