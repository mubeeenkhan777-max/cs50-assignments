// Implements a dictionary's functionality
#define _GNU_SOURCE

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Number of words in dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get hash value for word
    unsigned int index = hash(word);

    // Get first node in bucket
    node *cursor = table[index];

    // Search linked list
    while (cursor != NULL)
    {
        // Compare words without considering capitalization
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2-style hash
    unsigned long hash = 5381;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = ((hash << 5) + hash) + tolower((unsigned char) word[i]);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    // Temporary storage for a word
    char word[LENGTH + 1];

    // Read every word from dictionary
    while (fscanf(file, "%45s", word) == 1)
    {
        // Allocate memory for a new node
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            // Close file
            fclose(file);

            // Free everything already loaded
            unload();

            return false;
        }

        // Copy word into new node
        strcpy(new_node->word, word);

        // Calculate hash value
        unsigned int index = hash(word);

        // Insert node at beginning of linked list
        new_node->next = table[index];
        table[index] = new_node;

        // Increase word count
        word_count++;
    }

    // Close dictionary
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful
bool unload(void)
{
    // Go through every bucket
    for (unsigned int i = 0; i < N; i++)
    {
        // Start at beginning of linked list
        node *cursor = table[i];

        // Free every node in this bucket
        while (cursor != NULL)
        {
            node *temp = cursor;

            cursor = cursor->next;

            free(temp);
        }

        // Reset bucket
        table[i] = NULL;
    }

    // Reset word count
    word_count = 0;

    return true;
}
