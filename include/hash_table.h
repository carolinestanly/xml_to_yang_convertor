#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// Hash table entry structure
typedef struct HashTableEntry
{
    char *key;
    void *value;
    struct HashTableEntry *next;
} HashTableEntry;

// Hash table structure
typedef struct
{
    HashTableEntry *entries;
    unsigned int capacity;
    unsigned int size;
} HashTable;

// Create a new hash table with the given capacity
HashTable *create_hash_table(unsigned int capacity);

// Free the memory allocated for the hash table
void destroy_hash_table(HashTable *table);

// Add a new key-value pair to the hash table
_Bool hash_table_put(HashTable *table, const char *key);

// Check if the hash table contains the given key
_Bool hash_table_contains(const HashTable *table, const char *key);



#endif // HASH_TABLE_H
