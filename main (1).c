#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COULEURS
#define MAX 30
#define couleur(param) printf("\033[%sm",param)

typedef struct{
    
    int réservé;
    char catégorie;
    
}Siège;

typedef struct{
    
    int nbSièges;
    Siège *sièges;
    
}Rangée;

typedef struct{
    
    char nom[MAX];
    int nbRangées;
    int actif;
    Rangée *rangées;
    
}Salle;

int rechercheSalle(Salle *salle, char *n, int nbTotal){

    // boucle vérifiant si le nom existe
    // si oui, on affiche et on arrete la fonction
    // si non , on dit que y a pas et on arrete la fonction
    
    for(int i=0; i<nbTotal; i++){
        
        if(strcmp(n, salle[i].nom) == 0){
            
            printf("Cette salle existe !\n");
            return i; // donne l'indice de la salle
        }
    }
    printf("Cette salle n'existe pas !\n");
    return 0;
    
}

void modeManager(){
    
    // Doit créer une ou plusieurs salles
    // choisit le nombre de sièges et nombre de rangées par catégorie (A et B) 
    // => le reste des sièges sont en catégorie C
    // Choisit si une salle a une fosse (pas catégorie A) ou non
    // Choisit le prix d'une catégorie
    // Choisit la date et l'heure de fin d'un concert
    // Si un concert est terminé, il peut remodifier une salle
    // Il peut consulter l'état une salle (en concert, concert terminé, etc.)
    
    Salle *salle = NULL;
    int nB = 0;
    char input;
    
    printf("||MODE MANAGER||\n");
    printf("||Creation de salle||\n");
    
    printf("Combien de salles ?\n");
    scanf("%d",&nB);
    
    salle = malloc(nB * sizeof(Salle));
    
    if(salle == NULL)
    {
        exit(1);
    }
    
    for(int i=0; i<nB; i++){ // Crée une salle
    
        printf("Nom de la salle n°%d ?\n", i+1);
        scanf("%s",salle[i].nom);
        
        printf("Combien de rangees ?\n");
        scanf("%d",&salle[i].nbRangées);
        
        salle[i].rangées = malloc(salle[i].nbRangées * sizeof(*salle[i].rangées));
        
        if(salle[i].rangées == NULL)
        {
            exit(2);
        }
        
        for(int j=0; j<(salle[i].nbRangées); j++){ // Crée les rangées de sièges
            
            printf("Combien de sièges pour la rangee n°%d ?\n", j+1);
            scanf("%d",&salle[i].rangées[j].nbSièges);
            
            salle[i].rangées[j].sièges = malloc(salle[i].rangées[j].nbSièges * sizeof(*salle[i].rangées[j].sièges));
            
            if(salle[i].rangées[j].sièges == NULL)
            {
                exit(3);   
            }
            
            for(int k=0; k<(salle[i].rangées[j].nbSièges); k++){ // Initialise les sièges et définie une catégorie
            
                printf("Quel catégorie de prix pour le siège n°%d de la rangee n°%d ?\n", k+1,j+1);
                scanf(" %c",&salle[i].rangées[j].sièges[k].catégorie);
                
                salle[i].rangées[j].sièges[k].réservé = 0; // NON RESERVE 
            }
        }
    }
    
    printf("||Creation de salle(s) terminée||\n");
    
    // Appelle une fonction pour rechercher une salle
    
    /*
    char test[MAX];
    printf("Donnez le nom de la salle que vous recherchez :\n");
    scanf("%s",test);
    int indice = rechercheSalle(salle, test, nB);
    printf("Numéro de la salle %d\n",indice+1);
    */
    
    // en fonction de la salle à afficher
    
    
    for(int i=0; i<nB; i++){
        
        for(int j=0; j<(salle[i].nbRangées); j++){
            
            for(int k=0; k<(salle[i].rangées[j].nbSièges); k++){
                
                if(salle[i].rangées[j].sièges[k].réservé == 0){
                    
                    printf("0 ");
                }else{
                    printf("X ");
                }
            }
            printf("\n");
        }  
    }

}

void modeFestivalier(){
    
    printf("||MODE FESTIVALIER||\n");

    // Affiche les salles ayant un concert prévu et ceux actuellement en concert
    // Peut réserver un ou plusieurs sièges
    // Affiche le plan de la salle que l'utilisateur souhaite réserver (donner une légende)

}

int main(){
    
    FILE *fichier; 
    int input = 99;

    printf("-------------\n");
    printf("|| CY-FEST ||\n");
    printf("-------------\n");
    
    // Mettre de la couleur (couleur du texte; couleur du fond)
    couleur("5;41");
    printf("texte");
    couleur("0");
    
    /*
    // affiche tout dans le fichier texte jusqu'à ce qui n'y ai plus rien 
    char ligne[1000]; 
    fichier = fopen("exemple.txt", "r");
    
    while (fgets(ligne, sizeof(ligne), fichier) != '\0') {
        printf("%s", ligne);
    }
    
    // écris dans le fichier texte
    fichier = fopen("exemple.txt", "r");
    fprintf(fichier, "Je peux écrire dans le fichier comme ca !\n");
    
    fclose(fichier);
    */
    
    printf("Commandes utiles : MODE MANAGER = 1 ; MODE FESTIVALIER = 2; QUITTER = 0;\n");
    scanf("%d", &input);
    
    while(input < 0 || input > 2)
    {
        printf("Cette commande n'existe pas !!\n");
        scanf("%d", &input);
    }
    
    switch(input){
        
        case 1:
            modeManager();
            break;
        case 2:
            modeFestivalier();
            break;
        case 0:
            printf("Au revoir !");
            break;
    }
 
    // Ouverture du fichier en mode écriture
    //fichier = fopen("exemple.txt", "w");
    //fprintf(fichier, "Bonjour, monde !\n");
    
    return 0;
}
