/*
 *  fonctions.c
 *  
 *
 *  Created by Younes CHEIKH on 12/05/11.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "filesearch.h"
#include "../fonctions.h"


	//FONCTIONS

bool saisie_valide()
{
	int i;
	char c;
	int plus_char=0;
		//int egale_char=0;
	c=chaine_cryptarithme[0];
	
		//int lg=(int)strlen(chaine_cryptarithme);
	
		//int lg_res=0;
		//bool ch_res=false;
	nb_chars=sum_chars();
	lg_max=0;
	int lg_act=0;
	if (nb_chars>10)
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
		{
			plus_char++;
			if(lg_act>lg_max) 
				lg_max=lg_act;
			lg_act=0;
		}
		else 
			lg_act++;
	}
	if(lg_act>lg_max) 
		lg_max=lg_act;
	if(plus_char==0)
	{
		printf("la bonne forme: MOT+MOT\n");
		return false;
	}
	for(i=0;i<strlen(chaine_cryptarithme);i++)
	{
		c=chaine_cryptarithme[i];
		if( (c==' ')  || ((c!='+') && ((c<'a' || c>'z') && (c<'A' || c>'Z'))))
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


void cherche_sol(int i)
{
	int val,j;
	if(i<nb_chars && nb_sol==0)
	{
		for(val=0;val<10;val++)
		{
			for(j=i+1;j<nb_chars;j++)
				add_val(j,-1);
			if(ajout_possible(i,val))
			{
				add_val(i,val);
				if(cryptarithme_valide())
					nb_sol++;
				else 
					cherche_sol(i+1);
			}
		}
	}
}

bool mot_utilisable(char mot[])
{
	strcpy(chaine_cryptarithme,old_chaine_cryptarithme);
	strcat(chaine_cryptarithme,"=");
	strcat(chaine_cryptarithme,mot);
		//printf("%s: %d \n",chaine_cryptarithme,(int)strlen(chaine_cryptarithme));
	nb_chars=sum_chars();
	if(nb_chars<=10)
		return true;
	else 
		return false;
}

void free_mem()
{
	int lig;//,col;
	for(lig=0;lig<LG_CHAINE_RES;lig++)
			//for(col=0;col<nb_cols;col++)
	{
		free(m[lig]);
		free(m_chars[lig]);
	}
		//free(chaine_cryptarithme);
	free(_CHARS_LISTE);
	free(_INT_LISTE);
}

int nb_chiffre(int nombre)
{
	int n=0;
	while(nombre>0)
	{
		nombre=nombre/10;
		n++;
	}
	return n;
}
