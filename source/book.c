#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../headers/global.h"
#include "../headers/book.h"


void showMenuBook(){
    int choice = 0 ;

    do{

        puts("MENU LIVRE");
        puts("1- AJOUTER UN LIVRE");
        puts("2- LISTER LES LIVRES");
        puts("3- AFFICHER UN LIVRE");
        puts("4- MODIFIER LES INFORMATIONS D'UN LIVRE"); 
        puts("5- SUPPRIMER UN LIVRE");
        puts("6- Revenir en arrière");
        printf("\nCHOISIR UNE OPTION : ");
        
        scanf("%d", &choice);

        switch (choice){
            case 1:
                system("clear");
                puts("Ajout d'un nouveau livre ...");
                addBook();
                break;
            case 2:
                system("clear");
                showBooks();
                break;
            case 3:
                system("clear");
                showBook();
                break;
            case 4:
                system("clear");
                editBook();
                break; 
            case 5:
                system("clear");
                deleteBook();
                break;    
            case 6:
                system("clear");
                showMainMenu();
                break;    
            default:
                system("clear");
                puts("Veuillez faire un choix entre 1 et 6.\n");
                break;
        }
    
    }while(choice < 1 || choice > 6) ;
}

void addBook(){ 

    printf("\nEntrez le titre : ");
    getchar();
    char *title = lire(50);

    printf("\nEntrez les mots clés : ");
    char *keywords = lire(80);

    printf("\nEntrez la date de parution (AAAA-MM-JJ) : ");
    char *released_date = lire(15);

    printf("\nEntrez le numéro de l'autheur : ");
    int author_number = atoi(lire(50));

    char query[256] ;
    sprintf(query, "insert into %s(title, keywords, released_date, author_number) values('%s', '%s', '%s', '%d')", BOOK_TABLE_NAME, title, keywords, released_date, author_number);

    system("clear");

    if(mysql_query(connexion, query) == 0){
        puts("\n\t--- Ajout réussi ! ---\n");
    }else{
        contactAdmin();
    }

    showMenuBook();
}

void showBooks(){

    char query [256];
    sprintf(query, "select b.number, b.title, b.keywords, b.released_date, a.name, a.lname from %s b, %s a where b.author_number = a.number", BOOK_TABLE_NAME, AUTHOR_TABLE_NAME);
    
    if(mysql_query(connexion, query) == 0){

        MYSQL_RES* results = mysql_store_result(connexion);

        if(results != NULL && mysql_num_rows(results) > 0){

            MYSQL_ROW row ;
            MYSQL_FIELD* fields ;

            puts("\nListe exhaustive des livres : \n ");
            puts(" -----------------------------------------------------------------------");
            puts("|\tId |\tTitre |\tMots clés |\tDate de parution |\tAutheur |");
            puts(" -----------------------------------------------------------------------");  

            while( (row = mysql_fetch_row(results)) != NULL ) {
                printf("|");
                for(int i = 0; i < 5; i++){
                    if(i != 4){
                        printf("\t%s |", row[i]);
                    }else{
                        printf("\t%s %s |", row[i], row[i+1]);
                    }
                }
                puts("");
            }

        }else{ 
            NoDataAvailabe();
        }
        doPause();
        system("clear");
    }else{
        contactAdmin();
    }
    showMenuBook();
}

void showBook(){
    int bookNumber = _getBookNumber("Affichage du livre ...") ;

    char query[128];
    sprintf(query, "select number, title, keywords, released_date, author_number from %s where number = '%d' ;", BOOK_TABLE_NAME, bookNumber);
    
    if(mysql_query(connexion, query) == 0){

         MYSQL_RES* results = mysql_store_result(connexion);

        if(results != NULL && mysql_num_rows(results) > 0){

            MYSQL_ROW row ; 

            printf("\n\t\tLivre n°%d : \n", bookNumber);

            while( (row = mysql_fetch_row(results)) != NULL ) {
                printf("Id : %s \nTitre : %s\nMots clés : %s \nDate de parution : %s \nAutheur : %s\n", row[0],row[1],row[2],row[3],row[4]);
            }

        }else{ 
            NoDataAvailabe();
        }
        doPause();
        system("clear");
    }else{
        contactAdmin();       
    }
    showMenuBook();
}

void editBook(){ 
    int bookNumber = _getBookNumber("Edition du livre ...") ;

    char query[128] ;
    sprintf(query, "select title, keywords, released_date, author_number from %s where number = %d ;", BOOK_TABLE_NAME, bookNumber) ;

    if(mysql_query(connexion, query) == 0){
        
        MYSQL_RES* results = mysql_store_result(connexion);
        MYSQL_ROW row ; 

        char title[50], keywords[100], released_date[15];
        int author_number;

        if( (row = mysql_fetch_row(results)) != NULL && mysql_num_rows(results) > 0) {

            sprintf(title,"%s", row[0]);
            sprintf(keywords,"%s", row[1]);
            sprintf(released_date,"%s", row[2]);
            author_number = atoi(row[3]);

            printf("\nEntrez le titre (%s) : ", title);
            getchar();
            char* new_title = lire(50);

            printf("\nEntrez les mots clés (%s) : ", keywords);
            char* new_keywords = lire(100);

            printf("\nEntrez la date de parution (%s) : ", released_date);
            char* new_released_date = lire(15);

            printf("\nEntrez le numéro de l'autheur (%d) : ", author_number);
            int new_author_number = atoi(lire(5));
    

            if(new_title[0] != 0) strcpy(title, new_title);
            if(new_keywords[0] != 0) strcpy(keywords, new_keywords);
            if(new_released_date[0] != 0) strcpy(released_date, new_released_date);
            if(new_author_number != 0) author_number = new_author_number;

            char query[300] ;
            sprintf(query,"update %s set title = '%s', keywords = '%s', released_date = '%s', author_number = '%d' where number = %d", BOOK_TABLE_NAME, title, keywords, released_date, author_number, bookNumber) ;

            system("clear");

            if(mysql_query(connexion, query) == 0){
                puts("\n\t--- Edition réussie ! ---\n");
            }else{
                puts("\n\t--- Echec de l'édition, veuillez réessayer ! ---\n");
            } 
        }else{
            NoDataAvailabe();
            puts("\n\t--- Assurez-vous d'avoir saisi le bon numéro de livre --- \n");
        }
        doPause();
        system("clear");
    }else{
        contactAdmin();
    }

    showMenuBook();

}

void deleteBook(){
    
    int bookNumber = _getBookNumber("Suppression du livre ...");

    char query[64];
    sprintf(query, "delete from %s where number = '%d' ;", BOOK_TABLE_NAME, bookNumber);
    
    system("clear");
    if(mysql_query(connexion, query) == 0){
        puts("\n\t--- Suppression réussie ! --- \n");
    }else{
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
    }
    
    showMenuBook();
}

int _getBookNumber(char* message){
    int bookNumber ;

    printf("Entrez le numéro du livre : ");
    scanf("%d", &bookNumber);
    system("clear");
    printf("%s\n\n", message);

    return bookNumber ;
}
