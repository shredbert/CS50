#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");

    if (x < y)
    {
        printf("Less than!");
    }
    else if (x > y)
    {
        printf("Greate than!");
    }
    else {
        printf("Equals!!!");
    }
}
