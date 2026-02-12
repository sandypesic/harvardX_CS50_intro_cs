// Implements a dictionary's functionality

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

// Choose number of buckets in hash table
const unsigned int N = 17576; // increased for performance

// Hash table
node *table[N];

// Word counter
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert word to lowercase
    char lower[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        lower[i] = tolower(word[i]);
    }
    lower[len] = '\0';

    // Hash word
    unsigned int index = hash(lower);

    // Search linked list at that bucket
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lower) == 0)
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
    // Simple case-insensitive base-26 hash on first 3 letters
    unsigned int hash_val = 0;
    for (int i = 0; i < 3 && word[i] != '\0'; i++)
    {
        hash_val *= 26;
        hash_val += tolower(word[i]) - 'a';
    }
    return hash_val % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%45s", word) != EOF)
    {
        // Allocate new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(new_node->word, word);

        // Hash word
        unsigned int index = hash(word);

        // Insert at head of linked list
        new_node->next = table[index];
        table[index] = new_node;

        word_count++;
    }

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
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        table[i] = NULL;
    }
    return true;
}