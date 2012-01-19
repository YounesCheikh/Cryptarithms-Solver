/*
 *  backtracking.c
 *  
 *
 *  Created by Younes CHEIKH on 13/05/11.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "backtracking.h"
#include "../fonctions.h"


bool saisie_valide() 
{
	int i;
	char c;
	int plus_char=0;
	int egale_char=0;
	c=chaine_cryptarithme[0];
	
	int lg=(int)strlen(chaine_cryptarithme);
	
	int lg_max=0;
	int lg_act=0;
	int lg_res=0;
	bool ch_res=false;
	nb_chars=sum_chars();
	if (nb_chars>10)
		return false;
	
		//verification de la longueur du mots
	for(i=0;i<lg;i++)
	{
		if(chaine_cryptarithme[i]=='=')
		{
			ch_res=true;
			if(lg_act>lg_max)
				lg_max=lg_act;
			lg_act=0;
		}
		if(!ch_res)
		{
			if(chaine_cryptarithme[i]!='+')
				lg_act++;
			else
			{
				if(lg_max<lg_act)
					lg_max=lg_act;
				lg_act=0;
			}
		}
		else 
		{
			if(chaine_cryptarithme[i]!='=')
				lg_res++;
		}
	}
	if(lg_max>lg_res)
		return false;
	
		// --------------------------------------- //
	if((c<'a' || c>'z') && (c<'A' || c>'Z'))
	{
		printf("il faut taper des caracteres entre A et Z\n");
		return false;
	}
	for(i=0;i<strlen(chaine_cryptarithme);i++)
	{
		if(chaine_cryptarithme[i]=='+')
			plus_char++;
		if(chaine_cryptarithme[i]=='=')
			egale_char++;
	}
	if(egale_char==0 || plus_char==0)
	{
		printf("la bonne forme: MOT+MOT=MOT\n");
		return false;
	}
	for(i=0;i<strlen(chaine_cryptarithme);i++)
	{
		c=chaine_cryptarithme[i];
		if( (c==' ')  || ((c!='+' && c!='=') && ((c<'a' || c>'z') && (c<'A' || c>'Z'))))
			return false;
	}
	return true;
}

void saisie()
{
	bool s_valide=false;
	int nmots;
	do
	{
		printf("Cryptarithme: ");
		scanf("%s",chaine_cryptarithme);
		majiscule_of(chaine_cryptarithme);
		s_valide=saisie_valide();
		nmots=nb_mots();
		if(!s_valide)
			printf("saisie non valide\n");
		else if(nmots<3)
			printf("le cryptarithme sous la forme : mot+mot=mot\n");
	}while(!s_valide || nmots<3);
		//majiscule_of(chaine_cryptarithme);
}

void envoyer_res(FILE* fich) // procedure renvoi les solutions dans un fichier
{
	int i,j;
	for(j=0;j<nb_cols;j++)
	{
		for(i=LG_CHAINE_RES-1;i>=0;i--)
			if(m[i][j]!=-1)
				fprintf(fich,"%d",m[i][j]);
		if(j<nb_cols-2)
			fprintf(fich,"+");
		else if(j==nb_cols-2)
			fprintf(fich,"=");
		else 
			fprintf(fich,"\n");
	}
}

void cherche_sol(int i,FILE* fich) // fonction recurssive qui cherche les solutions possibles
{
	int val,j;
	if(i<nb_chars)
	{
		for(val=0;val<10;val++)
		{
			for(j=i+1;j<nb_chars;j++)
				add_val(j,-1);
			if(ajout_possible(i,val))
			{
				add_val(i,val);
				if(cryptarithme_valide())
				{
						//printf("\n================\n");
						//afficher_matrice();
					envoyer_res(fich);
					nb_sol++;
				}
				cherche_sol(i+1,fich);
			}
		}
	}
}

