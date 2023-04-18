#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

static unsigned int hash_string(const char *str);
/**************************************************************
 * @function hash_string                                      *
 * @description Hashes a string using the djb2 algorithm.     *
 *                                                            *
 * @param str The string to be hashed.                        *
 * @output The hash value of the string.                      *
 *************************************************************/

HashTable *create_hash_table(unsigned int capacity)
{
    // Allocate memory for the HashTable struct
    HashTable *table = malloc(sizeof(HashTable));
    if (table == NULL)
    {
        return NULL;
    }

    // Allocate memory for the HashTableEntry structs
    table->entries = malloc(capacity * sizeof(HashTableEntry));
    if (table->entries == NULL)
    {
        // Free the memory we already allocated
        free(table);
        return NULL;
    }

    // Set the capacity and size
    table->capacity = capacity;
    table->size = 0;

    // Initialize each entry in the table
    for (unsigned int i = 0; i < capacity; i++)
    {
        table->entries[i].key = NULL;
        table->entries[i].value = NULL;
        table->entries[i].next = NULL;
    }

    return table;
}

/*************************************************************************
 * @function destroy_hash_table                                          *
 * @description Frees the memory allocated for a hash table.             *
 *                                                                       *
 * @param table Pointer to the hash table to be freed.                   *
 * @output None (The memory allocated for the hash table will be freed.) *
 *************************************************************************/

void destroy_hash_table(HashTable *table)
{
    // Check if the table or entries are NULL, and return if so.
    if (table == NULL)
    {
        return;
    }
    if (table->entries == NULL)
    {
        free(table);
        return;
    }
    // Iterate through the entries of the table, and free them.
    for (unsigned int i = 0; i < table->capacity; i++)
    {
        HashTableEntry *entry = &(table->entries[i]);
        while (entry != NULL)
        {
            HashTableEntry *next_entry = entry->next;
            free(entry->key);
            free(entry);
            entry = next_entry;
        }
    }
    // Free the entries and the table itself.
    free(table->entries);
    free(table);
}

/*************************************************************
 * @function hash_table_put                                  *
 * @description Adds a key to a hash table.                  *
 *                                                           *
 * @param table Pointer to the hash table.                   *
 * @param key The key to be added to the hash table.         *
 * @output 1 if the key was added successfully, 0 otherwise. *
 *************************************************************/

_Bool hash_table_put(HashTable *table, const char *key)
{
    if (table->size == table->capacity)
    {
        // If the hash table is full, return 0
        return 0;
    }
    else
    {
        // Get the hash code for the key
        unsigned int hash = hash_string(key) % table->capacity;
        // Get the entry at the hash code index
        HashTableEntry *entry = &(table->entries[hash]);
        // Look for a free entry in the hash table
        while (entry != NULL)
        {
            if (entry->key != NULL && strcmp(entry->key, key) == 0)
            {
                // If the entry is found, return 1
                return 1;
            }
            else if (entry->next == NULL)
            {
                // If the entry is not found, create a new entry and return 1
                entry->next = malloc(sizeof(HashTableEntry));
                entry = entry->next;
                entry->key = strdup(key);
                entry->value = NULL;
                entry->next = NULL;
                table->size++;
                return 1;
            }
            else
            {
                // Otherwise, move on to the next entry
                entry = entry->next;
            }
        }
    }
    // If the hash table is full, return 0
    return 0;
}

/**************************************************************
 * @function hash_table_contains                              *
 * @description Checks if a hash table contains a key.        *
 *                                                            *
 * @param table Pointer to the hash table.                    *
 * @param key The key to be checked.                          *
 * @output 1 if the hash table contains the key, 0 otherwise. *
 **************************************************************/

// Returns 1 if the given key is in the hash table, 0 otherwise.
_Bool hash_table_contains(const HashTable *table, const char *key)
{
    // Check if the table or key is NULL
    if (table == NULL || key == NULL)
    {
        return 0;
    }

    // Calculate the hash value of the key
    unsigned int hash = hash_string(key) % table->capacity;

    // Get the entry at the calculated hash value
    HashTableEntry *entry = &(table->entries[hash]);

    // Loop through the entries
    while (entry != NULL)
    {
        // Check if the key is in the entry
        if (entry->key != NULL && strcmp(entry->key, key) == 0)
        {
            return 1;
        }

        // Move to the next entry
        entry = entry->next;
    }

    // If we got here, then the key is not in the table
    return 0;
}

/*********************************************************
 * @function hash_string                                 *
 * @description Hashes a string using the djb2 algorithm.*
 * @param str The string to be hashed.                   *
 * @output The hash value of the string.                 *
 *********************************************************/
static unsigned int hash_string(const char *str)
{
    // Initialize hash to 5381
    unsigned int hash = 5381;
    int c;
    // Loop through each character in the string
    while ((c = *str++))
    {
        // Multiply the hash by 33 and add the character
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}