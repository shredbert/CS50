#include <stdio.h>

void swap(int *x, int *y);

int main(void)
{
    int x = 17;
    int y = 33;

    printf("OG x: %i\n", x);
    printf("OG y: %i\n", y);

    swap(&x, &y);

    printf("NU x: %i\n", x);
    printf("NU y: %i\n", y);
}

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
