// Implements a dictionary's functionality
// No altering prototypes but can add globals/funcs & otherwise alter
// dictionary files as needed

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

// Test
void print_keys();

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
// const unsigned int N = 26; // single char key
const unsigned int N = 18954; // triple char key

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    /*
     *  TODO CASE-INSENSITIVE!!! Is this word in dictionary? Alphabetical &
     *  apostraphes (apostraphes don't start tho) Use strcasecmp() for
     *  case-insensitive comparisons Determine if word is in dictionary Hash
     *  the word for idx Access list using idx Traverse & use strcasecmp() to
     *  check case-insensitively Traversing: Use tmp var from 1^st^ item in
     *  list, move to next node based on cursor->next, & loop until
     *  cursor->next == NULL
     */

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
     First 3 letters = ((first letter upper - 65) * 27^2) + ((second letter
         upper - 65) * 27) + (third letter upper - 65)
     First 2 letters = ((first letter upper - 65) * 27) + (second letter upper
         - 65)
     First 1 letter upper = first letter upper - 65
     e.g. cat/caterpillar: 67 - 65 = 2, 65 - 65 = 0, 84 - 65 = 19
     2 * 27^2 = 1458
     0 * 27 = 0
     19
     idx = 1477???
     */

    // TODO: Improve this hash function
    // Return key for input word
    // Positive int idx between 0 & N - 1 (num of buckets)
    // At least 1 char/line, alphabetical, line breaks end lines, none longer
    // than LENGTH, words all lowercase IN DICTIONARY (not in text)


    // Store key
    unsigned int key;

    // // Single letter key

    // key = (toupper(word[0]) - 65);
    // return key;

    // Three letter key

    // 1 char words only subtract
    if (strcmp(&word[1], "\\") == 0)
    {
        // Single char is same as "a..." preceding
        key = (toupper(word[0] - 65));
    }
    // Check if word is 2 chars
    else if (strcmp(&word[2], "\\") == 0)
    {
        // Double char is same as "aa..." preceding
        key = ((toupper(word[0] - 65)) * 27) +
              strcmp(&word[1], "'") ? 26 : (word[1] - 97);
    }
    // Else word is 3+ chars
    else
    {
        key = ((toupper(word[0] - 65)) * 27^2) +
              (strcmp(&word[1], "'") ? 26 : ((word[1] - 97) * 27)) +
              (strcmp(&word[2], "'") ? 26 : (word[2] - 97));
    }
    return key;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Read lists of dictionary words

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

    // Test
    print_keys();

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    /*
    * Return num of words in dictionary
    * Count manually
    */

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
    /*
     * free() all memory previously allocated with malloc()
     * Return true if successful, false if not
     * Loop using cursor var to iterate through all indexes & related lists
     * Don't lose access to other important nodes
     * Use tmp var to hold pointer to next item--NOT recursive??
     * Can stop when cursor is null
     */

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

// Test
void print_keys()
{
    int key_count = 0;
    char keys[N];
    // Iterate through all possible keys to check words for their keys
    for (int i = 0; i < N; i++)
    {
        // Buffer node
        node *cursor = table[i];
        while (cursor)
        {
            bool exists = false;
            unsigned int key = hash(cursor->word);

            // Iterate through keys to check if in use for existing word
            for (int j = 0; j < key_count; j++)
            {
                if (keys[j] == key)
                {
                    exists = true;
                }
            }

            // Add keys to array of keys if not existing
            if (!exists)
            {
                keys[key_count] = key;
                key_count++;
            }
            cursor = cursor->next;
        }
    }

    printf("keys: %i\n", key_count);
    for (int i = 0; i < key_count; i++)
    {
        printf("%i\n", keys[i]);
    }
}
