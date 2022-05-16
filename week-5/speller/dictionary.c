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
// const unsigned int N = 17576;

// Hash table
node *table[N];

// Mine -- track size
unsigned int SIZE = 0;

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
    // Words have alphabetical chars & maybe apostrophes
    // Positive int idx between 0 & N - 1 (num of buckets)
    // Some words only contain 1 or 2 letters -- how to handle?
    // At least 1/line, alphabetical, line breaks end lines, none longer than
    // LENGTH, words all lowercase, only punctuation is apostraphes but none
    // start with them
    unsigned int first_char, second_char, third_char, key;
    // printf("%s\n", word);

    key = toupper(word[0]) % 26;

    // first_char = toupper(word[0]) % 26 * 1000;
    // second_char = toupper(word[1]) % 26 * 100;
    // third_char = toupper(word[2]) % 26 * 10;

    // key = (first_char + second_char + third_char) % N;

    return key;
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

        // Mine -- increment size
        SIZE++;
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

    // Test correct keys being stored in dictionary:
    int buckets = 0;
    int keys[N];
    for (int i = 0; i < SIZE; i++)
    {
        
    }

    // Dictionary size:
    printf("size: %i\n", SIZE);
    return SIZE;
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
