// Implements a dictionary's functionality
// No altering prototypes but can add globals/funcs & otherwise alter
// dictionary files as needed

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// Can change based on hash function--hard-code indexes
const unsigned int N = 26;
// If doing first 2 chars of each word:
// const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // CASE-INSENSITIVE!!!
    // Is this word in dictionary?
    // Has to match exactly--possessives don't count
    // No hard-coding words--has to exactly match
    // Passed only alphabetical words, maybe with apostrophes
    // Can use strcasecmp for case-insensitive comparisons
    // TODO

    // Determine if word is in dictionary
    // *Case-insensitive*

    // Hash the word for idx

    // Access list using idx

    // Traverse & use strcasecmp() to check case-insensitively

    // Traversing: Use tmp var from 1^st^ item in list, move to next node based
    // on cursor->next, & loop until cursor->next == NULL
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    // Return key for input word
    // Return same hash value regardless of case
    // Take word, return idx of hash table for finding/inserting
    // Return non-negative int
    // Words have alphabetical chars & maybe apostrophes
    // Output idx between 0 & N - 1 (num of buckets)
    // *Deterministic* -> consistent
    // Can use val % N to keep idx in appropriate range
    // Can use 1^st^ letter of word = 26, 1^st^ 2 = 676, Math formula using all
    // vals of letters
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO -- read lists of dictionary words

    // Open file
    FILE *dictionary_file = fopen(dictionary, "r");

    if (dictionary_file == NULL)
    {
        printf("Error opening dictionary\n");
        return false;
    }

    // Read word into memory
    // At least 1/line, alphabetical, line breaks end lines, none longer than
    // LENGTH, words all lowercase, only punctuation is apostraphes but none
    // start with them

    char buffer[LENGTH + 1];
    node *n = NULL;

    while(fscanf(dictionary_file, "%s", buffer) != EOF)
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
        unsigned int word_key = hash(buffer);

        // Point new node to current list head to set next location
        n->next = table[word_key];

        // Point list to new node to make it the new head
        table[word_key] = n;
    }

    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Return num of words in dictionary
    // Count manually?
    // As loading, can keep track in global?
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // free() all memory previously allocated with malloc()

    // Return true if successful, false if not

    // Loop using cursor var to iterate through all indexes & related lists
    // Don't lose access to other important nodes
    // Use tmp var to hold pointer to next item--NOT recursive??
    // Can stop when cursor is null
    return false;
}
