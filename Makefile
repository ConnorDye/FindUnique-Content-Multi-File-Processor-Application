uniq: uniq.o readOneWord.o hash.o
	gcc -o uniq -Wall -g fw.o readOneWord.o hash.o
uniq.o: uniq.c
	gcc -ansi -Wall -pedantic -g -c uniq.c

readOneWord.o: readOneWord.c
	gcc -ansi -Wall -pedantic -g -c readOneWord.c

hash.o: hash.c
	gcc -ansi -Wall -pedantic -g -c hash.c

clean:
	rm *.o uniq

git:
	git add uniq.c hash.c readOneWord.c hash.h readOneWord.h Makefile README
	git commit -m "$m"
	git push -u origin main
    
handin:
	scp uniq.c hash.c readOneWord.c hash.h readOneWord.h Makefile README chdye@unix1.csc.calpoly.edu:./asgn2

test:
	./uniq -n 10 INPUT2

valgrind:
	valgrind --leak-check=yes ./uniq -n 10 INPUT2

