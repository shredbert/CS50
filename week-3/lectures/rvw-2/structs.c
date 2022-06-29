#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    int length = 2;

    person phonebook[length];

    phonebook[0].name = "Carter";
    phonebook[0].number = "+1-617-495-1000";
    phonebook[1].name = "David";
    phonebook[1].number = "+1-949-468-2750";

    string search = get_string("Enter name: ");

    for (int i = 0; i < length; i++)
    {
        if (strcmp(search, phonebook[i].name) == 0)
        {
            printf("true\n");
            return 0;
        }
    }
    printf("false\n");
    return 1;
}
