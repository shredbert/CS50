#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int length = 7;
    int numbers[] = {4, 6, 8, 2, 7, 5, 0};

    int search = get_int("Enter search: ");

    for (int i = 0; i < length; i++)
    {
        if (numbers[i] == search)
        {
            printf("true\n");
            return 0;
        }
    }
    printf("false\n");
    return 1;
}
