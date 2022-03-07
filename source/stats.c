#define MATHLIB_STANDALONE
#include <stdio.h>
#include <R.h>
#include <Rmath.h>
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
                system("clear");
                showMenuStats();
                break;  
            case 2:
                system("clear");
                puts("\nFonctionnalité en cours de développement...\n");
                doPause();
                system("clear");
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

void borrowedThisMonth(){
    // char currentDate[15] = getCurrentDate();

    // char query[256];

    // sprintf(query, "select count(*) from %s where out_date", BORROWING_TABLE_NAME);

    // puts("Le nombre de livres empruntés ce mois est de : %d", numberBorrowed);
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
}
