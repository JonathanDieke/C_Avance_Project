#include <mysql/mysql.h>
#include <stdio.h>
#include "../headers/global.h"
#include "../headers/adherent.h"

MYSQL *connexion = NULL; 

void initializeConnexion(){
    connexion = mysql_init(0);
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
                // inserer le module 
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