#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(){

	//faire une fonction qui récupère les données du fichier concerts.txt 
	//et transforme en seconde
	
	//vérifier si la date actuelle est inférieure, égale ou supérieur à la date d'un concert
	
	struct tm tmp;
	
	tmp.tm_sec   = 0;
	tmp.tm_min   = 30;
	tmp.tm_hour  = 20;
	tmp.tm_mday  = 14;
	tmp.tm_mon   = 5-1;
	tmp.tm_year  = 2024-1900;
	tmp.tm_wday  = 0;
	tmp.tm_yday  = 0;
	tmp.tm_isdst = 0;

	// récupère le nombre de secondes actuel du système
	long current = time(NULL);
	
	// mktime récupère les données de la structure tm et la convertie en secondes
	long later = mktime(&tmp);

	printf("c = %ld\n", current);
	printf("l = %ld\n", later);

	printf("d = %ld\n", later-current);
	
	return 0;
	
	
	// fonction qui calcule datefin et datedebut différence 
	// fonction qui récupère données date concerts et les convertis en secondes système
	
	
}
