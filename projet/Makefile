#première cible : sera executée en premier

all: exec clean

main2.o : main2.c *.h
	gcc -c main2.c -o main2.o

fonctions2.o : fonctions2.c *.h
	gcc -c fonctions2.c -o fonctions2.o

exec : main2.o fonctions2.o
	gcc *.o -o exec

clean :
	rm -f *.o
