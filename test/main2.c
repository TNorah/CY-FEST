#include "main2.h"

int main(){
    
    Salle *salles = NULL;
    Concert *concerts = NULL;
    
    int choix = 99;
    int nbSalles = 0;
    int nbConcerts = 0;
    
    couleur("5;36");
    printf("-------------\n");
    printf("|| CY-FEST ||\n");
    printf("-------------\n");
    couleur("0");
    
    salles = lireSalle(&nbSalles, 0);
    //printf("nbSalles = %d",nbSalles);
    concerts = lireConcert(&nbConcerts, 0);
    //printf("nbConcerts = %d",nbConcerts);
    
    do{
        couleur("33");
        printf("|| MENU ||\n");
        couleur("0");

        printf("\n1- MODE MANAGER\n2- MODE FESTIVALIER\n3- RETOUR AU MENU\n4- QUITTER LE PROGRAMME\n\n");
        choix = scanfD(1);
        
        switch(choix){
            case 1:
                salles = modeManager(salles,concerts,&nbSalles,&nbConcerts);
                //printf("nbSalles = %d\n",nbSalles);
                break;
            case 2:
                salles = modeFestivalier(salles,concerts,&nbSalles,&nbConcerts);
                break;
            case 3:
                printf("|| Retour au menu ||\n");
                break;
            case 4:
                printf("|| Fin du programme ||\n");
                break;
            default :
                printf("Cette commande n'existe pas ! Recommencez\n\n");
                break;
        }
    }while(choix != 4);  
    
    free(salles);
    free(concerts);
	    
    return 0;
}
