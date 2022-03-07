#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mysql/mysql.h>
#include "./headers/global.h"


int main(int argc, int *argv[]){

    double res[10];
    res[0] = 10;
    res[1] = 14;                
    // ma_norm(10, res);
    // printf("\n ceil : %d \n", ceilling(2.4));
    
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
                mysql_query(connexion, "insert into authors(name, lname) values('Laouni', 'Mouhid')") ;
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
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date) values(3, 4, '2022-01-02', '2022-01-17')") ;
                mysql_query(connexion, "insert into borrowings(adherent_number, book_number, out_date, return_date) values(4, 3, '2022-03-01', '2022-03-15')") ;
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
