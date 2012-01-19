/*
 *  fonctions.h
 *  
 *
 *  Created by Younes CHEIKH on 13/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef FONCTIONS_H
#define FONCTIONS_H

	//Declaration des variables Globales

char chaine_cryptarithme[255];

char old_chaine_cryptarithme[255];

char* _CHARS_LISTE;

int* _INT_LISTE;

int** m; // La matrice des entiers

int LG_CHAINE_RES; // longueur de la chaine resultat <MONEY>

int nb_cols; // le nombre de colonnes de la matrice ou le nombre du mots

int nb_chars; // Le nombre du caracteres utilisé

char** m_chars; // La matrice des caracteres

int nb_sol;

int lg_max;

	// Fonctions

int sum_chars();

int nb_mots();

void majiscule_of(char chaine[]);

void initialise_m();

void initialise_m_chars();

void afficher_matrice();

void rempli_m_chars(int i,int col);

void initialise_char_liste();

void initialise_int_liste();

void rempli_m();

int cherche_valeur_possible(int lig,int retenue);

bool est_valide (int lig, int retenue);

bool bon_tableau();

bool cryptarithme_valide();

bool ajout_possible(int indice,int n);

void add_val(int indice, int val);

#endif