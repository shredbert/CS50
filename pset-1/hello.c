#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // get dat input
    string name = get_string("What's you name, dewd?!\n");
    printf("Heya there, %s!!!\n", name);
}

