#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool only_digits(string text);
int rotate(char text, int degrees);

int main(int argc, string argv[]) 
{
    // TODO: Validate args -- exactly 1
    if (argc != 2)
    {
        printf("Only 1 arg plz\n");
        return 1;
    }
    // TODO: Arg is positive int
    else if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // TODO: Parse arg & get plaintext
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext:  ");

    // TODO: Print ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
}

// TODO: Val int arg
bool only_digits(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (!isdigit(text[i]))
        {
            return false;
        }
    }
    return true;
}

// TODO: Cycle through alphabetical chars again if reach Z/z so NO SYMBOLS
int rotate(char text, int degrees)
{
    // Don't rotate punctuation
    if (!isalpha(text))
    {
        return text;
    }

    // A-Z = 65-90, a-z = 97-122
    int ciph_char = (int) text;
    for (int i = 0; i < degrees; i++)
    {
        if (ciph_char == 90)
        {
            ciph_char = 65;
        }
        else if (ciph_char == 122)
        {
            ciph_char = 97;
        }
        else
        {
            ciph_char++;
        }
    }
    return ciph_char;
}
