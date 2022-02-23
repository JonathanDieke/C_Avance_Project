#include <stdio.h>
#include <time.h>
// #include <string.h>
// #include <unistd.h>
#include "../headers/global.h"
#include "../headers/borrowing.h"


void showMenuBorrowing(){
    int choice = 0 ;

    do{

        puts("MENU EMPRUNT");
        puts("1- AJOUTER UN EMPRUNT");
        puts("2- LISTER LES EMPRUNTS");
        puts("3- AFFICHER UN EMPRUNT");
        puts("4- MODIFIER UN EMPRUNT");
        puts("5- LISTER LES RETARDATAIRES");
        puts("6- SUPPRIMER UN EMPRUNT");
        puts("7- Revenir en arrière");
        printf("\nCHOISIR UNE OPTION : ");
        
        scanf("%d", &choice);

        switch (choice){
            case 1:
                system("clear");
                puts("Ajout d'un nouvel emprunt ...");
                addBorrowing();
                break;
            case 2:
                system("clear");
                showBorrowings();
                break;
            case 3:
                system("clear");
                showBorrowing();
                break;
            case 4:
                system("clear");
                editBorrowing();
                break;
            case 5:
                system("clear");
                latecomersBorrowing();
                break;
            case 6:
                system("clear");
                deleteBorrowing();
                break;    
            case 7:
                system("clear");
                showMainMenu();
                break;    
            default:
                system("clear");
                puts("Veuillez faire un choix entre 1 et 7.\n");
                break;
        }
    
    }while(choice < 1 || choice > 7) ;
}

void addBorrowing(){

    time_t t_t = time(NULL);
    struct tm now = *localtime(&t_t) ;
    char current_date[15];

    sprintf(current_date, "%d-%d-%d", (now.tm_year+1900), (now.tm_mon+1), now.tm_mday);

    printf("\nEntrez l'identifiant de l'adhérent : ");
    getchar();
    int adherent_number = atoi(lire(5));

    printf("\nEntrez le numéro du livre : ");
    int book_number = atoi(lire(5));

    printf("\nEntrez la date d'emprunt (%s) : ", current_date);
    char* out_date = lire(15);
    if(out_date[0] == 0) out_date = current_date; 

    printf("\nEntrez la date de retour prévue (AAAA-MM-JJ) : ");
    char* return_date = lire(15);

    printf("\nEntrez la date de retour effective (AAAA-MM-JJ) (nulle par défaut) : ");
    char* effective_return_date = lire(15);

    char query[256] ;
    if(effective_return_date[0] == 0) {
        sprintf(query, "insert into %s(adherent_number, book_number, out_date, return_date) values('%d', '%d', '%s', '%s')", BORROWING_TABLE_NAME, adherent_number, book_number, out_date, return_date);
    }else{
        sprintf(query, "insert into %s(adherent_number, book_number, out_date, return_date, effective_return_date) values('%d', '%d', '%s', '%s', '%s')", BORROWING_TABLE_NAME, adherent_number, book_number, out_date, return_date, effective_return_date);
    }

    system("clear");

    if(mysql_query(connexion, query) == 0){
        puts("\n\t--- Ajout réussi ! ---\n");
    }else{
        puts("\n\t--- Echec de l'ajout, veuillez réessayer ! ---\n");
    }

    showMenuBorrowing();
}

void showBorrowing(){
    
}

void showBorrowings(){
    
}

void editBorrowing(){
    
}

void deleteBorrowing(){
    
} 

void latecomersBorrowing(){
    // récupérer tous les emprunts
    // comparer, pour chaque emrpunt, la date courante et la date de retour
    // si la date de retour est dépassée (date de retour supérieure à la date courante), considérer l'adhérent comme retardataire
    // afficher l'ensemble des retardataires

    showMenuBorrowing();
}