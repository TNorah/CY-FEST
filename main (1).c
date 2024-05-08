#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define couleur(param) printf("\033[%sm",param)
#define MAX 20

#define FICHIER_SALLES "salles.txt"
#define FICHIER_CONCERTS "concerts.txt"

typedef struct{
    
    int réservé;
    char catégorie;
    
}Siège;

typedef struct{
    
    int nbSièges;
    Siège *sièges;
    
}Rangée;

typedef struct{
    int heure;
    int min;
}Heure;

typedef struct{
    
    Heure heure;
    int jour;
    int mois;
    int année;
    
}Date;

typedef struct{
    
    char nom[MAX];
    char artiste[MAX];
    Date dateDebut;
    Date dateFin; // déterminer par l'utilisateur
    int fosse; // déterminer par l'utilisateur
    
}Concert;

typedef struct{
    
    char nom[MAX];
    int nbRangées;
    int actif;
    Rangée *rangées;
    Concert concert;
    
}Salle;

void ecrireSalle(Salle *tab, int N){
    
    FILE* fichier = fopen(FICHIER_SALLES,"w");
    
    if(fichier == NULL){
        printf("ERREUR LORS DE L'OUVERTURE DU FICHIER POUR ECRIRE\n");
        exit(5);
    }
    
    for(int i=0; i<N; i++){
        fprintf(fichier,"Nom : %s, nbRangées : %d, Actif : %d, \n",tab[i].nom,tab[i].nbRangées,tab[i].actif);
    }
}
/*
void lireSalle(int *nbF){

    FILE* fichier = fopen(FICHIER_SALLES,"r");
    
    if(fichier == NULL){
        printf("ERREUR LORS DE L'OUVERTURE DU FICHIER POUR LECTURE\n");
        exit(6);
    }
    
    *nbF = 0;
    char c;
    
    while((c = fgets(fichier)) != EOF){
        if(c == '\n'){
            nbF++;
        }
    }
    rewind(fichier);
    
    for(int i=0; i<*nbF; i++){
        //fscanf(fichier, "Nom : %s, nbRangées : %d, Actif : %d\n", tab[i].nom, tab[i].prenom, &tab[i].age);
    }
}
*/
int rechercheSalle(Salle *salle, char *Nom, int nbTotal){ 
    
    // recherche dans le tableau de salles si une salle existe
    // Si c'est le cas, il renvoie son indice dans le tableau
    
    for(int i=0; i<nbTotal; i++){
        
        if(strcmp(Nom, salle[i].nom) == 0){
            
            printf("La salle %s existe !\n",salle[i].nom);
            return i; // donne l'indice de la salle
        }
    }
    printf("Cette salle n'existe pas !\n");
    return -1;
}

void afficheSalle(Salle *salle, int nb){
    
    // Appelle une fonction pour rechercher une salle
    
    char test[MAX];
    
    printf("Donnez le nom de la salle que vous recherchez :\n");
    scanf("%s",test);
    
    int indice = rechercheSalle(salle, test, nb);
    
    // en fonction de la salle à afficher
    
    printf("Numéro de la salle %s est %d\n",salle[indice].nom,indice+1);
        
    for(int j=0; j<(salle[indice].nbRangées); j++){
            
        for(int k=0; k<(salle[indice].rangées[j].nbSièges); k++){
                
            if(salle[indice].rangées[j].sièges[k].réservé == 0){
                    
                printf("0 ");
            }else{
                
                printf("X ");
            }
        }
        printf("\n");
    }
}

Salle* créerSalle(int nB){
    
    int rA, rB; 
    int rC;
    
    Salle *tab = NULL;
    
    tab = malloc(nB * sizeof(Salle));
    
    if(tab == NULL)
    {
        exit(1);
    }
    
    for(int i=0; i<nB; i++){ // Crée une salle
    
        printf("Nom de la salle n°%d ?\n", i+1);
        scanf("%s",tab[i].nom);
        
        printf("Combien de rangees ?\n");
        scanf("%d",&tab[i].nbRangées);
        
        tab[i].rangées = malloc(tab[i].nbRangées * sizeof(*tab[i].rangées));
        
        if(tab[i].rangées == NULL)
        {
            exit(2);
        }
        
        // demande les rangées en catégorie A et B pour trouver ceux de la C
        printf("Combien de rangées pour la catégorie A ?\n");
        scanf("%d",&rA);
        
        printf("Combien de rangées pour la catégorie B ?\n");
        scanf("%d",&rB);
        
        rC = tab[i].nbRangées - (rA + rB);
        
        // Aussi, vérifier si la demande est correcte
        if(rC < 0){
            printf("WRONG INPUT!\n");
            exit(3);
        }
        
        for(int j=0; j<(tab[i].nbRangées); j++){ // Crée les rangées de sièges
            
            printf("Combien de sièges pour la rangee n°%d ?\n", j+1);
            scanf("%d",&tab[i].rangées[j].nbSièges);
            
            tab[i].rangées[j].sièges = malloc(tab[i].rangées[j].nbSièges * sizeof(*tab[i].rangées[j].sièges));
            
            if(tab[i].rangées[j].sièges == NULL)
            {
                exit(4);   
            }
            
            char c; // donne la catégorie de chaque rangée
            if(rA > j){
                c = 'A';
            }else if((rA+rB) > j){
                c = 'B';
            }else if(tab[i].nbRangées > j){
                c = 'C';
            }
            
            for(int k=0; k<(tab[i].rangées[j].nbSièges); k++){ // Initialise les sièges et définie une catégorie
                tab[i].rangées[j].sièges[k].catégorie = c;
                tab[i].rangées[j].sièges[k].réservé = 0;  
            }
        }
    }
    
    ecrireSalle(tab, nB);

    printf("||Creation de salle(s) terminée||\n");
    
    return tab;
}

// (tableau de salles de base, la taille du tab de base, nouvelle taille de tab à récupérer)
Salle* ajouterSalle(Salle *tab, int N_tab, int *T_p){ 
    
    Salle *tab1 = NULL; // nouveau tableau où vont être mis les salles du premier tableau et les nouvelles salles
    int N_tabAjouter; 
    
    int rA, rB;
    int rC;
    
    //ajoute une ou plusieurs salles lorsque le tableau est non vide

    printf("Combien de salles à ajouter ?\n");
    scanf("%d",&N_tabAjouter);
    
    int total = (N_tab+N_tabAjouter);
    
    tab1 = realloc(tab, total * sizeof(Salle));
    
    if(tab1 == NULL){
        printf("Oups!\n");
        exit(2);
    }
    
    for(int i=N_tab; i<total; i++){
        
        printf("Nom de la salle n°%d ?\n", i+1);
        scanf("%s",tab1[i].nom);
        
        printf("Combien de rangees ?\n");
        scanf("%d",&tab1[i].nbRangées);
        
        tab1[i].rangées = malloc(tab1[i].nbRangées * sizeof(*tab1[i].rangées));
        
        if(tab1[i].rangées == NULL)
        {
            exit(2);
        }
        
        printf("Combien de rangées pour la catégorie A ?\n");
        scanf("%d",&rA);
        
        printf("Combien de rangées pour la catégorie B ?\n");
        scanf("%d",&rB);
        
        rC = tab1[i].nbRangées - (rA + rB);
        
        if(rC < 0){
            printf("WRONG INPUT!\n");
            exit(3);
        }
        
        for(int j=0; j<(tab1[i].nbRangées); j++){ // Crée les rangées de sièges
            
            printf("Combien de sièges pour la rangee n°%d ?\n", j+1);
            scanf("%d",&tab1[i].rangées[j].nbSièges);
            
            tab1[i].rangées[j].sièges = malloc(tab1[i].rangées[j].nbSièges * sizeof(*tab1[i].rangées[j].sièges));
            
            if(tab1[i].rangées[j].sièges == NULL)
            {
                exit(4);   
            }
            
            char c; // donne la catégorie de chaque rangée
            if(rA > j){
                c = 'A';
            }else if((rA+rB) > j){
                c = 'B';
            }else if(tab[i].nbRangées > j){
                c = 'C';
            }
            
            for(int k=0; k<(tab1[i].rangées[j].nbSièges); k++){ // Initialise les sièges et définie une catégorie
                tab1[i].rangées[j].sièges[k].catégorie = c;
                tab1[i].rangées[j].sièges[k].réservé = 0; // NON RESERVE 
            }
        }
    }
    
    *T_p = total;
    printf("Fini!\n");
    return tab1;
    
}

Salle* modifierSalle(Salle *tab, int N){
    
    int indice;
    
    int rA, rB;
    int rC;
    
    // affiche nom des salles
    for(int i=0; i<N; i++){
        printf("Salle n°%d : %s\n",i+1,tab[i].nom);
    }
    
    // récupérer le nom pour vérifier et prendre l'indice de la salle
    char text[MAX];
    printf("Quelle salle voulez-vous modifier ?\n");
    scanf("%s",text);
    
    indice = rechercheSalle(tab, text, N);
    
    //modifie la salle

    printf("Nom de la salle n°%d à modifier ?\n", indice+1);
    scanf("%s",tab[indice].nom);
        
    printf("Combien de rangees ?\n");
    scanf("%d",&tab[indice].nbRangées);
        
    tab[indice].rangées = malloc(tab[indice].nbRangées * sizeof(*tab[indice].rangées));
        
    if(tab[indice].rangées == NULL)
    {
        exit(2);
    }
        
    printf("Combien de rangées pour la catégorie A ?\n");
    scanf("%d",&rA);
        
    printf("Combien de rangées pour la catégorie B ?\n");
    scanf("%d",&rB);
        
    rC = tab[indice].nbRangées - (rA + rB);
        
    if(rC < 0){
        printf("WRONG INPUT!\n");
        exit(3);
    }
        
    for(int j=0; j<(tab[indice].nbRangées); j++){ // Crée les rangées de sièges
            
        printf("Combien de sièges pour la rangee n°%d ?\n", j+1);
        scanf("%d",&tab[indice].rangées[j].nbSièges);
            
        tab[indice].rangées[j].sièges = malloc(tab[indice].rangées[j].nbSièges * sizeof(*tab[indice].rangées[j].sièges));
            
        if(tab[indice].rangées[j].sièges == NULL)
        {
            exit(4);   
        }
            
        char c; // donne la catégorie de chaque rangée
        if(rA > j){
            c = 'A';
        }else if((rA+rB) > j){
            c = 'B';
        }else if(tab[indice].nbRangées > j){
            c = 'C';
        }
            
        for(int k=0; k<(tab[indice].rangées[j].nbSièges); k++){ // Initialise les sièges et définie une catégorie
            tab[indice].rangées[j].sièges[k].catégorie = c;
            tab[indice].rangées[j].sièges[k].réservé = 0; // NON RESERVE 
        }
    }
    
    printf("|| Modification de la salle fini ! ||\n\n");
    
    return tab;
}

Salle* modeManager(int *nb){
    
    // Doit créer une ou plusieurs salles (X)
    // choisit le nombre de sièges et nombre de rangées par catégorie (A et B) (X)
    // => le reste des sièges sont en catégorie C (X)
    // Choisit si un concert a une fosse (pas catégorie A) ou non 
    // Choisit le prix d'une catégorie
    // Choisit la date et l'heure de fin d'un concert
    // Si un concert est terminé, il peut remodifier une salle
    // Il peut consulter l'état une salle (en concert, concert terminé, etc.)
    
    Salle *salle = NULL;
    int nB;
    int choix;
    
    printf("||MODE MANAGER||\n\n");
    
    do{
        printf("Que voulez-vous faire ?\n\n");
        printf("1- Créer une ou plusieurs salles \n");
        printf("2- Modifier une salle \n");
        printf("3- Attribuer une salle à un concert \n");
        printf("4- Quitter\n");
        
        scanf("%d",&choix);
        
        switch(choix){
            case 1:
                
                if(salle == NULL){
                    
                    printf("Combien de salles ?\n");
                    scanf("%d",&nB);
                
                    *nb = nB;
                    
                    printf("Salle vide !\n");
                    salle = créerSalle(*nb);
                }else{
                    printf("Salle non vide !\n");
                    salle = ajouterSalle(salle,nB,nb);
                    printf("nb = %d\n",*nb);
                }
                
                break;
            
            case 2:
                salle = modifierSalle(salle, *nb);
                afficheSalle(salle, *nb);
                
            case 4:
                printf("bye bye !\n");
                
            default :
                printf("Mauvaise commande !\n");
                break;
        }
    }while(choix != 4);
    
    return salle;
}

void modeFestivalier(){
    
    printf("||MODE FESTIVALIER||\n");

    // Affiche les salles ayant un concert prévu et ceux actuellement en concert
    // Peut réserver un ou plusieurs sièges
    // Affiche le plan de la salle que l'utilisateur souhaite réserver (donner une légende)

    printf("\n||Légende||\n");
    printf("   0   : siège libre\n");
    printf("   X   : siège occupé\n");
    printf("  Vert : catégorie A\n");
    printf(" Orange : catégorie B\n");
    printf(" Marron : catégorie C\n");
    
}

int main(){
    
    FILE *fichier;
    Salle *salles;
    
    int choix = 99;
    int nbSalles;

    printf("-------------\n");
    printf("|| CY-FEST ||\n");
    printf("-------------\n");
    
    do{
        
        printf("\n--MENU--\n");
        
        printf("\nMODE MANAGER = 1\nMODE FESTIVALIER = 2\nQUITTER = 3\nRETOUR AU MENU = 4\n\n");
        scanf("%d", &choix);
        
        switch(choix){
        
            case 1:
                salles = modeManager(&nbSalles);
                afficheSalle(salles,nbSalles);
                
                printf("nbSalles = %d\n",nbSalles);
                
                break;
            case 2:
                modeFestivalier();
                break;
            case 3:
                printf("|| Fin du programme ||\n");
                exit(3);
                break;
            case 4:
                printf("|| Retour au menu ||\n");
                break;
            default :
                printf("Cette commande n'existe pas ! Recommencez\n\n");
        }
        
    }while(choix != 3);  
 
    return 0;
}

