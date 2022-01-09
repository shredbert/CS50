#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // TODO: prompt for pyramid height between 1 & 8 inclusive & rpt. until valid
    int height;
    do
    {
        height = get_int("Enter the pyramid height plz: ");
    }
    while (height < 1 || height > 8);

    // TODO: print 1 row for each height
    for (int i = 0; i < height; i++)
    {
        // TODO: print 1 col for each height, with space & (i + 1) for hashes
        for (int j = 0; j < height; j++)
        {
            if (j >= (height - 1 - i))
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

