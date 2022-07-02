#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include "readOneWord.h"
#include "hash.h"

/*THIS PROGRAM TAKES AN UNKNOWN NUMBER OF WORDS AS STDIN OR AS FILES AND
DISPLAYS THE MOST COMMON WORDS BY FREQUENCY, AND IF THERE'S A FREQUENCY TIE
THEN BY REVERSE ALPHABETICAL ORDER. USING THE -n ARGUMENT WHEN YOU RUN IT
WILL ALLOW THE USER TO CHOOSE HOW MANY WORDS TO PRINT */


/*FUNCTION PROTOTYPES*/
void printResult(hash_entry* arrToPrint[],int wordsToPrint,
                                                int totalUniqWords);
void createArrToPrint(hash_entry* arrToPrint[], int wordsToPrint,
 hash_entry* hashTable[TABLE_SIZE]); /*SIZE = wordsToPrint in main */

hash_entry* findMax(hash_entry* hashTable[TABLE_SIZE]);
void UNITTEST(hash_entry* hashTable[TABLE_SIZE]);

int main(int argc, char *argv[]){
    int option; /*getOpt function */
    int wordsToPrint = 10; /*size of array to print */
    char* word = NULL;
    char* fileName = NULL;
    FILE *fp = stdin;
    /*int *totalUniqWords = (int *)malloc(sizeof(int));*/
    int totalUniqWords = 0;
    /*int *totalUniqRef = &totalUniqWords; */
    hash_entry* hashTable[TABLE_SIZE] = {NULL};
    /*Allocate array to print of size 10, and reallocate if needed*/
    hash_entry **arrToPrint = calloc(wordsToPrint,sizeof(hash_entry*)); 
    if(!arrToPrint){
                perror("NO MEMORY TO ALLOCATE/n");
                exit(EXIT_FAILURE);
        }
    /*totalUniqWords = 0; */

    while((option = getopt(argc, argv, "n:")) != -1){ /*n is followed by colon 
                                                   so it has associated value*/
         int i;
         switch(option){
            case 'n': /* [executable name] -n digt */
                for(i = 0; i < strlen(optarg); i++){
                    if(!isdigit(optarg[i])){ 
                        /*quit if -n argument isn't int) */
                        fprintf(stderr, "USAGE: [-n #words as digit] " 
                                                               "fileNames\n"); 
                        exit(EXIT_FAILURE);
                    }
                }
                
                if(optarg != NULL){
                    wordsToPrint = atoi(optarg);
                    arrToPrint = realloc(arrToPrint, 
                                            sizeof(hash_entry*)*wordsToPrint);
                    if(!arrToPrint){
                                    perror("NO MEMORY TO ALLOCATE\n");
                                    exit(EXIT_FAILURE);
                    }

                }
                break;
            default:
                fprintf(stderr, "Usage: %s [-n #words] fileNames\n", argv[0]);
                exit(EXIT_FAILURE);

        }

    }/*while getOpt doesn't report -1, we keep stepping through CL OPTIONS */


    /*GETOPT FUNCTION:
        1.) IF THERE ARE NO OPTION CHARACTERS, GETOPT RETURNS -1
        2.) OPTIND IS INDEX IN ARGV OF FIRST ELEMENT THAT IS NOT OPTION
    */    
    /*IF NO FILES GIVEN, PROGRAM TAKES IT'S INPUT FROM stdin; */
    if(optind < argc){

        while(optind < argc) { 
            fileName = argv[optind];
            if((fp = fopen(fileName, "r"))== NULL){ /*not working */
                perror("ISSUE WITH FILE");
                fprintf(stderr, "FILE WITH ISSUE IS: %s\n", fileName); 
            }
            else{
                /*add code to process file */
                while(!feof(fp)){
                    word = readlongword(fp);
                    if(word != NULL){
                        addItem(word, hashTable, &totalUniqWords);
                       /* printf("%s word read from file\n", word);
                        printf("%s exists as a word at hash %d\n\n",
                                 hashTable[hash(word)]->word, hash(word));*/
                    }
                }
                if(fp != NULL)
                    fclose(fp);
            }
            optind++;
            
        }
    }
    else{
       /* printf("No files given take input from stdin");*/
            while(!feof(fp)){
                    word = readlongword(fp);
                    if(word != NULL){
                       /* printf("%s word read from stdin\n", word);*/
                        addItem(word, hashTable, &totalUniqWords); /*in hash.c*/
                    }
            }

        /*take input from stdin*/
    }
    
    /*UNITTEST(hashTable);*/
    createArrToPrint(arrToPrint, wordsToPrint, hashTable);
    printResult(arrToPrint, wordsToPrint, totalUniqWords);
        
    /*printf("File name is %s and wordcount is %i\n", 
                            fileName, wordsToPrint);*/

    return 0;
}



hash_entry* findMax(hash_entry* hashTable[TABLE_SIZE]){
    int i;
    /*CREATE A NULL VALUE TO COMPARE AGAINST AS WE CANNOT USE index 0 if NULL*/
    hash_entry* maxToReturn = (hash_entry*)malloc(sizeof(hash_entry)); 
    hash_entry* max = maxToReturn;
    if(!maxToReturn){
        perror("NO MEMORY TO ALLOCATE\n");
        exit(EXIT_FAILURE);
    }
    max->word = "";
    max->count = 0;


    for(i = 0; i < TABLE_SIZE; i++){
        hash_entry* temp = hashTable[i]; /*defined in case of 
                                        chaining within hashtable*/
        
        /*if no word with hash continue to next iteration */        
        if(hashTable[i] == NULL)
            continue;
        
        
        /*if there is no chaining */
        if(hashTable[i]->count > max->count)
            max = hashTable[i];
        /*in case of frequency tie, choose word later in alphabet */
        else if(hashTable[i]->count == max->count){
            /*strcmp returns > 0 if max->word is less than str1 */  
            if(strcmp(hashTable[i]->word, max->word) > 0){
                max = hashTable[i];    
            }    
        }
        
        /*if there is chaining iterate the linked list */
        while(temp->next != NULL){
            temp = temp->next;
            if(temp->count > max->count){
                            max = temp;
            }
            else if(temp->count == max->count){
                if(strcmp(temp->word, max->word)>0)
                    max = temp;
            }    
        }
    }
    
    /*if(hashTable[hash(word)]->word == max->word && 
                            hashTable[hash(word)]->next == NULL)
        hashTable[hash(word)] = NULL;
    else if(hashTable[hash(word)]->word == max->word
                             && hashTable[hash(word)]->next != NULL)
        hashTable[hash(word)] = hashTable[hash(word)]->next;
    else{
        hash_entry* temp = hashTable[hash(word)]->next;
        hash_entry* prev = hashTable[hash(word)];
        while(temp->word != max->word){
            temp = temp->next;
            prev = prev->next;
        }
        prev = temp->next;
        temp = NULL;
    }*/
    if(max->searched) /*if max is already searched return NULL*/
        return NULL;

    maxToReturn->word = max->word; /*reallocated to hold proper count*/
    maxToReturn->count = max->count; 
    max->count = 0; /* set count to 0 so it doesn't reiterate*/
    max->searched = 1;

    return maxToReturn;

}

/*FUNCTION THAT CREATES THE ARRAY TO PRINTED FROM OUR HASH TABLE */
/*SIZE = wordsToPrint in main */
void createArrToPrint(hash_entry* arrToPrint[], int wordsToPrint, 
                      hash_entry* hashTable[TABLE_SIZE]){ 
    int i;
    for(i=0; i < wordsToPrint; i++){
            arrToPrint[i] = findMax(hashTable);
    }
}

/*FUNCTION THAT WILL PRINT OUR ARRAY */
void printResult(hash_entry* arrToPrint[],int wordsToPrint,int totalUniqWords){
    int i;
   
     
    printf("The top %d words (out of %d) are:\n",wordsToPrint, totalUniqWords);
    if(totalUniqWords == 0){
        exit(0);
    }
    
    for(i = 0; i < wordsToPrint; i++){
        if(arrToPrint[i] != NULL && arrToPrint[i] !=0){
            printf("%*d %s\n", 9, arrToPrint[i]->count, 
                    arrToPrint[i]->word);
        }
    }   
    

}

void UNITTEST(hash_entry* hashTable[TABLE_SIZE]){
    printf("UNIT TEST CALLED");
    hash_entry* max = findMax(hashTable);
    printf("Most occuring word is %s with a count of %d\n",
                                 max->word, max->count);
    max = findMax(hashTable);
    printf("Most occuring word is %s with a count of %d\n",
                                 max->word, max->count);

}

