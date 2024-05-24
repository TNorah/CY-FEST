#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define couleur(param) printf("\033[%sm",param)
#define MAX 30

#define FICHIER_SALLES "salles.txt"
#define FICHIER_CONCERTS "concerts.txt"


typedef struct{
    
    int réservé;
    int capacité;
    int prix;
    char catégorie;

}Siège;

typedef struct{
    
    int nbSièges;
    Siège *sièges;
    
}Rangée;

typedef struct{
    
    int heure;
    int min;
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
    int état;
    
}Concert;

typedef struct{
    
    char nom[MAX];
    int nbRangées;
    int état; //initialiser à zero
    Rangée *rangées;
    Concert concert; //initialiser à zero
    
}Salle;

void vide_buffer();
int scanfD(int nbRecup);
void scanfS(char *texte);
long conversionDateSecondesD(Concert *concert, int indice);
long conversionDateSecondesF(Concert *concert, int indice);
int testSiFichierVide(FILE *fichier);
void ecrireSalle(Salle *tabS, int Nbs);
void ecrireConcert(Concert *tabC, int Nbc);
Concert *lireConcert(int *nbC, int affiche);
Salle *lireSalle(int *nbS, int affiche);
int rechercheSalle(Salle *salle, char *Nom, int nbTotal);
int rechercheConcert(Concert *concert, char *Nom, int nbTotal);
void afficheSalle(Salle *salle, int nb);
Salle* créerSalle(int *nb);
Salle* ajouterSalle(Salle *tab, int N_tab, int *T_p);
Salle* modifierSalle(Salle *tab, Concert *c, int N, int nC);
Salle *attribuerConcert(Salle *salles, int nbs, Concert *concerts, int nbc);
Concert *modifierConcert(Concert *concert, int nbC);
Salle* modeManager(Salle *salle, Concert *concert, int *nbS, int *nbC);
Salle* réserverSalle(Salle *salle, int indiceS, int nbSalles);
Salle* modeFestivalier(Salle *salle, Concert *concert, int *nbS, int *nbC);
