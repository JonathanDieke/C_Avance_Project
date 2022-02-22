#include <mysql/mysql.h>
#include <stdio.h>
#include "../headers/adherent.h"
#include "../headers/book.h"
#include "../headers/global.h"  

MYSQL *connexion = NULL; 

char* BOOK_TABLE_NAME = "books" ;
char* ADHERENT_TABLE_NAME = "adherents";
char* AUTHOR_TABLE_NAME = "authors";

void initializeConnexion(){
    connexion = mysql_init(0);
}

char *lire(int size){
    int i = 0;

    char* text = (char*) malloc(sizeof(char)*size);

    while(i<size){
        scanf("%c", &text[i]);
        if(text[i] == '\n') break ;
        else i++ ;
    }
    text[i] = '\0';
    return text ;
}

void showMainMenu(){

    int choice = 0 ; 

    do{
        puts("\t\t BIENVENUE !!! ");  
        puts("MENU PRINCIPAL"); 
        puts("1- ADHERENTS ");
        puts("2- LIVRES "); 
        puts("3- EMPRUNTS ");
        puts("4- Quitter ");

        printf("CHOISIR UNE OPTION : "); 
        scanf("%d", &choice);

        switch (choice){
            case 1:
                system("clear");
                showMenuAdherent();
                break;
            case 2:
                system("clear");
                showMenuBook();
                break;
            case 3:
                // inserer le module 
                break;
            case 4:
                system("clear");
                puts("Bye ! ");
                exit(0);
                break;            
            default:
                system("clear");
                puts("Veuillez faire un choix entre 1 ET 3\n");
                break;
        }
    } while (choice < 1 || choice > 4);
    
}