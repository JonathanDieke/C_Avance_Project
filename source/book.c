#include <stdio.h>
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

    char title[50], keywords[80], released_date[15];
    int author_number ;

    puts("Entrez le titre : ");
    scanf("%s", title);

    printf("Entrez les mots clés : ");
    scanf("%s", keywords);

    printf("Entrez la date de parution (AAAA-MM-JJ) : ");
    scanf("%s[^\n]", released_date);

    printf("Entrez le numéro de l'autheur : ");
    scanf("%d", &author_number);

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
    int bookNumber ;

    printf("Entrez le numéro du livre : ");
    scanf("%d", &bookNumber);

    char query[64];
    sprintf(query, "select * from books where number = '%d' ;", bookNumber);
    
    if(mysql_query(connexion, query) != 0){
        system("clear");
        puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
        showMenuBook();
    }

    MYSQL_RES* results = mysql_store_result(connexion);

    if(results != NULL){

        MYSQL_ROW row ;
        MYSQL_FIELD* fields ;

        printf("\n\t\tLivre n°%d : \n", bookNumber);

        while( (row = mysql_fetch_row(results)) != NULL ) {
            printf("Id : %s \nTitre : %s\nMots clés : %s \nDate de parution : %s \nAutheur : %s\n", row[0],row[1],row[2],row[3],row[4]);
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

void editBook(){
    puts("edit book");

    showMenuBook();
}

void deleteBook(){
    
    int bookNumber = 0;

    printf("Entrez le numéro du livre : ");
    scanf("%d", &bookNumber);

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