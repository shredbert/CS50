#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool every_alpha(string key);

int main(int argc, string argv[]) 
{
    // TODO: If argc != 2, err & exit
    if (argc != 2)
    {
        printf("Wrong num of args!\nUsage: ./substitution [alphabet key]\n");
        return 1;
    }
    // TODO: If argv[] not string w/ 26 chars OR each letter of alphabet not
    // present only once, err & exit
    else if (!every_alpha(argv[1]))
    {
        printf("Wrong key format!\nUsage: ./substitution [alphabet key]\n");
        return 1;
    }

    // TODO: Get plaintext from user
    string plaintext = get_string("plaintext: ");
    // TODO: Print cipher text for user, converting 1 char @ a time
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // TODO: Only convert alphas
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                // TODO: Equate char # to place in key array & print upper
                // A = 65
                printf("%c", toupper(argv[1][(int) plaintext[i] - 65]));
            }
            else
            {
                // TODO: Equate char # to place in key array & print lower
                // a = 97
                printf("%c", tolower(argv[1][(int) plaintext[i] - 97]));
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}

bool every_alpha(string key)
{
    // TODO: Err if not 26 letters
    if (strlen(key) != 26)
    {
        return false;
    }
    else
    {
        char letters[26];
        int letters_length = 0;
        for (int i = 0; i < strlen(key); i++)
        {
            // TODO: Err if any not alpha
            if (!isalpha(key[i]))
            {
                return false;
            }
            else
            {
                // TODO: Err if any repeated letters
                for (int j = 0; j < letters_length; j++)
                {
                    if (toupper(letters[j]) == toupper(key[i]))
                    {
                        return false;
                    }
                }
                // TODO: Add letter to array to check for dups next time around
                letters[letters_length] = key[i];
                letters_length++;
            }
        }
    }
    return true;
}
