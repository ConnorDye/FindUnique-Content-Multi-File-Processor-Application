#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
/*#define DEBUGH*/


/*#define TABLE_SIZE 100000*/

unsigned hash(const char *);

/*DEFINITION FOR AN ENTRY IN OUR HASH TABLE */
/*
typedef struct hash_entry{
    char* word; 
    int count; 
    int searched; 
    struct hash_entry *next; 
}hash_entry; */


/*DEFININITON TO CREATE AN ITEM IN HASH TABLE)*/
hash_entry *createItem(char *word){
    hash_entry* item = (hash_entry*)malloc(sizeof(hash_entry));
    if(!item){
        perror("No memory to allocate hash item.\n");
        exit(EXIT_FAILURE);
    }
    item->word = word;
    item->count = 1;
    item->next = NULL;
    item->searched = 0;

    return item;
}

/*DEFINITION TO ADD AN ITEM TO HASH TABLE*/



/*HELPER FUNCTION TO ADD ITEM 
    /RETURNS ITEM IF FOUND
    /RETURNS NULL IF NOT FOUND
*/
hash_entry *lookup(char *s, hash_entry *hashtable[TABLE_SIZE]){
    hash_entry *item;

    for(item = hashtable[hash(s)]; item != NULL; item = item->next){
        if(strcmp(s, item->word) == 0)
            return item;
    }

    return NULL;

}

/*ADDITEM DECLARATION 
    /FOR THIS TO WORK HASHTABLE MUST BE INITIALIZED TO NULL */

/*FUNCTIONS AS FOLLOWS
    /If lookup finds word, simply increment count
    /If word is not in table and index is empty, add word at index
    /else handle the collision case
*/
void addItem(char *word, hash_entry *hashtable[TABLE_SIZE],
                                                       int *totalUniqWords){
    hash_entry *item;
    
    if((item =lookup(word, hashtable)) != NULL){
        item->count++; /*if the word is in the table already increment count */
    }
    else if((item =lookup(word, hashtable)) == NULL 
                                    && hashtable[hash(word)] == NULL){
        hashtable[hash(word)] = createItem(word);
        (*totalUniqWords)++;   
    }
    else{ /*collision case*/
        hash_entry *temp = hashtable[hash(word)];
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = createItem(word);
        (*totalUniqWords)++;
    }
}




/*creates hash value from word */
unsigned hash(const char *word){
    unsigned hashVal;

    for(hashVal = 0; *word != '\0'; word++){
        hashVal = *word + 31 * hashVal;
    }

    return hashVal % TABLE_SIZE;

}

#ifdef DEBUGH
int main(void){
    /*TEST CREATE ITEM */
    int *totalUniqWords = (int *)malloc(sizeof(int));
    *totalUniqWords = 0;
    hash_entry* hashTable[TABLE_SIZE] = {NULL};
    char* word = "hello";
    char* word2 = "n1";
    char* word3 = "m2";
    /*hashTable[hash(word)] = createItem(word);
    printf("%d", hash(word));
    printf("%s", hashTable[hash(word)]->word); 
    printf("%d", hashTable[hash(word)]->count);

    if(lookup(word, hashTable))
        printf("true\n");
    if(!lookup(word2, hashTable))
        printf("Look up passed!\n");    */


    /*TEST ADDITEM */
    addItem(word2, hashTable,totalUniqWords);
    addItem(word2, hashTable, totalUniqWords);
    addItem(word2, hashTable, totalUniqWords);
    addItem(word3, hashTable, totalUniqWords);
    addItem("Hello", hashTable, totalUniqWords);
    addItem("GET", hashTable, totalUniqWords);
    hash_entry *temp = hashTable[hash(word2)];                              
    while(temp->next != NULL){                                              
         printf("WORD %s at HASH %d\n", temp->word, hash(temp->word));
         temp = temp->next;                                                  
    }      



    printf("Total Unique words is %d\n", *totalUniqWords);
   /* printf("hash for word 2 is: %d && has for word 3 is: 
                    %d\n", hash(word2), hash(word3));
    printf("%s count is %d\n", hashTable[hash(word2)]->word,
                             hashTable[hash(word2)]->count);
    printf("%s count is %d\n",hashTable[hash(word2)]->next->next->word,
                             hashTable[hash(word2)]->count);*/
    return 0;
}
#endif

