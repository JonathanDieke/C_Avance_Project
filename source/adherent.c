#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../headers/adherent.h"
#include "../headers/global.h"
#include <mysql/mysql.h>

// MYSQL *_connexion  ;
void showMenuAdherent(/*MYSQL* connexion*/){
    // _connexion = connexion; 
    int choice = 0 ;

    do{

        puts("MENU ADHERENT");
        puts("1- AJOUTER UN ADHERENT");
        puts("2- LISTER LES ADHERENTS");
        puts("3- AFFICHER UN ADHERENT");
        puts("4- MODIFIER LES INFORMATIONS D'UN ADHERENT");
        puts("5- LISTER LES RETARDATAIRES");
        puts("6- SUPPRIMER UN ADHERENT");
        puts("7- Revenir en arrière");
        printf("\nCHOISIR UNE OPTION : ");
        
        scanf("%d", &choice);

        switch (choice){
            case 1:
                system("clear");
                puts("Ajout d'un nouvel adhérent ...");
                addAdherent();
                break;
            case 2:
                system("clear");
                showAdherents();
                break;
            case 3:
                system("clear");
                showAdherent();
                break;
            case 4:
                system("clear");
                editAdherent();
                break;
            case 5:
                system("clear");
                latecomersAdherent();
                break;
            case 6:
                system("clear");
                deleteAdherent();
                break;    
            case 7:
                system("clear");
                showMainMenu();
                break;    
            default:
                system("clear");
                puts("Veuillez faire un choix entre 1 et 6.\n");
                break;
        }
    
    }while(choice < 1 || choice > 7) ;


}

void addAdherent(/*MYSQL *connexion*/){ 

    char name[20], lname[30], address[30], birthdate[15] ;

    puts("Entrez le nom : ");
    scanf("%s", name);

    printf("Entrez le prénom : ");
    scanf("%s", lname);

    printf("Entrez l'adresse : ");
    scanf("%s", address);

    printf("Entrez la date d'anniversaire (AAAA-MM-JJ): ");
    scanf("%s", birthdate);

    char query[512] ;
    sprintf(query, "insert into adherents(name, lname, address, birthdate) values('%s', '%s', '%s', '%s')", name, lname, address, birthdate);

    system("clear");

    if(mysql_query(connexion, query) == 0){
        puts("\n\t--- Ajout réussi ! ---\n");

    }else{
        puts("\n\t---Echec de l'ajout, veuillez réessayer ! ---\n");
    }

    showMenuAdherent();

}

void showAdherents(){

    

    showMenuAdherent();
}

void showAdherent(){


    showMenuAdherent();
}

void editAdherent(){


    showMenuAdherent();
}

void deleteAdherent(){


    showMenuAdherent();
}

void latecomersAdherent(){


    showMenuAdherent();
}
