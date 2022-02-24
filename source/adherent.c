#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../headers/global.h"
#include "../headers/adherent.h"

void showMenuAdherent(){
    int choice = 0 ;

    do{

        puts("MENU ADHERENT");
        puts("1- AJOUTER UN ADHERENT");
        puts("2- LISTER LES ADHERENTS");
        puts("3- AFFICHER UN ADHERENT");
        puts("4- MODIFIER LES INFORMATIONS D'UN ADHERENT"); 
        puts("5- SUPPRIMER UN ADHERENT");
        puts("6- Revenir en arrière");
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
                deleteAdherent();
                break;    
            case 6:
                system("clear");
                showMainMenu();
                break;    
            default:
                system("clear");
                puts("Veuillez faire un choix entre 1 et 7.\n");
                break;
        }
    
    }while(choice < 1 || choice > 6) ;
}

void addAdherent(){    

    printf("\nEntrez le nom : ");
    getchar();
    char* name = lire(20);

    printf("Entrez le prénom : ");
    char* lname = lire(30);

    printf("Entrez l'adresse : ");
    char* address = lire(30);

    printf("Entrez la date d'anniversaire (AAAA-MM-JJ): ");
    char* birthdate = lire(15);

    char query[512] ;
    sprintf(query, "insert into %s(name, lname, address, birthdate) values('%s', '%s', '%s', '%s')", ADHERENT_TABLE_NAME, name, lname, address, birthdate);

    system("clear");

    if(mysql_query(connexion, query) == 0){
        puts("\n\t--- Ajout réussi ! ---\n");
    }else{
        puts("\n\t--- Echec de l'ajout, veuillez réessayer ! ---\n");
    }

    showMenuAdherent();
}

void showAdherents(){

    char query[256];
    sprintf(query, "select number, name, lname, address, birthdate from %s", ADHERENT_TABLE_NAME);

    if(mysql_query(connexion, query) != 0){
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
        showMenuAdherent();
    }

    MYSQL_RES* results = mysql_store_result(connexion);

    if(results != NULL){

        MYSQL_ROW row ;
        MYSQL_FIELD* fields ;

        puts("\nListe exhaustive des ahérents : \n ");
        puts(" -------------------------------------------------------------------------");
        puts("|\t Id |\t Nom |\t Prénom |\t Adresse |\t Date de naissance |");
        puts(" -------------------------------------------------------------------------");  

        while( (row = mysql_fetch_row(results)) != NULL ) { 
            // printf("|\t\t %s |\t\t %s |\t\t\t %s |\t\t\t %s |\t\t %s |\n", row[0],row[1],row[2],row[3],row[4]);
            for(int i = 0; i < 5; i++){
                printf("\t%s |", row[i]);
            } 
            puts("");
        }

        sleep(5);
        system("clear");
        showMenuAdherent();

    }else{
        system("clear");
        puts("\n\t--- Impossible de traiter la requête ! --- \n");
        sleep(3);
        showMenuAdherent();
    }
}

void showAdherent(){
    int adherentNumber = _getAdherentNumber("Affichage de l'adhérent...");

    char query[512];
    sprintf(query, "select number, name, lname, address, birthdate from %s where number = %d", ADHERENT_TABLE_NAME, adherentNumber);

    if(mysql_query(connexion, query) == 0){
        MYSQL_RES* results = mysql_store_result(connexion);

        if(results != NULL){

            MYSQL_ROW row ; 

            printf("\n\t\tAdherent n°%d : \n", adherentNumber);

            while( (row = mysql_fetch_row(results)) != NULL ) {
                printf("Id : %s \nNom : %s\nPrénom : %s \nAdresse : %s \nDate de naissance : %s\n", row[0],row[1],row[2],row[3],row[4]);
            }

            sleep(5);
            system("clear");

        }else{
            system("clear");
            puts("\n\t--- Impossible de traiter la requête ! --- \n");
            sleep(3);
        }
        showMenuAdherent();
    }else{
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
        showMenuAdherent();
    }

    showMenuAdherent();
}

void editAdherent(){

    int adherentNumber = _getAdherentNumber("Edition de l'adhérent ...") ;

    char query[128] ;
    sprintf(query, "select name, lname, address, birthdate from %s where number = %d ;", ADHERENT_TABLE_NAME, adherentNumber) ;

    if(mysql_query(connexion, query) != 0){
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
        showMenuAdherent();
    }

    MYSQL_RES* results = mysql_store_result(connexion);
    MYSQL_ROW row ; 

    char name[30], lname[50], address[50], birthdate[15];  

    if( (row = mysql_fetch_row(results)) != NULL ) {

        sprintf(name,"%s", row[0]);
        sprintf(lname,"%s", row[1]);
        sprintf(address,"%s", row[2]);
        sprintf(birthdate,"%s", row[3]);

        printf("\nEntrez le nom (%s) : ", name);
        getchar();
        char* new_name = lire(30);

        printf("\nEntrez le prénom (%s) : ", lname);
        char* new_lname = lire(50);

        printf("\nEntrez l'adresse (%s) : ", address);
        char* new_address = lire(50);

        printf("\nEntrez la date de naissance (%s) : ", birthdate);
        char* new_birthdate = lire(15);
 

        if(new_name[0] != 0) strcpy(name, new_name);
        if(new_lname[0] != 0) strcpy(lname, new_lname);
        if(new_address[0] != 0) strcpy(address, new_address);
        if(new_birthdate[0] != 0) strcpy(birthdate, new_birthdate); 

        char query[300] ;
        sprintf(query,"update %s set name = '%s', lname = '%s', address = '%s', birthdate = '%s' where number = %d", ADHERENT_TABLE_NAME, name, lname, address, birthdate, adherentNumber) ;

        system("clear");

        if(mysql_query(connexion, query) == 0){
            puts("\n\t--- Edition réussie ! ---\n");
        }else{
            puts("\n\t--- Echec de l'édition, veuillez réessayer ! ---\n");
        } 
    }else{
        system("clear");
        puts("\n\t--- Impossible de traiter la requête ! (Assurez-vous d'avoir saisi le bon numéro d'adhérent) --- \n");
    }

    showMenuAdherent();
}

void deleteAdherent(){

    int adherentNumber = _getAdherentNumber("Suppression de l'adhérent ...");

    char query[64];
    sprintf(query, "delete from %s where number = %d ;", ADHERENT_TABLE_NAME, adherentNumber);
    
    system("clear");
    
    if(mysql_query(connexion, query) == 0){
        puts("\n\t--- Suppression réussie ! --- \n");
    }else{
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
    }
    sleep(2);
    
    showMenuAdherent();
}

int _getAdherentNumber(char* message){
    int adherentNumber ;

    printf("Entrez le numéro de l'adhérent : ");
    scanf("%d", &adherentNumber);
    system("clear");
    printf("%s\n\n", message);

    return adherentNumber ;
}

