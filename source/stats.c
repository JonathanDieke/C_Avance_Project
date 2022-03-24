#define MATHLIB_STANDALONE
#include <stdio.h>
#include <R.h>
// #include <Rmath.h>
#include <Rinternals.h>
#include <Rembedded.h>
#include "../headers/global.h"
#include "../headers/stats.h"

void showMenuStats(){
    int choice = 0 ;  

    do{
        puts("MENU STATISTIQUES"); 
        puts("1- Appeler la fonction norm_rand() (depuis R) ");
        puts("2- Nombre moyen d'emprunts par mois (depuis R) "); 
        puts("2- Calcul du coefficient de corrélation (depuis R) "); 
        puts("3- Quitter "); 

        printf("CHOISIR UNE OPTION : "); 
        scanf("%d", &choice);

        switch (choice){
            case 1 :
                system("clear");  
                ma_norm(); 
                showMenuStats();
                break;  
            case 2:
                system("clear");
                R_Mean();
                showMenuStats();
                break;
            case 3:
                system("clear");
                showMainMenu();
                break;            
            default:
                system("clear");
                puts("Veuillez faire un choix entre 1 ET 3\n");
                break;
        }
    } while (choice < 1 || choice > 3);
}

void ma_norm() {  

    printf("\nGénérer combien de nombres ? (minimum 1) : ");
    getchar();
    int N = atoi(lire(2));

    if(N >= 1 && N<100){
        double d[N] ;
        
        for( int i =0; i< N; i++) {
            
            d[i] = norm_rand(); // Utilisation de la fonction norm rand de Rmath.h

            printf ("res[%d] = %f\n", i, d[i]) ;
        } 

    }else{
        printf("\nLe nombre entré n'est pas bon\n");
    }

    doPause();
    system("clear");
}

void R_Mean(){
   
    // int  mean = meanBorrowedBook("legerant", "Tarzan225", "biblio", "localhost");

    // int r_argc = 2;
    // char *r_argv[] = { "R", "--silent" };
    // Rf_initEmbeddedR(r_argc, r_argv);

    source("R_functions.R"); 
    SEXP meanBorrowedBook;
    PROTECT(meanBorrowedBook = lang2(install("meanBorrowedBook"), mkString("NULL")));
 
    int evalError;
    SEXP res = R_tryEval(meanBorrowedBook, R_GlobalEnv, &evalError);

    if (!evalError){
        double *result = REAL(res);
        printf("\nLe nombre moyen d'emprunts par mois est de : %f", *result);
    }
    else{
        printf("\nUne erreur s'est produite durant l'appel de la fonction R\n");
    }
    
    UNPROTECT(2);
    

    // puts("\nEn cours de développement.. \n");

    doPause();

    system("clear");
}


void source(const char *name)
{
    SEXP e;

    PROTECT(e = lang2(install("source"), mkString(name)));
    R_tryEval(e, R_GlobalEnv, NULL);
    UNPROTECT(1);
}
