#include <stdio.h>

#include "../dictionary.h"

bool test_load();

// Test functions in dictionary.c
int main(int argc, char *argv[])
{
    printf("Load passes: %i\n", test_load());
}

bool test_load()
{
    // bool load = load(table);
    // if (!load)
    // {
    //     return false;
    // }
    return true;
}
