biblio : global.o adherent.o book.o borrowing.o stats.o main.o
	gcc main.o adherent.o global.o book.o borrowing.o stats.o -o biblio -lmysqlclient -I/usr/share/R/include -L/usr/share/R/include -L/usr/lib/R/lib -lR 
#	-I/usr/share/R/include -L/usr/share/R/include -L/usr/lib/R/lib -lm -lRmath
#	-I/usr/share/R/include -L/usr/share/R/include -L/usr/lib/R/lib -lR -lm -lRmath
	rm *.o 
	./biblio

global.o : source/global.c
	gcc -c source/global.c -o global.o

adherent.o : source/adherent.c
	gcc -c source/adherent.c -o adherent.o
	
book.o : source/book.c
	gcc -c source/book.c -o book.o

borrowing.o : source/borrowing.c
	gcc -c source/borrowing.c -o borrowing.o

stats.o : source/stats.c
	gcc -c source/stats.c -o stats.o -I/usr/share/R/include -lR
#	-I/usr/share/R/include -L/usr/lib/R/lib -lm -lR -lm -lRmath

main.o : main.c
	gcc -c main.c -o main.o 
#	-I/usr/share/R/include -L/usr/share/R/include -L/usr/lib/R/lib -lR -lm -lRmath