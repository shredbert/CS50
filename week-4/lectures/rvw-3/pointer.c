#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
    printf("n's location: %p\n", p);
    printf("n's OG val: %i\n", *p);
}
