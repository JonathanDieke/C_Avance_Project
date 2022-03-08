#include <stdio.h>
#include <string.h>
#include <time.h>
#include <R.h> 
#include <Rinternals.h>
#include <Rembedded.h>
#include <mysql/mysql.h>
#include "./headers/global.h"


int main(int argc, int *argv[]){

    int r_argc = 2;
    char *r_argv[] = { "R", "--silent" };
    Rf_initEmbeddedR(r_argc, r_argv);
            
    
    char 
        host[15] = "localhost", 
        user[15] = "legerant", 
        password [15]= "Tarzan225", 
        database_name[15] = "biblio";
    
    initializeConnexion();
  
    if(mysql_real_connect(connexion, host, user, password, database_name, 0, NULL, 0)){ // Connexion au serveur

        mysql_query(connexion,"CREATE TABLE IF NOT EXISTS adherents(number integer auto_increment primary key, name varchar(30) NOT NULL, lname varchar(50) NOT NULL, address varchar(50) NOT NULL, birthdate date NOT NULL, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP) ;");

        mysql_query(connexion,"create table IF NOT EXISTS authors (number integer auto_increment primary key, name varchar(30) NOT NULL, lname varchar(50) NOT NULL, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);"  ) ;

        mysql_query(connexion,"create table IF NOT EXISTS books(number integer auto_increment primary key, title varchar(50) NOT NULL, keywords varchar(100), released_date date not null, author_number integer not null, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, foreign key fk_authors_books (author_number) REFERENCES authors(number) MATCH FULL ON DELETE cascade ON UPDATE cascade );");    

        mysql_query(connexion,"create table IF NOT EXISTS borrowings(id integer primary key auto_increment, adherent_number integer not null, book_number integer not null, out_date date not null, return_date date not null, effective_return_date date null, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, foreign key fk_authors_borrowings (adherent_number) REFERENCES adherents(number) MATCH FULL ON DELETE cascade ON UPDATE cascade , foreign key fk_books_borrowings (book_number) REFERENCES books(number) MATCH FULL ON DELETE cascade ON UPDATE cascade );");    
        
        MYSQL_RES *results ;

        char query[512];

        // authors fictifs
        sprintf(query, "select * from authors");
        if(mysql_query(connexion, query) == 0){
            results = mysql_store_result(connexion);
            if(results != NULL && mysql_num_rows(results) == 0){
                mysql_query(connexion, "insert into authors(name, lname) values('Ange', 'Diéké')") ;
                mysql_query(connexion, "insert into authors(name, lname) values('Roye', 'Traoré')") ;
                mysql_query(connexion, "insert into authors(name, lname) values('William', 'Kalumbi')") ;
                mysql_query(connexion, "insert into authors(name, lname) values('Albert', 'Camus')") ;
                mysql_query(connexion, "insert into authors(name, lname) values('Camara', 'Laye')") ;
                mysql_query(connexion, "insert into authors(name, lname) values('Robert', 'Kiyozaki')") ;
                mysql_query(connexion, "insert into authors(name, lname) values('Napoléon', 'Hill')") ;
                mysql_query(connexion, "insert into authors(name, lname) values('Laurent', 'Gounelle')") ;
                mysql_query(connexion, "insert into authors(name, lname) values('Cheick', 'Diop')") ;
            }
            // else{
            //     printf("\n erreur insertion authors \n");
            // }
        }

        //adherents fictifs
        sprintf(query, "select * from adherents");
        if(mysql_query(connexion, query) == 0){
            results = mysql_store_result(connexion);
            if(results != NULL && mysql_num_rows(results) == 0){
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Kounapetri', 'Ouattara', 'treichville', '2000-07-05')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Madeleine', 'Ouattara', 'treichville', '1998-06-02')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Jacques', 'Fodio', 'Sideci', '2000-10-3')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('David', 'Leroi', 'Silicon', '1995-07-13')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Carole', 'Yapi', 'Bouaflé', '2000-07-13')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Béranice', 'Déapo', 'Abidjan', '1995-07-13')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Priscille', 'Kadjomou', 'Agboville', '2001-11-1')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Esther', 'Bandama', 'Akoupé', 2000-07-13')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Hamilton', 'Lewiss', 'Silicon', '1995-05-17')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Mohamed', 'Diomandé', 'Korhogo', '2001-07-13')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Zidane', 'Mohamed', 'Abidjan', '2000-01-03')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Pyth', 'Pythus', 'AIESEC', '2001-02-03')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Elvira', 'Kocora', 'Bassam', '2002-07-14')") ;
                mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('Karamoko', 'Koné', 'Soubré', '1995-07-13')") ;
                // mysql_query(connexion, "insert into adherents(name, lname, address, birthdate) values('David', 'Leroi', 'Silicon', '1995-07-13')") ;
            }
            // else{
            //     printf("\n erreur insertion adherents \n");
            // }
        }

        // books fictifs
        sprintf(query, "select * from books");
        if(mysql_query(connexion, query) == 0){
            results = mysql_store_result(connexion);
            if(results != NULL && mysql_num_rows(results) == 0){
                mysql_query(connexion, "insert into books(title, keywords, released_date, author_number) values('L antidote', 'vie, mort, argent, gloire', '2019-02-12', 3)") ;
                mysql_query(connexion, "insert into books(title, keywords, released_date, author_number) values('Coloré', 'loyauté, courage', '2020-04-05', 4)") ;
                mysql_query(connexion, "insert into books(title, keywords, released_date, author_number) values('test', 'test', '2022-02-24', 1)") ;
                mysql_query(connexion, "insert into books(title, keywords, released_date, author_number) values('Amazing grace', 'christ, glorious, pray', '2019-03-03', 2)") ;
                mysql_query(connexion, "insert into books(title, released_date, author_number) values('L étranger', '2010-06-03', 4)") ;
                mysql_query(connexion, "insert into books(title, keywords, released_date, author_number) values('L enfant noir', 'souffrance, compassion', '2008-09-23', 5)") ;
                mysql_query(connexion, "insert into books(title, keywords, released_date, author_number) values('Rich dad, poor dad', 'réussite, dev personnel, entrepreneuriat', '2003-07-17', 6)") ;
                mysql_query(connexion, "insert into books(title, keywords, released_date, author_number) values('Réfléchissez et devenez riche', 'dev personnel, réussite, argent', '2001-03-03', 7)") ;
                mysql_query(connexion, "insert into books(title, keywords, released_date, author_number) values('Afrique : berceau', 'nègritude, racisme', '1989-1-11', 8)") ;
            }
            // else{
            //     printf("\n erreur insertion books \n");
            // }
        }

        //borrowings fictifs
        sprintf(query, "select * from borrowings");
        if(mysql_query(connexion, query) == 0){
            results = mysql_store_result(connexion);
            if(results != NULL && mysql_num_rows(results) == 0){
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date, effective_return_date) values(1,  1, '2019-02-12', '2019-02-25', '2019-02-28')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date, effective_return_date) values(1, 2, '2020-04-05', '2020-04-12', '2020-04-11')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date, effective_return_date) values(3, 4, '2022-01-02', '2022-01-17', '2022-01-25')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date) values(4, 3, '2022-03-01', '2022-03-15')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date, effective_return_date) values(1, 2, '2018-10-01', '2018-10-15', '2018-11-03')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date, effective_return_date) values(2, 3, '2018-03-11', '2018-03-25', '2018-03-24')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date) values(3, 4, '2019-02-17', '2019-02-28')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date, effective_return_date) values(4, 5, '2020-06-27', '2020-07-10', '2020-07-03')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date) values(5, 1, '2020-09-09', '2020-09-29')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date, effective_return_date) values(6, 2, '2021-12-23', '2023-01-03', '2023-01-01')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date, effective_return_date) values(4, 3, '2022-03-01', '2022-03-15', '2022-03-15)") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date) values(4, 3, '2022-02-01', '2022-02-15')") ;
            }
            // else{
            //     printf("\n erreur insertion borrowings \n");
            // }
        }


    }else{ 
        puts("\t\t!!! Echec lors de la connexion à la base de données. !!! \n");
        exit(0);
    }

    showMainMenu();
        
    return 0;
}
