#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef DEBUG
char *readlongword(FILE *);

int main(int argc, char* argv[]) {
	char* word = NULL;
	FILE *fp = stdin;

	if(!fp){
		fprintf(stderr, "ERROR: could not open file:\n");
		return EXIT_FAILURE;
	}

	
	
	while(!feof(fp)){
		word = readlongword(fp);
		if(word != NULL)
			printf("%s\n", word);
	}

	
	
	return 0;
}
#endif


char *readlongword(FILE *fp){
	int SIZE = 20; /*allocate 20 char array */
	int ch, i =0;
	char* word = calloc(SIZE, sizeof(char));
	if(!word){
		perror("NO MEMORY TO ALLOCATE/n");
		exit(EXIT_FAILURE);
	}
	
/*	while(!(isalpha(*fp)))
		fp++; */
	
	while((ch=getc(fp)) != EOF && (!isdigit(ch)) && 
                        (isalpha(ch))){
                   /*ch != '\n' && ch != '\r' && ch != ' '){*/
		if(i == SIZE - 1){
			SIZE += 20;
			word = realloc(word, SIZE * sizeof(char));
			if(!word){
				perror("NO MEMORY TO ALLOCATE/n");
				exit(EXIT_FAILURE);
			}
		}		
		word[i++] = tolower(ch);
	}
	word[i] = '\0';

	/*if(!(isalpha(word[0]))){
		free(word);
		return NULL;
	}*/
    
    if(ch == EOF || i == 0 || !(isalpha(word[0]))){
        free(word);
        return NULL;
    }
	return word;

}
