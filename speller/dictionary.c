// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

int counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashnumber = hash(word);
    node *list = table[hashnumber];
    while (list != NULL)
    {
        if (strcasecmp(list -> word, word) == 0)
        {
            return true;
        }
        list = list -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 65;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) return false;

    char buffer[45 + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *p = malloc(sizeof(node));
        if (p == NULL) return false;
        strcpy(p -> word, buffer);
        p -> next = NULL;

        int hashnumber = hash(buffer);
        if (table[hashnumber] == NULL) table[hashnumber] = p;
        else
        {
            p -> next = table[hashnumber];
            table[hashnumber]= p;
        }
        counter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *list = table[i];
        while(list != NULL)
        {
            node *temp = list;
            list = list -> next;
            free(temp);
        }
        free(list);
    }
return true;
}
