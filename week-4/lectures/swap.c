#include <stdio.h>

void swap(*x, *y);

int main(void)
{
    int x = 3;
    int y = 17;

    printf("OG: x = %i, y = %i\n", x, y);

    swap(&x, &y);

    printf("New: x = %i, y = %i\n", x, y);
}

void swap(int *x, int *y)
{

}
