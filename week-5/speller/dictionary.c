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
// const unsigned int N = 26;
const unsigned int N = 702;

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
    // TODO: Improve this hash function
    // Return key for input word
    // Positive int idx between 0 & N - 1 (num of buckets)
    // At least 1 char/line, alphabetical, line breaks end lines, none longer
    // than LENGTH, words all lowercase

    // // First letter
    // unsigned int key;
    // key = (toupper(word[0]) - 65);

    /*
     First 2 letters = ((first letter - 65) * 27) + (second letter - 65)
     aa = 0 (0 * 27 + 0)
     ab = 1 (0 * 27 + 1)
     ac = 2 (0 * 27 + 2)
     ad = 3 (0 * 27 + 3)
     ae = 4 (0 * 27 + 4)
     ...
     ba = 27 (1 * 27 + 0)
     bb = 28 (1 * 27 + 1)
     bc = 29 (1 * 27 + 2)
     bd = 30 (1 * 27 + 3)
     be = 31 (1 * 27 + 4)
     ...
     cx = 76 (2 * 27 + 22)
     cy = 77 (2 * 27 + 23)
     cx = 78 (2 * 27 + 24)
     cz = 79 (2 * 27 + 25)
     c' = 80 (2 * 27 + 26)
     ...
     zv = 697 (25 * 27 + 22)
     zx = 698 (25 * 27 + 23)
     zy = 699 (25 * 27 + 24)
     zz = 700 (25 * 27 + 25)
     z' = 701 (25 * 27 + 26)
     */

    unsigned int first_char, second_char, key;
    first_char = (toupper(word[0]) - 65) * 27;

    // Check if second char null & just assign first char to key if so
    if (strcmp(&word[1], "\\") == 0)
    {
        second_char = 0;
    }
    else
    {
        second_char = strcmp(&word[1], "'") ? 27 : (toupper(word[1]) - 65);
    }

    key = first_char + second_char;

    // return key;
    return key % N;
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
        unsigned int word_key = hash(buffer);

        // Point new node to current list head to set next location
        n->next = table[word_key];

        // Point list to new node to make it the new head
        table[word_key] = n;
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
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor)
        {
            bool exists = false;
            for (int j = 0; j < N; j++)
            {
                if (keys[j] == hash(cursor->word))
                {
                    exists = true;
                }
            }

            if (!exists)
            {
                keys[key_count] = hash(cursor->word);
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
