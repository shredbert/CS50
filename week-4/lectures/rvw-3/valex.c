#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *i = malloc(sizeof(int) * 3);
    i[1] = 17;
    i[2] = 33;
    i[3] = 45;
}
