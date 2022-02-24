#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mysql/mysql.h>
#include "./headers/global.h"

int main(int argc, int *argv[]){
    
    initializeConnexion();
 
    if(mysql_real_connect(connexion, "localhost", "legerant", "LenerfdelaGuerre2", "biblio", 0, NULL, 0)){ // Connexion au serveur

        mysql_query(connexion,"CREATE TABLE IF NOT EXISTS adherents(number integer auto_increment primary key, name varchar(30) NOT NULL, lname varchar(50) NOT NULL, address varchar(50) NOT NULL, birthdate date NOT NULL, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP) ;");

        mysql_query(connexion,"create table IF NOT EXISTS authors (number integer auto_increment primary key, name varchar(30) NOT NULL, lname varchar(50) NOT NULL, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);"  ) ;

        mysql_query(connexion,"create table IF NOT EXISTS books(number integer auto_increment primary key, title varchar(50) NOT NULL, keywords varchar(100), released_date date not null, author_number integer not null, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, foreign key fk_authors_books (author_number) REFERENCES authors(number) MATCH FULL ON DELETE set null ON UPDATE set null );");    

        mysql_query(connexion,"create table IF NOT EXISTS borrowings(id integer primary key auto_increment, adherent_number integer not null, book_number integer not null, out_date date not null, return_date date not null, effective_return_date date null, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, foreign key fk_authors_borrowings (adherent_number) REFERENCES adherents(number) MATCH FULL ON DELETE set null ON UPDATE set null , foreign key fk_books_borrowings (book_number) REFERENCES books(number) MATCH FULL ON DELETE set null ON UPDATE set null );");    
        
        // mysql_query(connexion, "insert into authors(name, lname) values('Ange', 'Diéké')") ;
        // mysql_query(connexion, "insert into authors(name, lname) values('Roye', 'Traoré')") ;
    }else{ 
        puts("\t\t!!! Echec lors de la connexion à la base de données. !!! \n");
        exit(0);
    }

    showMainMenu();
        
    return 0;
}
