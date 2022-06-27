// Perform a linear search on an array of numbers

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int length = 7;
    int numbers[] = {4, 6, 8, 2, 7, 5, 0};

    int search = get_int("Please enter a search number: ");

    for (int i = 0; i < length; i++)
    {
        if (search == numbers[i])
        {
            printf("true\n");
            return 0;
        }
    }

    printf("false\n");
    return 1;
}

