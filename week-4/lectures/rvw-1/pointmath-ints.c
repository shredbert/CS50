#include <stdio.h>

int main(void)
{
    int i[] = {5, 7, 9, 21, 36};
    printf("%i\n", *i);
    printf("%i\n", *(i + 1));
    printf("%i\n", *(i + 2));
    printf("%i\n", *(i + 3));
    printf("%i\n", *(i + 4));
}
