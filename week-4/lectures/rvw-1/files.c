#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Open file
    FILE *f = fopen("./phonebook.csv", "a");
    
    // Get data from user
    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    // Print new vals to file
    if (!f)
    {
        return 1;
    }

    fprintf(f, "%s,%s\n", name, number);

    // Close file
    fclose(f);

    // Open file with different arg to read
    FILE *n = fopen("./phonebook.csv", "r");

    // Read updated file back
    if (!n)
    {
        return 2;
    }

    printf("\nFile vals:\n");

    char c;
    while (fread(&c, sizeof(char), 1, n))
    {
        printf("%c", c);
    }

    // Close file
    fclose(n);
}
