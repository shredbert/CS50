#include <stdlib.h>

int main(void)
{
    int *i = malloc(3 * sizeof(int));
    i[1] = 5;
    i[2] = 7;
    i[3] = 9;
}
