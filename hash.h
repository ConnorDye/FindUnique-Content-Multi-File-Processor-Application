#ifndef HASHH
#define HASH
#define TABLE_SIZE 100000
/*DEFINITION FOR AN ENTRY IN OUR HASH TABLE */
typedef struct hash_entry{
    char* word;
    int count; /*count of words */
    int searched;
    struct hash_entry *next; /*in case of collision, we use chaining */
}hash_entry;

/*extern int totalUniqWords;*/

hash_entry *createItem(char *word);
hash_entry *lookup(char *s, hash_entry *hashtable[TABLE_SIZE]);
void addItem(char *word, hash_entry *hashtable[TABLE_SIZE],int*totalUniqWords);
unsigned hash(const char *word);

#endif
