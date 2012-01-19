/***
 * biblio.c
 * Younes CHEIKH
***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "biblio.h"

int max(int a,int b) //Fonction calcul le maximum entre deux entiers
{
	int m;
	m=a;
	if (m<=b) m=b;
	return m;
}

int min(int a,int b) //Fonction calcul le minimum entre deux entiers
{
	int m;
	m=a;
	if (m>=b) m=b;
	return m;
}

void ini_tableau(int* tab,int taille) //Fonction initialise un datbleau de 0 a taille
{
	//tab=(int*)malloc(sizeof(int*)*(taille));
	int i;
	for(i=0;i<taille;i++)
	{
		tab[i]=i;
		//printf("%d: %d | ",i,tab[i]);
	}
}

void afficher_tableau(int *tab, int taille) // fonction affiche un tableau
{
	int i;
	for(i=0;i<taille;i++)
		printf("%d ",tab[i]);
	printf("\n");
}