#include <stdio.h>
#include <cs50.h>

void swap(int *x, int *y);

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");

    printf("OG: %i & %i\n", x, y);

    swap(&x, &y);

    printf("Swapped: %i & %i\n", x, y);
}

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
