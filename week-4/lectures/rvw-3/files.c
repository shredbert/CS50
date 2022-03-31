#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("\nBefore writing:\n");
    FILE *r = fopen("./phonebook.csv", "r");
    if (!r)
    {
        printf("Bad file!!!\n");
        return 2;
    }
    char c;
    while (fread(&c, sizeof(char), 1, r))
    {
        printf("%c", c);
    }
    fclose(r);

    FILE *f = fopen("./phonebook.csv", "a");
    if (!f)
    {
        printf("Bad file!!!\n");
        return 1;
    }
    char *name = get_string("Name plz: ");
    char *num = get_string("Num plz: ");
    fprintf(f, "%s,%s\n", name, num);
    fclose(f);

    printf("\nAfter writing:\n");
    fopen("./phonebook.csv", "r");
    if (!r)
    {
        printf("Bad file!!!\n");
        return 2;
    }
    while (fread(&c, sizeof(char), 1, r))
    {
        printf("%c", c);
    }
    fclose(r);
}
