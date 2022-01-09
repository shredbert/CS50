#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt for start size (min. 9)
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // Prompt for end size (gt than start)
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // Calculate number of years until we reach threshold
    int years;
    while (start < end)
    {
        start = start + (start / 3) - (start / 4);
        years++;
    }

    // Print number of years
    printf("Years: %i\n", years);
}

