

#ifndef FONCTIONS_H
#define FONCTIONS_H

typedef struct 
{
	char chaine1[255];
	char chaine2[255];
	char chaine_res[255];
}T_cryptarithme;

typedef struct
{
	int * tab1;
	int * tab2;
	int * tab_res;
}T_tabs;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void majiscule_of_chaine(char chaine[]);
bool chiffre_in_chaine(char *chaine);

int summe_chars(T_cryptarithme cryptarithme);

bool caractere_present(char tab[],int taille, char caractere);

char* initialise_tab_chars(T_cryptarithme cryptarithme, char tab[]);

bool saisieValide (T_cryptarithme cryptarithme);

void initialise_tabs(T_cryptarithme cryptarithme, T_tabs tabs);

int* tab_calcul_initialise(int tab[],int taille);

int* creer_candidat_suivant(int tab[],int taille);

bool valeur_repeate(int tab[],int taille);

T_tabs sol_suivant(T_cryptarithme cryptarithme,T_tabs tabs, char tab_chars[],int tab_calcul[]);

bool recherche_non_terminee(int tab[],int taille);

bool estValide(T_cryptarithme cryptarithme,T_tabs tabs);

void charger_fichier(FILE* f, char m_sol[][255],int nb_sol);

#endif