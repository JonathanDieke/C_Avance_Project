#include <stdio.h>
#include <string.h>
#include "../headers/book.h"
#include <unistd.h>
#include "../headers/global.h"

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
    sprintf(query, "insert into books(title, keywords, released_date, author_number) values('%s', '%s', '%s', '%d')", title, keywords, released_date, author_number);

    system("clear");

    if(mysql_query(connexion, query) == 0){
        puts("\n\t--- Ajout réussi ! ---\n");
    }else{
        puts("\n\t--- Echec de l'ajout, veuillez réessayer ! ---\n");
    }

    showMenuBook();
}

void showBooks(){

    char* query  ="select * from books";
    
    if(mysql_query(connexion, query) != 0){
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
        showMenuBook();
    }

    MYSQL_RES* results = mysql_store_result(connexion);

    if(results != NULL){

        MYSQL_ROW row ;
        MYSQL_FIELD* fields ;

        puts("\nListe exhaustive des ahérents : \n ");
        puts(" -----------------------------------------------------------------------");
        puts("|\tId |\tTitre |\tMots clés |\tDate de parution |\tAutheur |");
        puts(" -----------------------------------------------------------------------");  

        while( (row = mysql_fetch_row(results)) != NULL ) {
            // fields = mysql_fetch_field(results); 
            printf("|");
            for(int i = 0; i < 5; i++){
                printf("\t%s |", row[i]);
            }
            puts("");
        }

        sleep(5);
        system("clear");
        showMenuBook();

    }else{
        system("clear");
        puts("\n\t--- Impossible de traiter la requête ! --- \n");
        sleep(3);
        showMenuBook();
    }
}

void showBook(){
    int bookNumber = _getBookNumber("Affichage du livre ...") ;

    char query[128];
    sprintf(query, "select number, title, keywords, released_date, author_number from books where number = '%d' ;", bookNumber);
    
    if(mysql_query(connexion, query) != 0){
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
        showMenuBook();
    }else{

        MYSQL_RES* results = mysql_store_result(connexion);

        if(results != NULL){

            MYSQL_ROW row ; 

            printf("\n\t\tLivre n°%d : \n", bookNumber);

            while( (row = mysql_fetch_row(results)) != NULL ) {
                printf("Id : %s \nTitre : %s\nMots clés : %s \nDate de parution : %s \nAutheur : %s\n", row[0],row[1],row[2],row[3],row[4]);
            }

            sleep(5);
            system("clear");

        }else{
            system("clear");
            puts("\n\t--- Impossible de traiter la requête ! --- \n");
            sleep(3);
        }
        showMenuBook();
    }


}

void editBook(){ 
    int bookNumber = _getBookNumber("Edition du livre ...") ;

    char query[128] ;
    sprintf(query, "select title, keywords, released_date, author_number from books where number = %d ;", bookNumber) ;

    if(mysql_query(connexion, query) != 0){
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
        showMenuBook();
    }

    MYSQL_RES* results = mysql_store_result(connexion);
    MYSQL_ROW row ; 

    char title[50], keywords[100], released_date[25], new_released_date[15]; 
    int author_number;

    if( (row = mysql_fetch_row(results)) != NULL ) {

        sprintf(title,"%s", row[0]);
        sprintf(keywords,"%s", row[1]);
        sprintf(released_date,"%s", row[2]);
        author_number = atoi(row[3]);

        printf("\nEntrez le titre (%s) : ", title);
        getchar();
        char* new_title = lire(30);

        printf("\nEntrez les mots clés (%s) : ", keywords);
        char* new_keywords = lire(30);

        printf("\nEntrez la date de parution (%s) : ", released_date);
        char* new_released_date = lire(15);

        printf("\nEntrez le numéro de l'autheur (%d) : ", author_number);
        int new_author_number = atoi(lire(2));
 

        if(new_title[0] != 0) strcpy(title, new_title);
        if(new_keywords[0] != 0) strcpy(keywords, new_keywords);
        if(new_released_date[0] != 0) strcpy(released_date, new_released_date);
        if(new_author_number != 0) author_number = new_author_number;

        char query[300] ;
        sprintf(query,"update books set title = '%s', keywords = '%s', released_date = '%s', author_number = '%d' where number = %d", title, keywords, released_date, author_number, bookNumber) ;

        system("clear");

        if(mysql_query(connexion, query) == 0){
            puts("\n\t--- Edition réussie ! ---\n");
        }else{
            puts("\n\t--- Echec de l'édition, veuillez réessayer ! ---\n");
        } 
    }else{
        system("clear");
        puts("\n\t--- Impossible de traiter la requête ! --- \n");
    }

    showMenuBook();
}

void deleteBook(){
    
    int bookNumber = _getBookNumber("Suppression du livre ...");

    char query[64];
    sprintf(query, "delete from books where number = '%d' ;", bookNumber);
    
    system("clear");
    if(mysql_query(connexion, query) == 0){
        puts("\n\t--- Suppression réussie ! --- \n");
    }else{
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
    }
    sleep(2);
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