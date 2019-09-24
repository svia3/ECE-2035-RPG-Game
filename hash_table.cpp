/*
 Student Name: Stephen Via
 Date: 11/9/2018

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;
  /** The hash function pointer */
  HashFunction hash;
  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;
  /** The value associated with this hash table entry */
  void* value;
  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
    // Allocate memory for the new hashTableEntry.
    HashTableEntry* newEntry = (HashTableEntry*)malloc(sizeof(HashTableEntry));
    //Initialize the components of the new hashTableEntry.
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = NULL;
    //Return pointer to newEntry in memory.
    return newEntry;
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
        // Hash the key into a index in the hash table.
        unsigned int myHash = hashTable->hash(key);
        HashTableEntry* currEntry = hashTable->buckets[myHash]; // pointer to first node in list.
        // Loop through external chain at a specific bucket index.
        while (currEntry) {
            if (currEntry->key == key) {
                return currEntry;
            }
            // Continue to the next node in the list.
            currEntry = currEntry->next;
        }
        return NULL; // Not in the list.
}

//static void printTable(HashTable* hashTable) {
//     unsigned int num = hashTable -> num_buckets;
//     printf("%d\n\n", num);
//     for (int i = 0; i < num; i++) {
//         HashTableEntry* elem = hashTable -> buckets[i];
//         while (elem != NULL) {
//             printf("%d ", elem -> key);
//             elem = elem -> next;
//         }
//         printf("\n");
//     }
//     printf("*******\n");
// }
/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets contain indeterminant values, init each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct.
  return newTable;
}

/**
* destroyHashTable
*
* Helper function deallocates all of the memory blocks that are stored
* for the hash table and successive nodes in memory.
*
* @param hashTable The pointer to the hash table.
*/
void destroyHashTable(HashTable* hashTable) {
    // Avoid NULL arguments.
    if (hashTable) {
        // Iterate over num_buckets size.
        unsigned int i;
        for (i = 0; i < hashTable->num_buckets; i++) {
            // Save current head of the externally chained list.
            HashTableEntry* myEntry = hashTable->buckets[i];
            while (myEntry) {
                // Save the pointer to next node in memory.
                HashTableEntry* temp = myEntry->next;
                // Free the entry and its allocated value.
                free(myEntry->value);
                free(myEntry);
                myEntry = temp;
            }
        }
        // free the buckets and the hashTable
        free(hashTable->buckets);
        free(hashTable);
    }
}

/**
 * insertItem
 *
 * Insert the value into the hash table based on the key.
 * In other words, create a new hash table entry and add it to a specific bucket.
 *
 * @param myHashTable The pointer to the hash table.
 * @param key The key that corresponds to the value.
 * @param value The value to be stored in the hash table.
 * @return old value if it is overwritten, or NULL if not replaced
 */
void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
      // Temporary pointer to old or new return value;
      void* temp;
      unsigned int myHash = hashTable->hash(key);
      HashTableEntry* curr = hashTable->buckets[myHash];
      // Check edge case if head key is equal to insert key.
      //printTable(hashTable);
      if (!curr) { // Is there a head?
            HashTableEntry* newEntry = createHashTableEntry(key, value);
            hashTable->buckets[myHash] = newEntry; // for some reason this cannot be curr.
            return NULL;
      }
      // Loop with a pointer to curr next for a NULL checker.
      while (curr->next) {
      // Replace if you find duplicate key.
         if (curr->key == key) {
            temp = curr->value;
            curr->value = value;
            //printTable(hashTable);
            return temp;
         }
         if (curr->next) { // Not null.
            curr = curr->next; // Cannot have a null pointer
         }
      }
      // Does the head key match? -> there is only one item in the list.
      // Head == Tail => default the while loop.
      if (curr->key == key) { // Does the head have a matching key?
           temp = curr->value;
           curr->value = value; // Replace the value.
           return temp;
      }
      // Add if no key is found.
      HashTableEntry* newEntry = createHashTableEntry(key, value);
      curr->next = newEntry;
      return NULL;
}

/**
 * getItem
 *
 * Get the value that corresponds to the key in the hash table.
 *
 * @param myHashTable The pointer to the hash table.
 * @param key The key that corresponds to the item.
 * @return the value corresponding to the key, or NULL if the key is not present
 */
void* getItem(HashTable* hashTable, unsigned int key) {
    // Hash current key into buckets.
    unsigned int myHash = hashTable->hash(key);
    HashTableEntry* curr = hashTable->buckets[myHash];
    // Iterate over list.
    while (curr) {
        // Does the key match?
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next; // Continue to next node.
    }
    return NULL; // Default.
}

/**
 * removeItem
 *
 * Remove the item in hash table based on the key and return the value stored in it.
 * In other words, return the value and free the hash table entry from heap.
 *
 * @param myHashTable The pointer to the hash table.
 * @param key The key that corresponds to the item.
 * @return the pointer of the value corresponding to the key, or NULL if the key is not present
 */
void* removeItem(HashTable* hashTable, unsigned int key) {
    HashTableEntry* curr; // Current node pointer.
    curr = findItem(hashTable, key); // Is it in the list?
    HashTableEntry* prev = NULL; // Previous node pointer.
    if (!curr) {
        return NULL; // If not, edge case, return NULL.
    }
    // Hash current node pointer.
    unsigned int myHash = hashTable->hash(key);
    curr = hashTable->buckets[myHash];
    // Keep track of a current temp pointer for data acquisition.
    void* temp;
    // Iterate over list.
    while (curr) {
        // Is the key found?
        if (curr->key == key) {
            temp = curr->value;
            if (prev) { // Does it have a previous pointer from previous iteration?
                prev->next = curr->next; // Remove from the list, NOT memory.
            } else {
                hashTable->buckets[myHash] = curr->next; // You are at the head. -> Edge case.
            }
            free(curr); // Free the entry.
            return temp;
        }
        prev = curr; // Store current node in previous to skip during a removal.
        curr = curr->next; // Next node in list.
    }
    return NULL;
}

/**
 * deleteItem
 *
 * Delete the item in the hash table based on the key. In other words, free the
 * value stored in the hash table entry and the hash table entry itself from
 * the heap.
 *
 * @param myHashTable The pointer to the hash table.
 * @param key The key that corresponds to the item.
 *
 */
void deleteItem(HashTable* hashTable, unsigned int key) {
    HashTableEntry* curr; // Current node pointer.
    HashTableEntry* prev = NULL; // Previous node pointer.
    curr = findItem(hashTable, key); // Is it in the list?
    if (!curr) {
        return; // If not, edge case, return NULL.
    }
    // Hash current node pointer.
    unsigned int myHash = hashTable->hash(key);
    curr = hashTable->buckets[myHash];
    // Keep track of a current temp pointer for data acquisition.
    void* temp;
    // Iterate over list.
    while (curr) {
        // Is the key found?
        if (curr->key == key) {
            temp = curr->value;
            if (prev) { // Does it have a previous pointer from previous iteration?
                prev->next = curr->next; // Remove from the list, NOT memory.
            } else {
                hashTable->buckets[myHash] = curr->next; // You are at the head. -> Edge case.
            }
            free(curr); // Free the entry.
            free(curr->value); // Free the value as well.
            return;
        }
        prev = curr; // Store current node in previous to skip during a removal.
        curr = curr->next; // Next node in list.
    }
    return;
}
