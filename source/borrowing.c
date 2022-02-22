#include <stdio.h>
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