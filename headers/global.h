#ifndef H_GLOBAL_H

#define H_GLOBAL_H

#include <mysql/mysql.h>


extern MYSQL *connexion  ;

extern char* BOOK_TABLE_NAME ; 
extern char* ADHERENT_TABLE_NAME ;
extern char* AUTHOR_TABLE_NAME ;
extern char* BORROWING_TABLE_NAME ;

void initializeConnexion();

void showMainMenu();

char* lire(int size);

char* getCurrentDate();

char* getCurrentDateTime();

void doPause();

void failRequest_Retry();

void impossibleRequestTreatment();

void contactAdmin();

void NoDataAvailabe();  

#endif