// #include <mysql/mysql.h>
#include <stdio.h>
#include <time.h>
#include "../headers/adherent.h"
#include "../headers/book.h"
#include "../headers/borrowing.h"
#include "../headers/stats.h"
#include "../headers/global.h"  

MYSQL *connexion = NULL; 

char* BOOK_TABLE_NAME = "books" ;
char* ADHERENT_TABLE_NAME = "adherents";
char* AUTHOR_TABLE_NAME = "authors";
char* BORROWING_TABLE_NAME = "borrowings";

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
        puts("4- Statistiques ");
        puts("5- Quitter ");

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
                system("clear");
                showMenuBorrowing();
                break;
            case 4:
                system("clear");
                showMenuStats();
                break;  
            case 5:
                system("clear");
                puts("Bye ! ");
                exit(0);
                break;            
            default:
                system("clear");
                puts("Veuillez faire un choix entre 1 ET 5\n");
                break;
        }
    } while (choice < 1 || choice > 4);
    
}

char* getCurrentDate(){
    time_t t_t = time(NULL);
    struct tm now = *localtime(&t_t) ;
    char* current_date = (char*) malloc(sizeof(char)*15);

    sprintf(current_date, "%d-%d-%d", (now.tm_year+1900), (now.tm_mon+1), now.tm_mday);

    return current_date ;
}

void doPause(){
    getchar();
    printf("\n\nAppuyer sur une touche pour continuer ...\n");
    getchar();
}

void failRequest_Retry(){
    puts("\n\t--- Echec de la requête, veuillez, réessayer ! --- \n");
}

void impossibleRequestTreatment(){
    puts("\n\t--- Impossible de traiter la requête ! --- \n");
}

void contactAdmin(){
    puts("\n\t--- Echec, veuillez contacter l'administrateur ! ---\n");
}

void NoDataAvailabe(){
    puts("\n\tAucune donnée disponible ! \n");
}

char* getCurrentDateTime(){
    time_t t_t = time(NULL);
    struct tm now = *localtime(&t_t) ;
    char* current_datetime = (char*) malloc(sizeof(char)*25);

    sprintf(current_datetime, "%d-%d-%d %d:%d:%d", (now.tm_year+1900), (now.tm_mon+1), now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);

    return current_datetime ;
}
