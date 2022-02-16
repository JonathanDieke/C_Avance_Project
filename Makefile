biblio : main.o adherent.o
	gcc main.o adherent.o -o biblio -lmysqlclient
	rm *.o

adherent.o : source/adherent.c
	gcc -c source/adherent.c -o adherent.o

main.o : main.c
	gcc -c main.c -o main.o
