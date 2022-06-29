#include <stdio.h>
#include <cs50.h>

void draw(int height);

int main(void)
{
    int height = get_int("Enter height: ");
    draw(height);
}

void draw(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
