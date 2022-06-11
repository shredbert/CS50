// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <math.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 18954;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get key of word for idx
    unsigned int key = hash(word);

    // Iterate over dictionary nodes @ idx
    node *cursor = table[key];
    while (cursor)
    {
        // Check if matches word
        if (strcasecmp(cursor->word, word) == 0)
        {
            // If found, return true
            return true;
        }

        cursor = cursor->next;
    }

    // Else return true
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /*
      Three letter key:
      (27^2 * char 1) + (27 * char 2) + char 3
      e.g. cat/caterpillar = 1458 + 0 + 19 = 1477
     */

    unsigned int key, first = 0, second = 0, third = 0;

    // Always at least 1 digit
    first = (toupper(word[0]) - 65) * pow(27, 2);

    if (strlen(word) >= 2)
    {
        // If second is "'", hard-code to 26
        if (strcmp(&word[1], "'") == 0)
        {
            second = 26;
        }
        else
        {
            second = (toupper(word[1]) - 65);
        }
        second = second * 27;
    }

    if (strlen(word) >= 3)
    {
        // If third is "'", hard-code to 26
        if (strcmp(&word[2], "'") == 0)
        {
            third = 26;
        }
        else
        {
            third = (toupper(word[2]) - 65);
        }
    }

    key = (first + second + third) % N;

    return key;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Read lists of dictionary words

    // Open file with NULL check
    FILE *dictionary_file = fopen(dictionary, "r");

    if (dictionary_file == NULL)
    {
        printf("Error opening dictionary\n");
        return false;
    }

    // Read word into memory
    char buffer[LENGTH + 1];
    node *n = NULL;

    while (fscanf(dictionary_file, "%s", buffer) != EOF)
    {
        // Hash each word to get key
        // Each word gets new node -- allocate with malloc(), check for NULL
        n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("Error allocating memory for list node\n");
            return false;
        }

        // Copy word to node
        strcpy(n->word, buffer);

        // Get key back from hash func
        unsigned int key = hash(buffer);

        // Point new node to current list head to set next location
        n->next = table[key];

        // Point list to new node to make it the new head
        table[key] = n;
    }

    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return num of words in dictionary

    // Iterate through all idxs
    int size = 0;
    for (int i = 0; i < N; i++)
    {
        // Iterate through all words @ idx
        node *cursor = table[i];
        while (cursor)
        {
            size++;
            cursor = cursor->next;
        }
    }

    // Dictionary size:
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over all indexes
    for (int i = 0; i < N; i++)
    {
        // Iterate over nodes with cursor & store next position in tmp
        node *cursor = table[i], *tmp;
        while (cursor)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }

    return true;
}

