#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    FILE *fw = fopen("./phonebook.csv", "a");
    if (!fw)
    {
        printf("Bad file!!!\n");
        return 1;
    }
    char *name = get_string("Name: ");
    char *number = get_string("Number: ");
    fprintf(fw, "%s,%s\n", name, number);
    fclose(fw);

    FILE *fr = fopen("./phonebook.csv", "r");
    if (!fr)
    {
        printf("Bad file!!!\n");
        return 2;
    }
    char c;
    while (fread(&c, sizeof(char), 1, fr))
    {
        printf("%c", c);
    }
    fclose(fr);
}
