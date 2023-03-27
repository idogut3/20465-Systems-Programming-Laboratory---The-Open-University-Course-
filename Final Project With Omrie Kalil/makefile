run: project.o macro.o first_run.o first_run2.o second_run.o mioun.o
	gcc -ansi -Wall -pedantic project.o macro.o first_run.o first_run2.o second_run.o mioun.o -o run
project.o: project.c
	gcc -c -ansi -Wall -pedantic project.c -o project.o
macro.o: macro.c
	gcc -c -ansi -Wall -pedantic macro.c -o macro.o
first_run.o: first_run.c
	gcc -c -ansi -Wall -pedantic first_run.c -o first_run.o
first_run2.o: first_run2.c
	gcc -c -ansi -Wall -pedantic first_run2.c -o first_run2.o
second_run.o: second_run.c
	gcc -c -ansi -Wall -pedantic second_run.c -o second_run.o
mioun.o: mioun.c
	gcc -c -ansi -Wall -pedantic mioun.c -o mioun.o

