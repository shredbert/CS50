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
    person phonebook[2];
    phonebook[0].name = "Carter";
    phonebook[0].number = "+1-617-495-1000";
    phonebook[1].name = "David";
    phonebook[1].number = "+1-949-468-2750";

    int length = 2;
    string search = get_string("Enter search name: ");

    for (int i = 0; i < length; i++)
    {
        if (strcmp(phonebook[i].name, search) == 0)
        {
            printf("Found!!!\n");
            return 0;
        }
    }
    printf("Not found!!!\n");
    return 1;
}
