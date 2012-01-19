/*
 *  main.c
 *  
 *
 *  Created by Younes CHEIKH on 13/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "backtracking.h"
#include "../fonctions.h"


int main()
{
	nb_sol=0;
	LG_CHAINE_RES=0;
	saisie();
	nb_cols=nb_mots();
	int i=strlen(chaine_cryptarithme)-1;
	while(chaine_cryptarithme[i]!='=')
	{
		LG_CHAINE_RES++;
		i=i-1;
	}
	
		// L'allocation dynamique des matrices m et m_chars
	m=(int**)malloc(sizeof(int*)*LG_CHAINE_RES);
	for(i=0;i<LG_CHAINE_RES;i++)
		m[i]=(int*)malloc(sizeof(int*)*nb_cols);
	
	m_chars=(char**)malloc(sizeof(char*)*LG_CHAINE_RES);
	for(i=0;i<LG_CHAINE_RES;i++)
		m_chars[i]=(char*)malloc(sizeof(char*)*nb_cols);
		// ########### fin de l'allocation dynamique
	
	initialise_m();
	initialise_m_chars();
	rempli_m_chars(strlen(chaine_cryptarithme)-1,nb_cols-1);
	
		//nb_chars=sum_chars();
	
	_INT_LISTE=(int*)malloc(sizeof(int*)*nb_chars);
	_CHARS_LISTE=(char*)malloc(sizeof(char*)*nb_chars);
	
	initialise_int_liste();
	initialise_char_liste();
	
	
		//printf("%s\n%d,%d\n",chaine_cryptarithme,nb_cols,LG_CHAINE_RES);
	rempli_m();
		//afficher_matrice();
		//for(i=0;i<nb_chars;i++)
		//	printf("%c ",_CHARS_LISTE[i]);
		//printf("\n");
	
	FILE* _RES_=fopen("resultats.txt","w");
	if (_RES_==NULL)
	{
		printf("Je ne pas creer des fichier dans le repertoire courant!\n");
		exit(-1);
	}
	fprintf(_RES_,"%s\n",chaine_cryptarithme);
	cherche_sol(0,_RES_);
	fclose(_RES_);
	
	
	
	FILE* _FIN_=fopen("fin.txt","w");
	if (_FIN_==NULL)
	{
		printf("Je ne pas creer des fichier dans le repertoire courant!\n");
		exit(-1);
	}
	else 
	{
		fprintf(_FIN_,"%d",nb_sol);
		fclose(_FIN_);
	}
	if(nb_sol>0)
	{
		int choix;
		printf("* Pour afficher les solutions en fenetres python taper 1 \n");
		printf("* Pour afficher les solutions dans fenetre acctuelle taper 2 \n");
		do
		{
		printf("Taper votre choix: ");
		scanf("%d",&choix);
		if(choix!=1 && choix!=2)
			printf("Je n'ai pas compris votre choix!!\n");
		}
		while(choix!=1 && choix!=2);
	if(choix==1)
		system("python read_results.py &");
	else
		system("./afficher_res");
	}
	else
	{
		char c_null;
		printf("Aucune solution trouvé\n"); 
		printf("taper n'import quelle touche pour quitter: ");
		scanf("%c",&c_null);
		scanf("%c",&c_null);
	}
	return 0;
}
