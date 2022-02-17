biblio : main.o adherent.o global.o
	gcc main.o adherent.o global.o -o biblio -lmysqlclient
	rm *.o 

adherent.o : source/adherent.c
	gcc -c source/adherent.c -o adherent.o

global.o : source/global.c
	gcc -c source/global.c -o global.o

main.o : main.c
	gcc -c main.c -o main.o
