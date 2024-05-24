#include "main2.h"

void vide_buffer(){
	while(getchar()!= '\n'){
	}
}

int scanfD(int nbRecup){ // fonction qui récupère les nombres entiers en vérifiant les conditions
    
    int value;
    int verif;
    
    do{   
        verif = scanf("%d", &value);
        vide_buffer(); 
        if (verif != nbRecup || value < 0){
            printf("Saisie incorrecte !\n");
        }
    }while (verif != nbRecup || value < 0);
    
    return value;
}

void scanfS(char *texte){ // fonction qui récupère les chaines de caractères sans débordement
    
    if (texte == NULL) {
        printf("ERREUR : pointeur vide !!\n");
        exit(EXIT_FAILURE);
    }
    
    if(strlen(texte) >= MAX){
        printf("ERREUR : debordement !!\n");
        exit(EXIT_FAILURE);
    }
}

long conversionDateSecondesD(Concert *concert, int indice){ // fonction qui convertie la date du début de concert en secondes système

    struct tm tmp;
    
    if(concert == NULL){
        exit(EXIT_FAILURE);
    }
    
    tmp.tm_sec   = 0;
    tmp.tm_min   = concert[indice].dateDebut.min;
    tmp.tm_hour  = concert[indice].dateDebut.heure;
    tmp.tm_mday  = concert[indice].dateDebut.jour;
    tmp.tm_mon   = (concert[indice].dateDebut.mois)-1;
    tmp.tm_year  = (concert[indice].dateDebut.année)-1900;
	
    long debutC = mktime(&tmp);
    
    printf("d = %ld\n", debutC);
    
    return debutC;
}

long conversionDateSecondesF(Concert *concert, int indice){ // fonction qui convertie la date de fin de concert en secondes système

    struct tm tmp;
    
    if(concert == NULL){
        exit(EXIT_FAILURE);
    }
    
    tmp.tm_sec   = 0;
    tmp.tm_min   = concert[indice].dateFin.min;
    tmp.tm_hour  = concert[indice].dateFin.heure;
    tmp.tm_mday  = concert[indice].dateFin.jour;
    tmp.tm_mon   = (concert[indice].dateFin.mois)-1;
    tmp.tm_year  = (concert[indice].dateFin.année)-1900;
	
    long FinC = mktime(&tmp);
    
    printf("f = %ld\n", FinC);
    
    return FinC;
}

int testSiFichierVide(FILE *fichier){ // vérifie si le fichier ouvert est vide ou non
    int caracterePremier = 0;
 
    caracterePremier = fgetc(fichier); //On lit le prmeier caractère du fichier
    if(caracterePremier == EOF)
    {
        return 1; //le fichier est vide donc on retourne 1
    }
    rewind(fichier);
    
    return 0; //le fichier n'est pas vide donc on retourne 0
}

void ecrireSalle(Salle *tabS, int Nbs){ // sauvegarde les informations des salles dans le fichier salles.txt
    
    FILE* fichier = fopen(FICHIER_SALLES,"w");
    
    if(fichier == NULL){
        printf("ERREUR LORS DE L'OUVERTURE DU FICHIER POUR ECRIRE\n");
        exit(5);
    }
    
    for(int i=0; i<Nbs; i++){
        fprintf(fichier,"%s %d %d %s ",tabS[i].nom,tabS[i].nbRangées,tabS[i].état,tabS[i].concert.nom);
        
        for(int j = 0; j<tabS[i].nbRangées; j++){
        fprintf(fichier, "|%d| ", tabS[i].rangées[j].nbSièges);
        
            for(int k = 0; k<tabS[i].rangées[j].nbSièges; k++){
                fprintf(fichier, "|%d %c %d| ", tabS[i].rangées[j].sièges[k].réservé, tabS[i].rangées[j].sièges[k].catégorie, tabS[i].rangées[j].sièges[k].prix);
            }
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}

void ecrireConcert(Concert *tabC, int Nbc){ // sauvegarde les informations des concerts dans le fichier concerts.txt
    
    FILE* fichier = fopen(FICHIER_CONCERTS,"w");
    
    if(fichier == NULL){
        printf("ERREUR LORS DE L'OUVERTURE DU FICHIER POUR ECRIRE\n");
        exit(5);
    }
    
    for(int i=0; i<Nbc; i++){
        fprintf(fichier,"%s %s %dh%d |%d/%d/%d| %dh%d |%d/%d/%d| %d %d\n",tabC[i].nom,tabC[i].artiste,
        tabC[i].dateDebut.heure,tabC[i].dateDebut.min,tabC[i].dateDebut.jour,tabC[i].dateDebut.mois,
        tabC[i].dateDebut.année,tabC[i].dateFin.heure,tabC[i].dateFin.min,tabC[i].dateFin.jour,
        tabC[i].dateFin.mois,tabC[i].dateFin.année,tabC[i].fosse, tabC[i].état);
    }
    
    fclose(fichier);
}

Concert *lireConcert(int *nbC, int affiche){ // lire et récupère les informations des concerts pour les utiliser

    FILE *fichier = fopen(FICHIER_CONCERTS,"r");
    
    if(fichier == NULL){
        printf("Erreur d'ouverture en mode lecture!\n");
        fclose(fichier);
        exit(99);
    }
    
    if(testSiFichierVide(fichier) == 1){
        printf("Fichier concert vide !\n");
        fclose(fichier);
        return NULL;
    }
    
    *nbC = 0;
    char c;
    
    while((c = fgetc(fichier)) != EOF){
        if(c == '\n'){
            (*nbC)++;
        }
    }
    rewind(fichier);
    
    Concert *concert = malloc((*nbC) * sizeof(Concert));
    
    if(concert == NULL){
        printf("Probleme d'allocation -- LireConcert --\n");
        exit(9);
    }
    
    for(int i=0; i<*nbC; i++){
        fscanf(fichier,"%s %s %dh%d |%d/%d/%d| %dh%d |%d/%d/%d| %d %d\n",concert[i].nom,concert[i].artiste,
        &concert[i].dateDebut.heure,&concert[i].dateDebut.min,&concert[i].dateDebut.jour,&concert[i].dateDebut.mois,
        &concert[i].dateDebut.année,&concert[i].dateFin.heure,&concert[i].dateFin.min,&concert[i].dateFin.jour,
        &concert[i].dateFin.mois,&concert[i].dateFin.année,&concert[i].fosse,&concert[i].état);
    }
    
    if (affiche == 1){
        for (int i = 0; i < *nbC; i++){
            printf("Nom : %s, Artiste : %s, Debut : %dh%d |%d/%d/%d|, Fin : %dh%d |%d/%d/%d| fosse : %d, etat = %d\n",
            concert[i].nom, concert[i].artiste, concert[i].dateDebut.heure, concert[i].dateDebut.min, concert[i].dateDebut.jour,
            concert[i].dateDebut.mois, concert[i].dateDebut.année, concert[i].dateFin.heure, concert[i].dateFin.min,
            concert[i].dateFin.jour, concert[i].dateFin.mois, concert[i].dateFin.année, concert[i].fosse, concert[i].état);
        }
    }
    
    fclose(fichier);
    return concert;
}

Salle *lireSalle(int *nbS, int affiche){ // lire et récupère les informations des salles de concerts pour les utiliser

    FILE *fichier = fopen(FICHIER_SALLES,"r");
    
    if(fichier == NULL){
        printf("Erreur d'ouverture en mode lecture!\n");
        exit(99);
    }
    
    if(testSiFichierVide(fichier) == 1){
        fclose(fichier);
        return NULL;
    }
    
    *nbS = 0;
    char c;
    
    while((c = fgetc(fichier)) != EOF){
        if(c == '\n'){
            (*nbS)++;
        }
    }
    rewind(fichier);
    
    //printf("nbS = %d\n",*nbS);
    
    Salle *salle = malloc((*nbS) * sizeof(Salle));
    
    if(salle == NULL){
        printf("Probleme d'allocation -- LireSalle --\n");
        exit(9);
    }
    
    for(int i=0; i<*nbS; i++){
        fscanf(fichier,"%s %d %d %s ",salle[i].nom,&salle[i].nbRangées,&salle[i].état,salle[i].concert.nom);
        //printf("%s %d %d %s ",salle[i].nom,salle[i].nbRangées,salle[i].état,salle[i].concert.nom);
        
        salle[i].rangées = malloc(salle[i].nbRangées * sizeof(Rangée));
        
        for (int j=0; j<salle[i].nbRangées; j++){
            fscanf(fichier, "|%d| ",&salle[i].rangées[j].nbSièges);
            //printf("|%d| ",salle[i].rangées[j].nbSièges);
            
            salle[i].rangées[j].sièges = malloc(salle[i].rangées[j].nbSièges * sizeof(Siège));
            
            for (int k=0; k<salle[i].rangées[j].nbSièges; k++){
                fscanf(fichier, "|%d %c %d| ",&salle[i].rangées[j].sièges[k].réservé,&salle[i].rangées[j].sièges[k].catégorie, &salle[i].rangées[j].sièges[k].prix);
                //printf("|%d %c| ",salle[i].rangées[j].sièges[k].réservé,salle[i].rangées[j].sièges[k].catégorie);
                
            }
        }
        printf("\n");
    }
    
    if(affiche == 1){
        for (int i = 0; i < *nbS; i++){
            printf("Nom : %s, nbRangees : %d, Etat : %d, Concert : %s\n", salle[i].nom, salle[i].nbRangées, salle[i].état, salle[i].concert.nom);
        }
    }
    
    fclose(fichier);
    return salle;
}

int rechercheSalle(Salle *salle, char *Nom, int nbTotal){ // recherche dans le tableau de salles si une salle existe, si c'est le cas, il renvoie son indice dans le tableau

    if(salle == NULL){
        printf("Il n'y a pas de salle --rechercheSalle-- \n");
        return -1;
    }
    
    if(Nom == NULL){
        printf("ERREUR : pointeur Nom ne pointe sur rien --rechercheSalle-- \n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<nbTotal; i++){
        
        if(strcmp(Nom, salle[i].nom) == 0){
            
            printf("La salle %s existe !\n",salle[i].nom);
            return i; // donne l'indice de la salle
        }
    }
    printf("Cette salle n'existe pas !\n");
    return -2;
}

int rechercheConcert(Concert *concert, char *Nom, int nbTotal){ // recherche dans le tableau de concerts si un concert existe, si c'est le cas, il renvoie son indice dans le tableau
    
    if(concert == NULL){
        printf("La concert est vide ! --rechercheConcert-- \n");
        return -1;
    }
    
    if(Nom == NULL){
        printf("ERREUR : pointeur Nom ne pointe sur rien --rechercheSalle-- \n");
        exit(EXIT_FAILURE);
    }
    
    for(int i=0; i<nbTotal; i++){
        
        if(strcmp(Nom, concert[i].nom) == 0){
            printf("La concert %s existe !\n",concert[i].nom);
            return i; // donne l'indice de la concert
        }
    }
    printf("Ce concert n'existe pas !\n");
    return -2;
}

void afficheSalle(Salle *salle, int nb){ // affiche une ou plusieurs salles en fonction du choix utilisateur
    
    char texte[MAX];
    int choix;
    int verif;
    int prixA, prixB, prixC;
    
    if(salle == NULL){
        printf("ERREUR : Il n'y a pas de salles\n");
        return;
    }
    
    printf("\n|| Affichage de salles||\n");

    salle = lireSalle(&nb, 1);
    
    do{
        printf("Voulez-vous afficher une seule salle ou toutes les salles ?\n 1- Une seule\n 2- Plusieurs\n");
        verif = scanf("%d",&choix);
        vide_buffer();
        
    }while(choix < 1 || choix > 2 || verif != 1);
    
    if(choix == 1){
        
        printf("||CHOIX 1||\n\n");
        do{
            printf("Donnez le nom de la salle que vous recherchez :\n");
            verif = scanf("%s",texte);
            vide_buffer();
            
        }while(verif != 1);
        scanfS(texte);
    
        // Appelle une fonction pour rechercher une salle
        int indice = rechercheSalle(salle, texte, nb);
        
        if(indice < 0){
            return;
        }
    
        // en fonction de la salle à afficher
        printf("Numero de la salle %s est %d\n",salle[indice].nom,indice+1);
        
        printf("-- %s --\n\n",salle[indice].nom);
        
        for(int j=0; j<(salle[indice].nbRangées); j++){
            printf("R%d ",j+1);
            
            for(int k=0; k<(salle[indice].rangées[j].nbSièges); k++){
                
                if(salle[indice].rangées[j].sièges[k].réservé == 0){
                    
                    if (salle[indice].rangées[j].sièges[k].catégorie == 'A') {

                        prixA = salle[indice].rangées[j].sièges[k].prix;
                        couleur("32");
                        printf("O ");
                        couleur("0");
                    }
                    else if (salle[indice].rangées[j].sièges[k].catégorie == 'B') {

                        prixB = salle[indice].rangées[j].sièges[k].prix;
                        couleur("33");
                        printf("O ");
                        couleur("0");
                    }
                    else if (salle[indice].rangées[j].sièges[k].catégorie == 'C') {

                        prixC = salle[indice].rangées[j].sièges[k].prix;
                        couleur("35");
                        printf("O ");
                        couleur("0");
                    }

                }
                else {
                    couleur("31");
                    printf("X ");
                    couleur("0");
                }
            }
            printf("\n");
        }
        printf("\n--Legende--\n0   : siege libre\nX   : siege occupé\nVert : categorie A -> %d\nOrange : categorie B -> %d\nViolet : categorie C -> %d\n", prixA, prixB, prixC);
        return;
    }else{
        
        printf("||CHOIX 2||\n\n");
        
        for(int i=0; i<nb; i++){
            printf("-- %s --\n\n",salle[i].nom);
            
            for(int j=0; j<(salle[i].nbRangées); j++){
                printf("R%d ",j+1);
                
                for(int k=0; k<(salle[i].rangées[j].nbSièges); k++){
                
                    if(salle[i].rangées[j].sièges[k].réservé == 0){
                    
                        if (salle[i].rangées[j].sièges[k].catégorie == 'A') {

                            prixA = salle[i].rangées[j].sièges[k].prix;
                            couleur("32");
                            printf("O ");
                            couleur("0");
                        }
                        else if (salle[i].rangées[j].sièges[k].catégorie == 'B') {

                            prixB = salle[i].rangées[j].sièges[k].prix;
                            couleur("33");
                            printf("O ");
                            couleur("0");
                        }
                        else if (salle[i].rangées[j].sièges[k].catégorie == 'C') {

                            prixC = salle[i].rangées[j].sièges[k].prix;
                            couleur("35");
                            printf("O ");
                            couleur("0");
                        }

                    }else{
                        couleur("31");
                        printf("X ");
                        couleur("0");
                    }
   
                }
                printf("\n");
            }
            printf("\n");
            printf("\n--Legende--\n0   : siege libre\nX   : siege occupé\nVert : categorie A -> %d\nOrange : categorie B -> %d\nViolet : categorie C -> %d\n", prixA, prixB, prixC);
        }
        return;
    }
}

Salle* créerSalle(int *nb){ // créer une salle de concert lorsque le tableau de salles est vide (première execution du programme)
    
    int rC, nB;
    int prixA, prixB, prixC;
    int rA, rB; 
    int verif;
    char c; 
    char InitialiseTexte[] = "Non";
    
    if(nb == NULL){
        printf("ERREUR : pointeur vide !\n");
        exit(EXIT_FAILURE);
    }
    
    Salle *tab = NULL;
    printf("Combien de salles ?\n");
    nB = scanfD(1);

    tab = malloc(nB * sizeof(Salle));
    
    if(tab == NULL){
        printf("ERREUR : echec de l'allocation !!\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i=0; i<nB; i++){ // Crée une salle
    
        do{
            printf("Nom de la salle n.%d ?\n", i+1);
            verif = scanf("%[^\n]s",tab[i].nom);
            vide_buffer();
            
        }while(verif != 1);
        scanfS(tab[i].nom);
        
        printf("Combien de rangees ?\n");
        tab[i].nbRangées = scanfD(1);
        
        if(tab[i].nbRangées == 0){
            printf("ERREUR : saisie incorrecte !\n");
            exit(EXIT_FAILURE);
        }
        
        strcpy(tab[i].concert.nom, InitialiseTexte);
        //printf("Contenu de tab nom : %s\n", tab[i].concert.nom); 
        strcpy(tab[i].concert.artiste, InitialiseTexte);
        //printf("Contenu de tab artiste : %s\n", tab[i].concert.artiste); 
        
        tab[i].concert.dateDebut.heure = 0;
        tab[i].concert.dateDebut.min = 0;
        tab[i].concert.dateDebut.jour = 0;
        tab[i].concert.dateDebut.mois = 0;
        tab[i].concert.dateDebut.année = 0;
        
        tab[i].concert.dateFin.heure = 0;
        tab[i].concert.dateFin.min = 0;
        tab[i].concert.dateFin.jour = 0;
        tab[i].concert.dateFin.mois = 0;
        tab[i].concert.dateFin.année = 0;
        
        tab[i].concert.fosse = 0;
        
        tab[i].rangées = malloc(tab[i].nbRangées * sizeof(*tab[i].rangées));
        
        if(tab[i].rangées == NULL)
        {
            printf("ERREUR : echec de l'allocation !!\n");
            free(tab);
            exit(EXIT_FAILURE);
        }
        
        printf("Combien de rangees pour la categorie A ?\n");
        rA = scanfD(1); // demande les rangées en catégorie A et B pour trouver ceux de la C

        printf("Combien de rangees pour la categorie B ?\n");
        rB = scanfD(1);
        
        rC = tab[i].nbRangées - (rA + rB);
        
        if(rC < 0){ // Aussi, vérifier si la demande est correcte
            printf("ERREUR : Mauvaise saisie des categories A et B !!\n");
            free(tab);
            exit(EXIT_FAILURE);
        }
        
        printf("Prix catégorie A ?\n");
        prixA = scanfD(1);

        printf("Prix catégorie B ?\n");
        prixB = scanfD(1);

        printf("Prix catégorie C ?\n");
        prixC = scanfD(1);
        
        for(int j=0; j<(tab[i].nbRangées); j++){ // Crée les rangées de sièges
            
            do{
                printf("Combien de sieges pour la rangee n°%d ?\n", j+1);
                verif = scanf("%d",&tab[i].rangées[j].nbSièges);
                vide_buffer();
                
            }while(tab[i].rangées[j].nbSièges <= 0 || verif != 1);
            
            tab[i].rangées[j].sièges = malloc(tab[i].rangées[j].nbSièges * sizeof(*tab[i].rangées[j].sièges));
            
            if(tab[i].rangées[j].sièges == NULL){
                printf("ERREUR : echec de l'allocation !!\n");
                free(tab);
                exit(EXIT_FAILURE);   
            }
            
            // donne la catégorie de chaque rangée
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
                
                if (tab[i].rangées[j].sièges[k].catégorie == 'A'){
                    tab[i].rangées[j].sièges[k].prix = prixA;
                }
                else if (tab[i].rangées[j].sièges[k].catégorie == 'B'){
                    tab[i].rangées[j].sièges[k].prix = prixB;
                }
                else if (tab[i].rangées[j].sièges[k].catégorie == 'C'){
                    tab[i].rangées[j].sièges[k].prix = prixC;
                }

            }
        }
    }
    ecrireSalle(tab, nB);
    *nb = nB;
    
    printf("||Creation de salle(s) terminee||\n");
    return tab;
}

// (tableau de salles de base, la taille du tab de base, nouvelle taille de tab à récupérer)
Salle* ajouterSalle(Salle *tab, int N_tab, int *T_p){ // ajoute des salles lorsqu'il y a déjà des salles de sauvegarder
    
    char InitialiseTexte[] = "Non";
    char c;
    int prixA, prixB, prixC;
    int NtabAjouter;
    int verif; 
    int rA, rB;
    int rC;
    
    //ajoute une ou plusieurs salles lorsque le tableau est non vide
    printf("Combien de salles a ajouter ?\n");
    NtabAjouter = scanfD(1);
    
    int total = (N_tab+NtabAjouter);
    
    tab = realloc(tab, total * sizeof(Salle));
    
    if(tab == NULL){
        printf("ERREUR : echec de l'allocation !!\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i=N_tab; i<total; i++){
        
        printf("Nom de la salle n.%d ?\n", i+1);
        do{
            verif = scanf("%[^\n]s",tab[i].nom);
            vide_buffer();
            
        }while(verif != 1);
        scanfS(tab[i].nom);
        
        printf("Combien de rangees ?\n");
        tab[i].nbRangées = scanfD(1);

        if(tab[i].nbRangées == 0){
            printf("ERREUR : saisie incorrecte ! \n");
            if (salle[i].rangées != NULL) {
                for (int i = 0; i < salle[i].nbRangées; i++) {
                    if (salle[i].rangées[i].sièges != NULL) {
                        free(salle[i].rangées[i].sièges);
                    }
                }
                free(salle[i].rangées);
            }
            exit(EXIT_FAILURE);
        }
        
        strcpy(tab[i].concert.nom, InitialiseTexte);
        //printf("Contenu de tab nom : %s\n", tab[i].concert.nom); 
        strcpy(tab[i].concert.artiste, InitialiseTexte);
        //printf("Contenu de tab artiste : %s\n", tab[i].concert.artiste); 
        
        tab[i].concert.dateDebut.heure = 0;
        tab[i].concert.dateDebut.min = 0;
        tab[i].concert.dateDebut.jour = 0;
        tab[i].concert.dateDebut.mois = 0;
        tab[i].concert.dateDebut.année = 0;
        
        tab[i].concert.dateFin.heure = 0;
        tab[i].concert.dateFin.min = 0;
        tab[i].concert.dateFin.jour = 0;
        tab[i].concert.dateFin.mois = 0;
        tab[i].concert.dateFin.année = 0;
        
        tab[i].concert.fosse = 0;
        
        tab[i].rangées = malloc(tab[i].nbRangées * sizeof(*tab[i].rangées));
        
        if(tab[i].rangées == NULL){
            printf("ERREUR : saisie incorrecte ! \n");
            if (salle[i].rangées != NULL) {
                for (int i = 0; i < salle[i].nbRangées; i++) {
                    if (salle[i].rangées[i].sièges != NULL) {
                        free(salle[i].rangées[i].sièges);
                    }
                }
                free(salle[i].rangées);
            }
            exit(EXIT_FAILURE);
        }
        
        printf("Combien de rangees pour la categorie A ?\n");
        rA = scanfD(1);
        printf("Combien de rangees pour la categorie B ?\n");
        rB = scanfD(1);
        
        rC = tab[i].nbRangées - (rA + rB);
        
        if(rC < 0){
            printf("ERREUR : mauvaise saisie des categories A et B !!\n");
            if (salle[i].rangées != NULL) {
                for (int i = 0; i < salle[i].nbRangées; i++) {
                    if (salle[i].rangées[i].sièges != NULL) {
                        free(salle[i].rangées[i].sièges);
                    }
                }
                free(salle[i].rangées);
            }
            exit(EXIT_FAILURE);
        }

        printf("Prix catégorie A ?\n");
        prixA = scanfD(1);

        printf("Prix catégorie B ?\n");
        prixB = scanfD(1);

        printf("Prix catégorie C ?\n");
        prixC = scanfD(1);
        
        for(int j=0; j<(tab[i].nbRangées); j++){ // Crée les rangées de sièges
            
            printf("Combien de sieges pour la rangee n°%d ?\n", j+1);
            tab[i].rangées[j].nbSièges = scanfD(1);

            tab[i].rangées[j].sièges = malloc(tab[i].rangées[j].nbSièges * sizeof(*tab[i].rangées[j].sièges));
            
            if (tab[i].rangées[j].sièges == NULL) {
                printf("ERREUR : echec de l'allocation !!\n");
                if (salle[i].rangées != NULL) {
                    for (int i = 0; i < salle[i].nbRangées; i++) {
                        if (salle[i].rangées[i].sièges != NULL) {
                            free(salle[i].rangées[i].sièges);
                        }
                    }
                    free(salle[i].rangées);
                }
                exit(EXIT_FAILURE); 
            }
            
            // donne la catégorie de chaque rangée
            if(rA > j){
                c = 'A';
            }else if((rA+rB) > j){
                c = 'B';
            }else if(tab[i].nbRangées > j){
                c = 'C';
            }
            
            for(int k=0; k<(tab[i].rangées[j].nbSièges); k++){ // Initialise les sièges et définie une catégorie
                tab[i].rangées[j].sièges[k].catégorie = c;
                tab[i].rangées[j].sièges[k].réservé = 0; // NON RESERVE 

                if (tab[i].rangées[j].sièges[k].catégorie == 'A') {
                    tab[i].rangées[j].sièges[k].prix = prixA;
                }
                else if (tab[i].rangées[j].sièges[k].catégorie == 'B') {
                    tab[i].rangées[j].sièges[k].prix = prixB;
                }
                else if (tab[i].rangées[j].sièges[k].catégorie == 'C') {
                    tab[i].rangées[j].sièges[k].prix = prixC;
                }
            }
        }
    }
    
    ecrireSalle(tab, total);
    printf("|| Ajout salle fini ||\n\n");
    
    *T_p = total;
    return tab;
}

Salle* modifierSalle(Salle *tab, Concert *c, int N, int nC) // modifie une salle en fonction du choix de l'utilisateur
    
    char textS[MAX];
    
    int prixA, prixB, prixC;
    int indiceS;
    int indiceC;
    int verif;
    //char textC[MAX];
    
    int rA, rB;
    int rC;
    
    if(tab == NULL){
        printf("pas de salles -- modifierSalle --\n");
        return NULL;
    }
    
    if(c == NULL){
        printf("pas de concerts -- modifierSalle --\n");
        return NULL;
    }
    
    // affiche nom des salles
    for(int i=0; i<N; i++){
        printf("Salle n.%d : %s\n",i+1,tab[i].nom);
    }
    
    // récupérer le nom pour vérifier et prendre l'indice de la salle
    
    printf("Quelle salle voulez-vous modifier ?\n");
    do {
        verif = scanf("%[^\n]s", textS);
        vide_buffer();

    } while (verif != 1);
    scanfS(textS);
    
    indiceS = rechercheSalle(tab, textS, N);
    
    if(indiceS < 0){
    	printf("ERREUR : cette salle n'existe pas donc rien a modifier !\n");
    	return tab;
    }

    if (strcmp(tab[indiceS].concert.nom, "Non") == 0){
        printf("Cette salle ne contient pas de concert, vous pouvez la modifier sans problème\n");
    }
    else {
        long current = time(NULL);

        indiceC = rechercheConcert(c, tab[indiceS].concert.nom, nC);
        long DebutC = conversionDateSecondesD(c, indiceC);
        long FinC = conversionDateSecondesF(c, indiceC);

        if (current > FinC) {
            printf("Tu peux modifier salle!\n");
        }
        else {
            printf("Tu peux pas modifier salle!\n");
            return tab;
        }
    }
    
    //modifie la salle
    printf("Nom de la salle n.%d a modifier ?\n", indiceS+1);
    do {
        verif = scanf("%[^\n]s", tab[indiceS].nom);
        vide_buffer();

    }while (verif != 1);
    scanfS(tab[indiceS].nom);
    
    if(strlen(tab[indiceS].nom) > MAX){
    	printf("ERREUR : trop de caracteres !\n"); 
    	exit(EXIT_FAILURE);
    }
        
    printf("Combien de rangees ?\n");
    tab[indiceS].nbRangées = scanfD(1); 
        
    tab[indiceS].rangées = malloc(tab[indiceS].nbRangées * sizeof(*tab[indiceS].rangées));
        
    if(tab[indiceS].rangées == NULL){
        exit(EXIT_FAILURE);
    }
        
    printf("Combien de rangees pour la categorie A ?\n");
    rA = scanfD(1);
    printf("Combien de rangees pour la categorie B ?\n");
    rB = scanfD(1);
        
    rC = tab[indiceS].nbRangées - (rA + rB);
        
    if(rC < 0){
        printf("Mauvaise entree!\n");
        exit(EXIT_FAILURE);
    }

    printf("Prix catégorie A ?\n");
    prixA = scanfD(1);

    printf("Prix catégorie B ?\n");
    prixB = scanfD(1);

    printf("Prix catégorie C ?\n");
    prixC = scanfD(1);
        
    for(int j=0; j<(tab[indiceS].nbRangées); j++){ // Crée les rangées de sièges
            
        printf("Combien de sieges pour la rangee n°%d ?\n", j+1);
        tab[indiceS].rangées[j].nbSièges = scanfD(1);
            
        tab[indiceS].rangées[j].sièges = malloc(tab[indiceS].rangées[j].nbSièges * sizeof(*tab[indiceS].rangées[j].sièges));
            
        if(tab[indiceS].rangées[j].sièges == NULL){
            exit(EXIT_FAILURE);  
        }
            
        char c; // donne la catégorie de chaque rangée
        if(rA > j){
            c = 'A';
        }else if((rA+rB) > j){
            c = 'B';
        }else if(tab[indiceS].nbRangées > j){
            c = 'C';
        }
            
        for(int k=0; k<(tab[indiceS].rangées[j].nbSièges); k++){ // Initialise les sièges et définie une catégorie
            
            tab[indiceS].rangées[j].sièges[k].catégorie = c;
            tab[indiceS].rangées[j].sièges[k].réservé = 0; // NON RESERVE 

            if (tab[indiceS].rangées[j].sièges[k].catégorie == 'A') {
                tab[indiceS].rangées[j].sièges[k].prix = prixA;
            }
            else if (tab[indiceS].rangées[j].sièges[k].catégorie == 'B') {
                tab[indiceS].rangées[j].sièges[k].prix = prixB;
            }
            else if (tab[indiceS].rangées[j].sièges[k].catégorie == 'C') {
                tab[indiceS].rangées[j].sièges[k].prix = prixC;
            }
        }
    }
    
    ecrireSalle(tab, N);
    printf("|| Modification de la salle fini ! ||\n\n");
    
    return tab;
}

Salle *attribuerConcert(Salle *salles, int nbs, Concert *concerts, int nbc){ // attribue une salle à un concert en fonction de la date de début et de fin d'un concert et de son état actuel, de meme pour une salle

	char s[MAX];
	char c[MAX];
    	int verif;
	
	salles = lireSalle(&nbs, 1);
	concerts = lireConcert(&nbc, 1);

    	if (salles == NULL || concerts == NULL) {
        	printf("ERREUR : il n'y a pas de salles et/ou de concerts !\n");
        	exit(EXIT_FAILURE);
    	}

	printf("quel salle attribue ?\n");
    	do{
        	verif = scanf("%[^\n]s", s);
        	vide_buffer();

    	}while(verif != 1);
    	scanfS(s);
	
	int indiceS = rechercheSalle(salles,s,nbs);
	
	if(indiceS < 0){
		printf("ERREUR : Cette salle n'existe pas --attribuerConcert--\n");
		return salles;
	}
	
	if(salles[indiceS].état == 1){
		printf("Cette salle est deja prise par un concert !\n");
		return salles;
	}
	
	printf("quel concert attribue ?\n");
    	do {
        	verif = scanf("%[^\n]s", c);
        	vide_buffer();

    	}while (verif != 1);
    	scanfS(c);
	
	int indiceC = rechercheConcert(concerts,c,nbc);
	
	if(indiceC < 0){
		printf("ERREUR : Ce concert n'existe pas --attribuerConcert--\n");
		return salles;
	}
	
	if(concerts[indiceC].état == 1){
		printf("Cet concert est deja prise !\n");
		return salles;
	}
	
	printf("%s\n",concerts[indiceC].nom);
	printf("%s\n",concerts[indiceC].artiste);
	printf("%d\n",concerts[indiceC].fosse);
	
	strcpy(salles[indiceS].concert.nom, concerts[indiceC].nom);
	strcpy(salles[indiceS].concert.artiste, concerts[indiceC].artiste);
	salles[indiceS].concert.fosse = concerts[indiceC].fosse;
	
	salles[indiceS].état = 1;
	concerts[indiceC].état = 1;
	
	salles[indiceS].concert.dateDebut.heure = concerts[indiceC].dateDebut.heure;
	salles[indiceS].concert.dateDebut.min = concerts[indiceC].dateDebut.min;
	salles[indiceS].concert.dateDebut.jour = concerts[indiceC].dateDebut.jour;
	salles[indiceS].concert.dateDebut.mois = concerts[indiceC].dateDebut.mois;
	salles[indiceS].concert.dateDebut.année = concerts[indiceC].dateDebut.année;
	
	salles[indiceS].concert.dateFin.heure = concerts[indiceC].dateFin.heure;
	salles[indiceS].concert.dateFin.min = concerts[indiceC].dateFin.min;
	salles[indiceS].concert.dateFin.jour = concerts[indiceC].dateFin.jour;
	salles[indiceS].concert.dateFin.mois = concerts[indiceC].dateFin.mois;
	salles[indiceS].concert.dateFin.année = concerts[indiceC].dateFin.année;
	
	ecrireSalle(salles,nbs);
	ecrireConcert(concerts,nbc);
	
	printf("nom : %s",salles[indiceS].concert.nom);
	printf("artiste = %s\n",salles[indiceS].concert.artiste);
	printf("fosse = %d\n",salles[indiceS].concert.fosse);
	
	return salles;
}

Concert *modifierConcert(Concert *concert, int nbC){ // modifie les dates d'un concert, s'il possède une fosse ou pas et vérifie l'état du concert 
    
    char text[MAX];
    int input = 99;
    int verif;
    
    printf("|| Modification Concert ||\n");
    
    // Partie Date
    if(concert == NULL){
    	printf("ERREUR : Concert vide !\n");
    	return NULL; 
    }

    //concert = lireConcert(nbC, 1);
    for (int i = 0; i < nbC; i++){
        printf("Concert n.%d : Nom : %s, Artiste : %s, Date Debut : %dh%d %d/%d/%d, Date Fin : %dh%d %d/%d/%d\n",i+1,concert[i].nom, concert[i].artiste,
        concert[i].dateDebut.heure, concert[i].dateDebut.min, concert[i].dateDebut.jour, concert[i].dateDebut.mois, concert[i].dateDebut.année,
        concert[i].dateFin.heure, concert[i].dateFin.min, concert[i].dateFin.jour, concert[i].dateFin.mois, concert[i].dateFin.année);
    }
        	
    printf("Quel concert modifier ?\n");
    do {
        verif = scanf("%[^\n]s", text);
        vide_buffer();

    } while (verif != 1);
    scanfS(text);
    
    int indice = rechercheConcert(concert, text, nbC);
    
    if(indice < 0){
    	printf("ERREUR : Ce concert n'existe pas !\n");
    	return concert;
    }
    
    long current = time(NULL);
    long DebutC = conversionDateSecondesD(concert, indice);
    long FinC = conversionDateSecondesF(concert, indice);
    
    if(current < DebutC || current > FinC){
    	printf("Tu peux modifier !\n");
    }else{
    	printf("Tu peux pas modifier !\n");
    	return concert;
    }
    
    printf("Avant\n");
    printf("%dh%d %d/%d/%d",concert[indice].dateFin.heure,concert[indice].dateFin.min,concert[indice].dateFin.jour,
    concert[indice].dateFin.mois,concert[indice].dateFin.année);
    
    do{
    	printf("Donnez la date de fin : (ex : 12h55 13/5/2024)\n");
    	
    	verif = scanf("%dh%d %d/%d/%d",&concert[indice].dateFin.heure,&concert[indice].dateFin.min,&concert[indice].dateFin.jour,
    	&concert[indice].dateFin.mois,&concert[indice].dateFin.année);
    	vide_buffer();
    	
    }while(concert[indice].dateFin.heure < 0 || concert[indice].dateFin.heure > 23 || 
     concert[indice].dateFin.min < 0 || concert[indice].dateFin.heure > 59 || 
     concert[indice].dateFin.jour < 0 || concert[indice].dateFin.jour > 31 ||
     concert[indice].dateFin.mois < 0 ||concert[indice].dateFin.mois > 12 ||
     concert[indice].dateFin.année < 2024 || verif != 5);
    
    FinC = conversionDateSecondesF(concert, indice);
    
    if(FinC < DebutC){
    	printf("Date invalide ! :(\n");
	    exit(EXIT_FAILURE);
    }
    
    // tester avec des valeurs mauvaises
    printf("Fin\n");
    printf("%dh%d %d/%d/%d\n\n",concert[indice].dateFin.heure,concert[indice].dateFin.min,concert[indice].dateFin.jour,
    concert[indice].dateFin.mois,concert[indice].dateFin.année);
    
    // Partie Fosse
    do{	
    	printf("Voulez-vous ajouter une fosse (1- Oui | 0- Non)?\n");
    	verif = scanf("%d",&input);
    	vide_buffer();
    	
    }while(input<0 || input>1 || verif != 1);
    
    if(input == 1){
    	printf("Fosse ajoutee !\n");
    	concert[indice].fosse = 1;
    }
    
    ecrireConcert(concert,nbC);
    return concert;
}

Salle* modeManager(Salle *salle, Concert *concert, int *nbS, int *nbC){ // fonction qui permet au manager de gérer les salles et concerts du festival
    
    int choix;
    int verif;
    
    printf("||MODE MANAGER||\n\n");
    
    do{
        printf("1- CREER UNE OU PLUSIEURS SALLES\n2- MODIFIER UNE SALLE\n3- MODIFIER UN CONCERT\n4- ATTRIBUER UNE SALLE A UN CONCERT\n5- RETOUR AU MENU\n");
        choix = scanfD(1);

        switch(choix){
            case 1:
                if(salle == NULL){
                    //printf("Salle vide !\n");
                    salle = créerSalle(nbS);
                }else{
                    //printf("Salle non vide !\n");
                    salle = ajouterSalle(salle,*nbS,nbS);
                    //printf("nb = %d\n",*nbS);
                }
                break;
            case 2:
                //printf("nbS = %d\n", *nbS);
                //printf("nbC = %d\n", *nbC);
                salle = modifierSalle(salle,concert,*nbS,*nbC);
                break;
            case 3:
                concert = modifierConcert(concert,*nbC);
                break;
            case 4:
                salle = attribuerConcert(salle,*nbS,concert,*nbC);
                break;
            case 5:
            	printf("|| Retour au menu ||\n");
                break;
            default :
                printf("Mauvaise commande !\n");
                break;
        }
    }while(choix != 5);
    
    return salle;
}

Salle* réserverSalle(Salle *salle, int indiceS, int nbSalles){ // fonction qui permet à un festivalier de réserver une place dans la salle de son choix en fonction de sa disponibilité
    
    int l,c;
    int verif;
    int prixA, prixB, prixC;
    
    if(salle == NULL){
        printf("ERREUR : il n'y a pas de salles!\n");
        exit(EXIT_FAILURE);
    }
    
    if(indiceS < 0){
        return salle;
    }

    if (salle[indiceS].état != 1) {
        printf("Cette salle n'a pas de concert d'attribue!\n");
        return salle;
    }
    
    printf("-- %s --\n\n",salle[indiceS].nom);
    for(int j=0; j<salle[indiceS].nbRangées; j++){
        printf("R%d ",j+1);
        for(int k=0; k<salle[indiceS].rangées[j].nbSièges; k++){
            
            if(salle[indiceS].rangées[j].sièges[k].réservé == 0){
                if(salle[indiceS].rangées[j].sièges[k].catégorie == 'A'){
                	
                    prixA = salle[indiceS].rangées[j].sièges[k].prix;
                    couleur("32");
                	printf("O ");
                	couleur("0");
                }
                if(salle[indiceS].rangées[j].sièges[k].catégorie == 'B'){
                	
                    prixB = salle[indiceS].rangées[j].sièges[k].prix;
                    couleur("33");
                	printf("O ");
                	couleur("0");
                }
                if(salle[indiceS].rangées[j].sièges[k].catégorie == 'C'){
                    
                    prixC = salle[indiceS].rangées[j].sièges[k].prix;
                    couleur("35");
                	printf("O ");
                	couleur("0");
                }

            }else{
                couleur("31");
                printf("X ");
                couleur("0");
            }
        }
        printf("\n");
    }
    printf("\n--Legende--\n0   : siege libre\nX   : siege occupé\nVert : categorie A -> %d\nOrange : categorie B -> %d\nViolet : categorie C -> %d\n",prixA,prixB,prixC);

    do{
    	printf("Donnez l'emplacement que vous voulez réservé : (ex : 1,3)\n");
    	verif = scanf("%d,%d",&l,&c);
    	vide_buffer();
    }while(verif != 2 || l<=0 || c<=0);
    
    if(l > salle[indiceS].nbRangées){
    	printf("debordement memoire !! cette rangee n'existe pas\n");
    	exit(EXIT_FAILURE);
    }
    if(c > salle[indiceS].rangées[l-1].nbSièges){
 	printf("debordement memoire !! ce siege n'existe pas\n");
 	exit(EXIT_FAILURE);
    }
    if(salle[indiceS].rangées[l-1].sièges[c-1].réservé == 1){
    	printf("Ce siege est deja pris !\n");
    }
    
    salle[indiceS].rangées[l-1].sièges[c-1].réservé = 1;
    
    ecrireSalle(salle,nbSalles);
    
    return salle;
}

Salle* modeFestivalier(Salle *salle, Concert *concert, int *nbS, int *nbC){ // fonction qui permet au festivalier de voir les salles et de réserver une place
    
    int choix = 99;
    int indiceC;
    int indiceS;
    int verif;
    
    long current;
    long FinC;
    long DebutC;
    
    char nom[MAX];
    
    if(salle == NULL){
        printf("ERREUR : il n'y a pas de salles !\n");
        return NULL;
    }
    
    current = time(NULL);
    printf("%ld",current);
    
    for(int indiceS=0; indiceS<*nbS; indiceS++){
        
        indiceC = rechercheConcert(concert,salle[indiceS].concert.nom,*nbC);
        
        DebutC = conversionDateSecondesD(concert, indiceC);
        FinC = conversionDateSecondesF(concert, indiceC);
        
        if(indiceC < 0){
            printf("Salle : %s n'a pas de concert d'attribuée\n",salle[indiceS].nom);
            
        }else if(current < DebutC){
            printf("Salle : %s , Statut : concert %s prevu\n",salle[indiceS].nom,salle[indiceS].concert.nom);
        }else if(current > DebutC && current < FinC){
            printf("Salle : %s , Statut : concert %s en cours\n",salle[indiceS].nom,salle[indiceS].concert.nom);
        }else if(current > FinC){
            printf("Salle : %s , Statut : concert %s termine\n",salle[indiceS].nom,salle[indiceS].concert.nom);
        }
    }
    
    do{
        printf("||MODE FESTIVALIER||\n\n");

        printf("1- AFFICHER UNE OU PLUSIEURS SALLES\n2- RESERVER DES PLACES\n3- RETOUR AU MENU\n\n");
        choix = scanfD(1);
        
        switch(choix){
            case 1 :
                afficheSalle(salle,*nbS);
                break;
            case 2: 
                printf("|| Reservation de places ||\n");
                
                salle = lireSalle(nbS,1);
                printf("Dans quelle salle voulez-vous reserver ?\n");
                do {
                    verif = scanf("%[^\n]s", nom);
                    vide_buffer();

                } while (verif != 1);
                scanfS(nom);
                
                indiceS = rechercheSalle(salle,nom,*nbS);
                indiceC = rechercheConcert(concert,salle[indiceS].concert.nom,*nbC);
                
                current = time(NULL);
                DebutC = conversionDateSecondesD(concert, indiceC);
                FinC = conversionDateSecondesF(concert, indiceC);
                
                if(current >= DebutC){
                    printf("Tu ne peux pas reserver cette salle !\n");
                    return salle;
                }else{
                    printf("Tu peux réserver cette salle!\n");
                    réserverSalle(salle, indiceS, *nbS);
                }
                break;
            case 3:
                printf("|| Retour au menu ||\n");
                break;
            default :
                printf("choix default\n");
                break;
        }
        
    }while(choix != 3);
    
    return salle;
}
