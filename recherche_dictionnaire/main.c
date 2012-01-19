/*
 *  main.c
 *  
 *
 *  Created by Younes CHEIKH on 12/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "filesearch.h"
#include "../fonctions.h"


	// MAIN
int main()
{
	nb_sol=0;
	int i;
	LG_CHAINE_RES=0;
	saisie();
	int n_max=nb_chiffre(nb_mots());
	strcpy(old_chaine_cryptarithme,chaine_cryptarithme);
	char chaine_tmp[255];
	FILE * dictionnaire=fopen("Ods.txt","r");
	if(dictionnaire==NULL)
	{
		printf("dictionnaire introuvable!\n");
		exit(-1);
	}
	bool first_exec=true;
	do
	{
		nb_sol=0;
		if(first_exec)
		{
			do 
			{
				fscanf(dictionnaire,"%s",chaine_tmp);
			}while(strlen(chaine_tmp)<lg_max);
			first_exec=false;
		}
		else 
			fscanf(dictionnaire,"%s",chaine_tmp);
		
		if (mot_utilisable(chaine_tmp))
		{
			nb_cols=nb_mots();
			i=strlen(chaine_cryptarithme)-1;
				//printf("%s\n",chaine_cryptarithme);
			LG_CHAINE_RES=0;
			while(chaine_cryptarithme[i]!='=')
			{
				LG_CHAINE_RES++;
				i=i-1;
			}
				//printf("LG_c %d\n",LG_CHAINE_RES);
			
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
			
			_INT_LISTE=(int*)malloc(sizeof(int*)*nb_chars);
			_CHARS_LISTE=(char*)malloc(sizeof(char*)*nb_chars);
			
			initialise_int_liste();
			initialise_char_liste();
			
				//Start Searching!
			cherche_sol(0);
			
			if(nb_sol!=0)
			{
				printf("%s\n",chaine_tmp);
			}
		}
			//free_mem();
	}while(strlen(chaine_tmp)<=lg_max+n_max);
	
	char c_null;
	while (true)
	{
		printf("taper n'importe quelle touche pour quitter: ");
		scanf("%c",&c_null);
		scanf("%c",&c_null);
			//printf("bonjour\n");
		break;
	}
	
	return 0;
}
