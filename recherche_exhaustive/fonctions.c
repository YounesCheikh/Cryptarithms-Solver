#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "biblio.h"
#include "fonctions.h"



	// fonction creer une fenetre dans le terminal
WINDOW *create_newwin(int height, int width, int starty, int startx) 
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

	//fonction efface une fentre
void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}

//Procedure transforme les minuscules en majiscules
void majiscule_of_chaine(char chaine[])
{
	int i;
	for(i=0;i<strlen(chaine);i++)
		if (chaine[i]>='a' && chaine[i]<='z')
			chaine[i]=chaine[i]-32; // remplace les caracteres majiscules avec des miniscules
}

//foction booleen verif si une chaine de caracteres contient un chiffre ou pas.
bool chiffre_in_chaine(char *chaine)
{
	bool retval=false; //la valeur a renvoyer
	int i;
	for(i=0;i<strlen(chaine);i++)
		if ((chaine[i]>='0' && chaine[i]<='9') || chaine[i]==' ')
			retval=true; // Si la chaine1 contient des chiffres
	return retval;
}

int summe_chars(T_cryptarithme cryptarithme)
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
	int big=max(max(strlen(cryptarithme.chaine1),strlen(cryptarithme.chaine2)),strlen(cryptarithme.chaine_res));
	char c1,c2,c3; //des caracteres temperaires
	for(i=0;i<big;i++)
	{
		c1=cryptarithme.chaine1[i];
		c2=cryptarithme.chaine2[i];
		c3=cryptarithme.chaine_res[i];
		for(j=0;j<26;j++)
		{
			if(tab_tmp_char[j]==c1)
				tab_tmp_cpt[j]++;
			if(tab_tmp_char[j]==c2)
				tab_tmp_cpt[j]++;
			if(tab_tmp_char[j]==c3)
				tab_tmp_cpt[j]++;
		}
	}
	int somme=0;
	for(i=0;i<26;i++)
		if(tab_tmp_cpt[i]!=0)
			somme++;
	return somme;
}

	// fonction booleene renvoi vrai si le caractere 'caractere' est present dans le tableau tab
bool caractere_present(char tab[],int taille, char caractere)
{
	int i;
	bool retval=false;
	for(i=0;i<taille;i++)
		if(tab[i]==caractere)
			retval=true;
	return retval;
}

	//fonction qui initialise le tableau SENDMORY
char* initialise_tab_chars(T_cryptarithme cryptarithme, char tab[])
{
	int nb_chars=summe_chars(cryptarithme);
	int i=0;
	int j;
	//char tab_of_chars[nb_chars];
	while(i<nb_chars)
	{
		for(j=0;j<strlen(cryptarithme.chaine1);j++)
			if(!caractere_present(tab,nb_chars,cryptarithme.chaine1[j]))
			{
				tab[i]=cryptarithme.chaine1[j];
				i++;
			}
		for(j=0;j<strlen(cryptarithme.chaine2);j++)
			if(!caractere_present(tab,nb_chars,cryptarithme.chaine2[j]))
			{
				tab[i]=cryptarithme.chaine2[j];
				i++;
			}
		for(j=0;j<strlen(cryptarithme.chaine_res);j++)
			if(!caractere_present(tab,nb_chars,cryptarithme.chaine_res[j]))
			{
				tab[i]=cryptarithme.chaine_res[j];
				i++;
			}
	}
	return tab;
}

//Fonction verif si l'utilisateur a tapé des 
//chaines du caracteres valide à utilisé ou pas
bool saisieValide(T_cryptarithme cryptarithme)
{
	//temp actuel
	time_t temp_act;
	time(&temp_act);
	//la valeur renvoyer par la fonction
	bool retval=false;
	//longueur de la chaine 1
	int stch1=strlen(cryptarithme.chaine1); 
	//longueur de la chaine 2
	int stch2=strlen(cryptarithme.chaine2); 
	// longueur de la chaine_res
	int stch_res=strlen(cryptarithme.chaine_res); 
	// Fichier qui contient les erreurs qui mettre la fonction renvoi un false
	FILE* f_erreur=fopen("erreur","a"); 
    if (f_erreur==NULL)
    {
		printf("\nProbleme: fichier 'erreur'\nNumero d'erreur: %d\n\a",errno);
    }
    
    // on verif s'il ya un chiffre dans les chaines
	if(chiffre_in_chaine(cryptarithme.chaine1) || chiffre_in_chaine(cryptarithme.chaine1) || chiffre_in_chaine(cryptarithme.chaine_res))
	{
		fprintf(f_erreur,"\n------------------%s\nChaine contient un ou plusieurs chiffres\n",ctime(&temp_act));
		fclose(f_erreur);
		return retval;
	}
	
	// entier utiliser pour comparer entre la longueur des chaines
	int big;
	
	// verification si la longueur des chaine est valide ou pas
	if( stch_res<max(stch1,stch2))
	{
		fprintf(f_erreur,"\n------------------%s\nles 2 chaine sont petit!\nstch1=%d\nstch2=%d\nstch_res=%d\n",ctime(&temp_act),stch1,stch2,stch_res);
		fclose(f_erreur);
		return retval;
	}
	else
	{
		big=max(stch1,stch2);
		if (stch_res>big+1)
		{
			fprintf(f_erreur,"\n------------------%s\nprobleme longueur chaine!\nstch1=%d\nstch2=%d\nstch_res=%d\n",ctime(&temp_act),stch1,stch2,stch_res);
			fclose(f_erreur);
			return retval;
		}
	}
	
	//Verification le nombre totale du caracteres utuliser
	
	if (summe_chars(cryptarithme)<10)
		retval=true;
	else
	{
		fprintf(f_erreur,"\n------------------%s\nLe nombre des caracteres depasse 10!\n%d caracteres!\n",ctime(&temp_act),summe_chars(cryptarithme));
		fclose(f_erreur);
		return retval;
	}
	return(retval);
}

void initialise_tabs(T_cryptarithme cryptarithme, T_tabs tabs)
{
	ini_tableau(tabs.tab1,strlen(cryptarithme.chaine1));
	ini_tableau(tabs.tab2,strlen(cryptarithme.chaine2));
	ini_tableau(tabs.tab_res,strlen(cryptarithme.chaine_res));
}


	//Fonction initialise le tableau entier qui associe au tableau SENDMORY
int* tab_calcul_initialise(int tab[],int taille)
{
	int i;
	tab[0]=1;
	tab[1]=0;
	for(i=2;i<taille;i++) tab[i]=i;
	return tab;
}

	//Fonction cherche le candidat suivant d'un tableau
int* creer_candidat_suivant(int tab[],int taille)
{
	int i=taille-1;
	int j;

	while ( (tab[i]==9) )
			{
				i--;
			}
	//passage au suivant
	tab[i]=tab[i]+1;
	//on met a 1 tous les "digits" suivants s'il y en a
	if (i<taille-1)
	{
		for(j=i+1;j<=taille-1;j++) tab[j]=0;
	}
	return(tab);
}


	// fonction renvoi vrai s'il ya une valeau qui se repeat plusieurs fois dans une tableau
bool valeur_repeate(int tab[],int taille)
{
	bool RETVAL=false;
	int i,j;
	for(i=0;i<taille-1;i++)
		for(j=i+1;j<taille;j++)
			if(tab[i]==tab[j])
				RETVAL=true;
	return RETVAL;
}

	//fonction renvoi le typte T_tabs associe au type T_cryptarithme

T_tabs sol_suivant(T_cryptarithme cryptarithme,T_tabs tabs, char tab_chars[],int tab_calcul[])
{
	int nb_chars=summe_chars(cryptarithme);
	int i,j;
	for(i=0;i<nb_chars;i++)
	{
		for(j=0;j<strlen(cryptarithme.chaine1);j++)
		{
			if(cryptarithme.chaine1[j]==tab_chars[i])
				tabs.tab1[j]=tab_calcul[i];
		}	
		for(j=0;j<strlen(cryptarithme.chaine2);j++)
		{
			if(cryptarithme.chaine2[j]==tab_chars[i])
				tabs.tab2[j]=tab_calcul[i];
		}	
		for(j=0;j<strlen(cryptarithme.chaine_res);j++)
		{
			if(cryptarithme.chaine_res[j]==tab_chars[i])
				tabs.tab_res[j]=tab_calcul[i];
		}	
	}
	return tabs;
}

	//Fonction determine si la recherche est terminée ou pas
bool recherche_non_terminee(int tab[],int taille)
{
	bool retval=false;
	int i=0;
	int val=9;
	while(i<taille)
	{
		if(tab[i]!=val)
		{
			retval=true;
			break;
		}
		i++;
		val--;
	}
	return retval;
}

	//Fonction booleen renvoi vrai si le cryptarithme est valide
bool estValide(T_cryptarithme cryptarithme,T_tabs tabs)
{
	bool retval=true;
	int i;
	
	if(tabs.tab1[0]==0 || tabs.tab2[0]==0 || tabs.tab_res[0]==0)
		return false;
	int nb1=0;
	for(i=0;i<strlen(cryptarithme.chaine1);i++)
		nb1=(nb1*10)+tabs.tab1[i];
	int nb2=0;
	for(i=0;i<strlen(cryptarithme.chaine2);i++)
		nb2=(nb2*10)+tabs.tab2[i];
	int nb_res=0;
	for(i=0;i<strlen(cryptarithme.chaine_res);i++)
		nb_res=(nb_res*10)+tabs.tab_res[i];
	
	if (nb_res!=nb1+nb2)
		retval=false;
	return retval;
}

	//Fonction charche les solution d'un fichier dans un tableau des chaine de caracteres
void charger_fichier(FILE* f, char m_sol[][255],int nb_sol)
{
	int i=0;
	while(i<nb_sol)
	{
		fscanf(f,"%s",m_sol[i]);
		i++;
	}
}
