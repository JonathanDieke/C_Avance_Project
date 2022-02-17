#ifndef H_GLOBAL_H
#define H_GLOBAL_H

#include <mysql/mysql.h>


extern MYSQL *connexion  ;

void initializeConnexion();

void showMainMenu();


#endif