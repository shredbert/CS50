// Perform a linear search on an array of names

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int length = 7;
    string names[] = {"Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"};

    string search = get_string("Enter search name: ");

    for (int i = 0; i < length; i++)
    {
        if (strcmp(search, names[i]) == 0)
        {
            printf("true\n");
            return 0;
        }
    }
    printf("false\n");
    return 1;
}
