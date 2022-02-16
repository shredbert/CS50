#include <cs50.h>
#include <stdio.h>
#include <string.h>

int string_length(string s);

int main(void)
{
    string name = get_string("Name: ");

    // custom
    int length = string_length(name);
    printf("%i\n", length);

    // use std lib
    int length2 = strlen(name);
    printf("%i\n", length2);
}

int string_length(string s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}
