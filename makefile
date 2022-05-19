pendu.exe: pendu.o
	gcc pendu.o -o pendu.exe

pendu.o: pendu.c
	gcc -c pendu.c