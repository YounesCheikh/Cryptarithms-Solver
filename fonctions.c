/*
 *  fonctions.c
 *  
 *
 *  Created by Younes CHEIKH on 13/05/11.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fonctions.h"


int sum_chars()
{
		//Verification le nombre totale du caracteres utuliser
	char tab_tmp_char[26]; // tableau contient tous les caracteres majiscules
	int tab_tmp_cpt[26]; //tableau compte le nombre de répétation du caracteres dans une chaine
	
	char c='A'; //caractere du debut de tableau tab_tmp_char;
				//remplissage de tableau du caracteres tab_tmp_char
	int i,j;
	for(i=0;i<26;i++)
	{
		tab_tmp_char[i]=c;
		tab_tmp_cpt[i]=0;
		c++;
	}
	for(i=0;i<strlen(chaine_cryptarithme);i++)
	{
		c=chaine_cryptarithme[i];
		if(c!='+' && c!='=')
			for(j=0;j<26;j++)
			{
				if(tab_tmp_char[j]==c)
					tab_tmp_cpt[j]++;
			}
	}
	int somme=0;
	for(i=0;i<26;i++)
		if(tab_tmp_cpt[i]!=0)
			somme++;
		//printf("\nsomme: %d\n",somme);
	return somme;
}


int nb_mots()
{
	int nb_plus=0;
	int i=0;
	while(chaine_cryptarithme[i]!='\0')
	{
		if(chaine_cryptarithme[i]=='+')
			nb_plus++;
		i++;
	}
	return (nb_plus+2);
}


void majiscule_of(char chaine[])
{
	int i;
	for(i=0;i<strlen(chaine);i++)
		if (chaine[i]>='a' && chaine[i]<='z')
			chaine[i]=chaine[i]-32; // remplace les caracteres majiscules avec des miniscules
}


void initialise_m()
{
	int i,j;
	for(i=0;i<LG_CHAINE_RES;i++)
		for(j=0;j<nb_cols;j++)
			m[i][j]=-1;
}

void initialise_m_chars()
{
	int i,j;
	for(i=0;i<LG_CHAINE_RES;i++)
		for(j=0;j<nb_cols;j++)
			m_chars[i][j]='*';
}


void afficher_matrice()
{
	int i,j;
	for(j=0;j<nb_cols;j++)
	{
		for(i=LG_CHAINE_RES-1;i>=0;i--)
			if(m[i][j]==-1)
				printf(" ");
			else 
				printf("%d",m[i][j]);
		printf("\n");
	}
	printf("---------------\n");
	for(j=0;j<nb_cols;j++)
	{
		for(i=LG_CHAINE_RES-1;i>=0;i--)
			if(m_chars[i][j]=='*')
				printf(" ");
			else 
				printf("%c",m_chars[i][j]);
		printf("\n");
	}
	printf("===============\n\n");
	
}



void rempli_m_chars(int i,int col)
{
	int j=0;
	if(i>0 && col>0)
	{
			//printf("i: %d, col: %d\n",i,col);
		while(chaine_cryptarithme[i]!='=' && chaine_cryptarithme[i]!='+')
		{
			m_chars[j][col]=chaine_cryptarithme[i];
			i--;
			j++;
		}
		rempli_m_chars(i-1,col-1);
	}
	if (col==0)
	{
			//printf("else i: %d, col: %d\n",i,col);
		while(i>=0)
		{
			m_chars[j][col]=chaine_cryptarithme[i];
			i--;
			j++;
		}
	}
}



void initialise_char_liste()
{
	int i,j,k;
	bool trouve;
	k=0;
	
	for(i=0;i<nb_chars;i++)
		_CHARS_LISTE[i]='*';
	
	for(j=0;j<strlen(chaine_cryptarithme);j++)
	{
		trouve=false;
		if(chaine_cryptarithme[j]!='+' && chaine_cryptarithme[j]!='=')
		{
			for(i=0;i<nb_chars;i++)
				if(chaine_cryptarithme[j]==_CHARS_LISTE[i])
					trouve=true;
			if(trouve==false)
			{
				_CHARS_LISTE[k]=chaine_cryptarithme[j];
				k++;
			}
		}
	}
}

void initialise_int_liste()
{
	int i;
	for(i=0;i<nb_chars;i++) // initialise tous les cases du tableau a -1
	{
		_INT_LISTE[i]=-1;
	}
	
}

void rempli_m()
{
	
	int i;
	int col;
	int lig;
	for(lig=0;lig<LG_CHAINE_RES;lig++)
		for(col=0;col<nb_cols;col++)
			for(i=0;i<nb_chars;i++)
				if(m_chars[lig][col]==_CHARS_LISTE[i]) // && tab_calcul[i]!=-1)
					m[lig][col]=_INT_LISTE[i];
	
}

int cherche_valeur_possible(int lig,int retenue)
{
		//printf("here!\n");
	int i;
	int somme=0;
	for(i=0;i<nb_cols-1;i++)
	{
		if(m[lig][i]!=-1)
			somme=somme+m[lig][i];
	}
	if(somme+retenue==m[lig][nb_cols-1])
		return 0;
	else if((somme+retenue-m[lig][nb_cols-1])%10==0)
		return ((somme+retenue-m[lig][nb_cols-1])/10);
	else 
		return -1;
}

bool est_valide (int lig, int retenue)
{
	int i,j;
	for(i=0;i<nb_cols;i++)
		for(j=0;j<LG_CHAINE_RES-1;j++)
		{
			if((m[j][i]==0 && m[j+1][i]==-1) || (m[j+1][i]==0 && j==LG_CHAINE_RES-2))
				return false;
		}
	int r=cherche_valeur_possible(lig,retenue);
	if(lig<LG_CHAINE_RES-1)
	{
		if (r!=-1)
			return est_valide(lig+1,r);
		else
			return false;
		
	}
	else if(lig==LG_CHAINE_RES-1)
		if(r!=0) 
			return false;
	return true;
}

bool bon_tableau()
{
	int i,j,cpt;
	
	for(i=0;i<nb_chars;i++)
	{
		if(_INT_LISTE[i]==-1)
			return false;
		cpt=0;
		for(j=0;j<nb_chars;j++)
			if(_INT_LISTE[i]==_INT_LISTE[j])
				cpt++;
		if(cpt>1)
			return false;
	}
	return true;
}



bool cryptarithme_valide()
{
	return (bon_tableau() && est_valide (0,0));
}

bool ajout_possible(int indice,int n)
{
	int i;
	for(i=0;i<=indice;i++)
		if(_INT_LISTE[i]==n)
			return false;
	return true;
}

void add_val(int indice, int val)
{
	int lig,col;
	_INT_LISTE[indice]=val;
	for(lig=0;lig<LG_CHAINE_RES;lig++)
		for(col=0;col<nb_cols;col++)
			if(m_chars[lig][col]==_CHARS_LISTE[indice])
				m[lig][col]=val;
}


