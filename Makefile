biblio : global.o adherent.o book.o main.o
	gcc main.o adherent.o global.o book.o -o biblio -lmysqlclient
	rm *.o 


global.o : source/global.c
	gcc -c source/global.c -o global.o

adherent.o : source/adherent.c
	gcc -c source/adherent.c -o adherent.o
	
book.o : source/book.c
	gcc -c source/book.c -o book.o

main.o : main.c
	gcc -c main.c -o main.o