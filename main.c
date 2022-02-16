#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "./headers/adherent.h"


int main(int argc, int *argv[]){
 

    MYSQL *connexion  ;
    connexion = mysql_init(0);

    //Tentative de création de la BD
    char* query = "CREATE DATABASE IF NOT EXISTS biblio";
    // stringstream ss ;


    if(mysql_real_connect(connexion, "localhost", "legerant", "LenerfdelaGuerre2", "biblio", 0, NULL, 0)){ // Connexion au serveur

        int queryState = mysql_query(connexion, "CREATE DATABASE IF NOT EXISTS biblio");

        mysql_query(connexion,"CREATE TABLE IF NOT EXISTS adherents(number integer auto_increment primary key, name varchar(30) NOT NULL, lname varchar(50) NOT NULL, address varchar(50) NOT NULL, birthdate date NOT NULL, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP) ;");
        
        mysql_query(connexion,"create table IF NOT EXISTS authors (number integer auto_increment primary key, name varchar(30) NOT NULL, lname varchar(50) NOT NULL, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);");    

        mysql_query(connexion,"create table IF NOT EXISTS books(number integer auto_increment primary key, title varchar(50) NOT NULL, keyword varchar(100), released_date date, author_number integer not null, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, foreign key fk_authors_books (author_number) REFERENCES authors(number) MATCH FULL ON DELETE NO ACTION ON UPDATE NO ACTION );");    

        mysql_query(connexion,"create table IF NOT EXISTS borrowings(id integer primary key auto_increment, adherent_number integer not null, book_number integer not null, out_date date not null, return_date date not null, effective_return_date date null, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, foreign key fk_authors_borrowings (adherent_number) REFERENCES adherents(number) MATCH FULL ON DELETE NO ACTION ON UPDATE NO ACTION , foreign key fk_books_borrowings (book_number) REFERENCES books(number) MATCH FULL ON DELETE NO ACTION ON UPDATE NO ACTION );");    

    }else{ 
        printf("\n\t\t!!! Echec lors de la connexion au serveur !!! \n");
    }

        printf("\n\t\t BIENVENUE !!! \n");  
        printf("\nCHOISIR UNE OPTION \n"); 
        printf("\n1- ADHERENTS \n");
        printf("\n2- LIVRES \n");
        printf("\n3- EMPRUNTS \n");

        int choice = 0 ; 
        scanf("%d", &choice);

        switch (choice){
    
            case 1:
                system("clear");
                showOwnerMenuAdherent();
                break;
            case 2:
                // inserer le module 
                break;
            case 3:
                // inserer le module 
                break;
            
            default:
                printf("ENTRER UN ENTIER COMPRIS ENTRE 1 ET 3");
                break;
        }
        

    return 0;
}
