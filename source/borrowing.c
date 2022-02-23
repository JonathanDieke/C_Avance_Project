#include <stdio.h> 
#include <unistd.h>
#include <string.h>
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
        puts("6- LIVRES EMPRUNTES");
        puts("7- SUPPRIMER UN EMPRUNT");
        puts("8- Revenir en arrière");
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
                borrowedBook();
                break; 
            case 7:
                system("clear");
                deleteBorrowing();
                break;    
            case 8:
                system("clear");
                showMainMenu();
                break;    
            default:
                system("clear");
                puts("Veuillez faire un choix entre 1 et 7.\n");
                break;
        }
    
    }while(choice < 1 || choice > 8) ;
}

void addBorrowing(){

    char* current_date = getCurrentDate();

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

void showBorrowings(){
    char query [256];
    sprintf(query, "select b1.id, a.name, a.lname, b2.title, b1.out_date, b1.return_date, b1.effective_return_date from %s b1, %s a, %s b2 where b1.adherent_number = a.number and b1.book_number = b2.number", BORROWING_TABLE_NAME, ADHERENT_TABLE_NAME, BOOK_TABLE_NAME);
     
    if(mysql_query(connexion, query) == 0){
        MYSQL_RES* results = mysql_store_result(connexion);

        if(results != NULL){

            MYSQL_ROW row ;
            MYSQL_FIELD* fields ;

            puts("\nListe exhaustive des emprunts : \n ");
            puts(" -----------------------------------------------------------------------------------------------");
            puts("|\tId |\tAdhérents |\tLivre |\tDate d'emprunt |\tRetour prévu |\tRetour effectif |");
            puts(" -----------------------------------------------------------------------------------------------");  

            while( (row = mysql_fetch_row(results)) != NULL ) {
                printf("|");
                for(int i = 0; i < 6; i++){
                    if(i == 1){
                        printf("\t%s %s |", row[i], row[i+1]);
                        i++ ;
                    }else{
                        printf("\t%s |", row[i]);
                    }
                }
                puts("");
            }

            sleep(5);
            system("clear");
            showMenuBorrowing();

        }else{
            system("clear");
            puts("\n\t--- Impossible de traiter la requête ! --- \n");
            sleep(3);
            showMenuBorrowing();
        }                                                                                                           
    }else{
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
        showMenuBorrowing();
    }      
}

void showBorrowing(){

    int borrowingNumber = _getBorrowingNumber("Affichage des informations sur l'emprunt...");

    char query [256];
    sprintf(query, "select b1.id, a.name, a.lname, b2.title, b1.out_date, b1.return_date, b1.effective_return_date from %s b1, %s a, %s b2 where b1.adherent_number = a.number and b1.book_number = b2.number and b1.id='%d'", BORROWING_TABLE_NAME, ADHERENT_TABLE_NAME, BOOK_TABLE_NAME, borrowingNumber);
     
    if(mysql_query(connexion, query) == 0){

         MYSQL_RES* results = mysql_store_result(connexion);

        if(results != NULL){

            MYSQL_ROW row ;
            MYSQL_FIELD* fields ;

            printf("\nEmprunts n°%d: \n ", borrowingNumber);
            puts(" -----------------------------------------------------------------------------------------------");
            puts("|\tId |\tAdhérents |\tLivre |\tDate d'emprunt |\tRetour prévu |\tRetour effectif |");
            puts(" -----------------------------------------------------------------------------------------------");  

            while( (row = mysql_fetch_row(results)) != NULL ) {
                printf("|");
                for(int i = 0; i < 6; i++){
                    if(i == 1){
                        printf("\t%s %s |", row[i], row[i+1]);
                        i++ ;
                    }else{
                        printf("\t%s |", row[i]);
                    }
                }
                puts("");
            }

            sleep(5);
            system("clear");
            showMenuBorrowing();

        }else{
            system("clear");
            puts("\n\t--- Impossible de traiter la requête ! --- \n");
            sleep(3);
            showMenuBorrowing();
        }    
    }else{
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
        showMenuBorrowing();
    }

}

void editBorrowing(){
    int borrowingNumber = _getBorrowingNumber("Edition d'un emprunt...");
 
    char query[300] ;
    sprintf(query, "select a.name, a.lname, b2.title, b1.out_date, b1.return_date, b1.effective_return_date from %s b1, %s a, %s b2 where b1.adherent_number = a.number and b1.book_number = b2.number and b1.id='%d'", BORROWING_TABLE_NAME, ADHERENT_TABLE_NAME, BOOK_TABLE_NAME, borrowingNumber);
     
    if(mysql_query(connexion, query) == 0){

        MYSQL_RES* results = mysql_store_result(connexion);
        MYSQL_ROW row ; 

        char adherent[80], book[50], out_date[15], return_date[15], effective_return_date[15];

        if( (row = mysql_fetch_row(results)) != NULL ) {

            sprintf(adherent,"%s %s", row[0], row[1]);
            sprintf(book,"%s", row[2]);
            sprintf(out_date,"%s", row[3]);
            sprintf(return_date,"%s", row[4]);
            sprintf(effective_return_date,"%s", row[5]);
            
            printf("\nNoms de l'adhérent : %s", adherent);  

            printf("\nTitre du livre : %s ", book);

            printf("\nDate d'emprunt : %s ", out_date);

            printf("\nDate de retour : %s ", return_date);

            if(row[5] == NULL)  printf("\nDate de retour effective (AAAA-MM-JJ) :");
            else   printf("\nDate de retour effective (valeur actuelle : %s) : ", effective_return_date);
            getchar();
            char* new_effective_return_date = lire(15);
 
            if(new_effective_return_date[0] != 0) {
                strcpy(effective_return_date, new_effective_return_date); 
                char query[256] ;
                sprintf(query,"update %s set effective_return_date = '%s' where id = %d", BORROWING_TABLE_NAME, effective_return_date, borrowingNumber) ;

                system("clear");

                if(mysql_query(connexion, query) == 0){
                    puts("\n\t --- Modificaion réussie ! ---");                    
                }else{
                    puts("\n\t --- Echec des modifications, veuillez réessayer ! ---");
                }
                showMainMenu();
            }else{
                system("clear");

                puts("\n\t--- Aucune modification apportée ! --- \n");

                showMainMenu();
            }
 
        }else{
            system("clear");
            puts("\n\t--- Impossible de traiter la requête ! --- \n");
        }


    }else{
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez réessayer ! --- \n");
        sleep(3);
        showMenuBorrowing();

    }
}

void deleteBorrowing(){
    int borrowingNumber = _getBorrowingNumber("Suppression d'un emprunt ...");

    char query[64];
    sprintf(query, "delete from %s where id = '%d' ;", BORROWING_TABLE_NAME, borrowingNumber);
    
    system("clear");
    if(mysql_query(connexion, query) == 0){
        puts("\n\t--- Suppression réussie ! --- \n");
    }else{
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
    }
    sleep(2);
    showMenuBorrowing();
} 

void latecomersBorrowing(){
    // récupérer tous les emprunts
    // comparer, pour chaque emrpunt, la date courante et la date de retour
    // si la date de retour est dépassée (date de retour supérieure à la date courante), considérer l'adhérent comme retardataire
    // afficher l'ensemble des retardataires

    showMenuBorrowing();

}


void borrowedBook(){

}

int _getBorrowingNumber(char* message){
    int borrowingNumber ;

    printf("Entrez l'identifiant de l'emprunt : ");
    scanf("%d", &borrowingNumber);
    system("clear");
    printf("%s\n\n", message);

    return borrowingNumber ;
}