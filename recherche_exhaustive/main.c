#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "biblio.h"
#include "fonctions.h"



int main(int argc, char *argv[])
{
	initscr();			/* Start curses mode 		*/

	if(LINES<28 || COLS<80) // si la taille de terminal est petite on quit
	{
		
		printw("La taille de la fenetre est tres petite, Taille minimale '25x80'\n");
		refresh();
		printw("La taille de cette fenetre est '%dx%d'\n",LINES,COLS);
		printw("Essayer de redimensionner la fenetre et executer le programme a nouveau\n");
		int tmp_reste=10;
		printw("temp reste pour quitter: ");
		while(tmp_reste>0)
		{
			mvprintw(3,strlen("temp reste pour quitter: "),"  ");
			mvprintw(3,strlen("temp reste pour quitter: "),"%d",tmp_reste);
			timeout(1000);
			getch();
			tmp_reste--;
		}
		endwin();
		system("clear");
		exit(0);
	}
	else
	{
		cbreak();			/* Line buffering disabled, Pass on
						everty thing to me 		*/
		//printf("here!");
		//declaration des formes
		WINDOW *win_principale;
		WINDOW *win_menu;
		WINDOW *win_main;
		WINDOW *win_forme;
		WINDOW *win_msgs;
		WINDOW *win_solutions;
		WINDOW *win_footer;
		
		T_cryptarithme cryptarithme; //decalration de type
		////allocation dynamique de la memoire
	// 	cryptarithme.chaine1=(char*)malloc(sizeof(char*)*(strlen(cryptarithme.chaine1)));
	// 	cryptarithme.chaine2=(char*)malloc(sizeof(char*)*(strlen(cryptarithme.chaine2)));
	// 	cryptarithme.chaine_res=(char*)malloc(sizeof(char*)*(strlen(cryptarithme.chaine_res)));
		
		
		T_tabs tabs;
		
		
		int startx, starty, width, height;
		int H_win_menu,W_win_menu,H_win_main,W_win_main,H_win_footer,W_win_footer;
		int H_win_msgs,W_win_msgs,H_win_forme,W_win_forme;
		int H_win_solutions,W_win_solutions;
		
		starty = 1;	/* Calculating for a center placement */
		startx = 1;	/* of the window		*/
		//int ch;

		keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
		
		start_color();			/* Start color 			*/
		init_pair(1, COLOR_WHITE, COLOR_BLACK); //couleur normal
		init_pair(2, COLOR_WHITE, COLOR_GREEN);	 //couleur verte
		init_pair(3, COLOR_RED, COLOR_WHITE);	 //couleur d'erruer "rouge"
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);	 //couleur d'erruer "rouge"
		init_pair(5, COLOR_RED, COLOR_BLACK);	 //couleur d'erruer "rouge"	
		
		height = LINES-2;
		width = COLS-2;
		H_win_menu=5;
		W_win_menu=width-4;
		H_win_footer=6;
		W_win_footer=COLS-6;
		H_win_main=height-H_win_menu-H_win_footer-2;
		W_win_main=width-4;
		H_win_msgs=5;
		W_win_msgs=W_win_main/2-4;
		H_win_forme=5;
		W_win_forme=W_win_main/2-2;
		H_win_solutions=height-H_win_footer-H_win_menu-H_win_forme-4;
		W_win_solutions=W_win_main-4;
		
		int x_menu,y_menu,x_main,y_main,x_footer,y_footer,x_forme,y_forme,x_msgs,y_msgs,x_solutions,y_solutions;
		x_menu=3;
		y_menu=2;
		x_footer=3;
		y_footer=height-H_win_footer;
		y_main=starty+H_win_menu+1;
		x_main=3;
		x_msgs=W_win_main-W_win_msgs+1;
		y_msgs=starty+H_win_menu+2;
		x_forme=5;
		y_forme=starty+H_win_menu+2;
		x_solutions=5;
		y_solutions=starty+H_win_menu+H_win_forme+2;
		
		attron(COLOR_PAIR(5));
		mvprintw(LINES-1,0,"(CTRL+C) to force exit");
		attroff(COLOR_PAIR(5));
		refresh();
		
		win_principale = create_newwin(height, width, starty, startx);
		win_menu = create_newwin(H_win_menu, W_win_menu , y_menu, x_menu);
		win_footer = create_newwin(H_win_footer, W_win_footer, y_footer, x_footer);
		win_main = create_newwin(H_win_main, W_win_main, y_main, x_main);
		win_msgs = create_newwin(H_win_msgs, W_win_msgs, y_msgs, x_msgs);
		win_forme = create_newwin(H_win_forme, W_win_forme, y_forme, x_forme);
		win_solutions = create_newwin(H_win_solutions, W_win_solutions, y_solutions, x_solutions);
		
		attron(A_BOLD);
		int i;
		attron(COLOR_PAIR(4));
		
		//Header
		for(i=1;i<W_win_menu-1;i++)
			mvprintw(y_menu+1,x_menu+i,"#");
		mvprintw(y_menu+2,x_menu+1,"################");
		mvprintw(y_menu+2,W_win_menu/2,"CRYPTARITHME");
		mvprintw(y_menu+2,x_menu+W_win_menu-17,"################");
		for(i=1;i<W_win_menu-1;i++)
			mvprintw(y_menu+3,x_menu+i,"#");
		attroff(COLOR_PAIR(4));
		attroff(A_BOLD);
		//fin header
		//debut footer
		attron(A_UNDERLINE);
		attron(A_BOLD);
		mvprintw(y_footer+1,x_footer+(W_win_footer/2-strlen("CENTRE UNIVERSITAIRE JEAN-FRANCOIS CHAMPOLLION")/2),"CENTRE UNIVERSITAIRE JEAN-FRANCOIS CHAMPOLLION");
		attroff(A_BOLD);
		attroff(A_UNDERLINE);
		mvprintw(y_footer+2,x_footer+1,"ETUDIANT  : YOUNES CHEIKH");
		mvprintw(y_footer+3,x_footer+1,"Enseignant: PIERRE PICCININI");
		mvprintw(y_footer+4,x_footer+(W_win_footer/2-strlen("2010/2011")/2),"2010/2011");
		//fin footer
		mvprintw(y_forme,x_forme+1,"Taper les chaines de caracteres:");
		move(y_msgs,x_msgs+1);
		//mvprintw(y_msgs,x_msgs+1,"observations:");
		//refresh();
		//wrefresh(win_msgs);
		//wrefresh(win_forme);
		
			
	// 	char chaine1[20];
	// 	char chaine2[20];
	// 	char chaine_res[20];
		//bool chaines_valide;
		int ch;
		int nb_sol=0;
		bool first_exe=true;
		bool first_search=true;
		while(1)
		{
			//refresh();
// 			wrefresh(win_msgs);
// 			wrefresh(win_forme);
			attron(COLOR_PAIR(1));
			mvprintw(y_solutions+1,x_solutions+1,"nombres des solutions: %d",nb_sol);
			int tmp;
			if(first_exe)
			{
				mvprintw(y_forme+1,x_forme+1,"CHAINE 1: ");
				mvprintw(y_forme+2,x_forme+1,"CHAINE 2: ");
				mvprintw(y_forme+3,x_forme+1,"CHAINE RESULTAT: ");
				
				bool chaines_valide;	
				do
				{
					for(tmp=1;tmp<=strlen(cryptarithme.chaine1);tmp++)
						mvprintw(y_forme+1,x_forme+tmp+strlen("CHAINE 1: ")," ");
					mvprintw(y_forme+1,x_forme+1+strlen("CHAINE 1: "),"");
					getstr(cryptarithme.chaine1);
					majiscule_of_chaine(cryptarithme.chaine1);
					mvprintw(y_forme+1,x_forme+1+strlen("CHAINE 1: "),"%s",cryptarithme.chaine1);
					
					for(tmp=1;tmp<=strlen(cryptarithme.chaine2);tmp++)
						mvprintw(y_forme+2,x_forme+tmp+strlen("CHAINE 2: ")," ");
					mvprintw(y_forme+2,x_forme+1+strlen("CHAINE 2: "),"");
					getstr(cryptarithme.chaine2);
					majiscule_of_chaine(cryptarithme.chaine2);
					mvprintw(y_forme+2,x_forme+1+strlen("CHAINE 2: "),"%s",cryptarithme.chaine2);
					
					for(tmp=1;tmp<=strlen(cryptarithme.chaine_res);tmp++)
						mvprintw(y_forme+3,x_forme+tmp+strlen("CHAINE RESULTAT: ")," ");
					mvprintw(y_forme+3,x_forme+1+strlen("CHAINE RESULTAT: "),"");
					getstr(cryptarithme.chaine_res);
					majiscule_of_chaine(cryptarithme.chaine_res);
					mvprintw(y_forme+3,x_forme+1+strlen("CHAINE RESULTAT: "),"%s",cryptarithme.chaine_res);
					chaines_valide=saisieValide(cryptarithme);
					int lg_ch1=strlen(cryptarithme.chaine1);
					int lg_ch2=strlen(cryptarithme.chaine2);
					int lg_ch_res=strlen(cryptarithme.chaine_res);
					if(chaines_valide)
					{
						if(lg_ch_res!=0 && lg_ch1!=0 && lg_ch2!=0)
						{
							tabs.tab1=(int*)malloc(sizeof(int*)*(strlen(cryptarithme.chaine1)));
							tabs.tab2=(int*)malloc(sizeof(int*)*(strlen(cryptarithme.chaine2)));
							tabs.tab_res=(int*)malloc(sizeof(int*)*(strlen(cryptarithme.chaine_res)));
							for(tmp=1;tmp<W_win_msgs-1;tmp++)
								mvprintw(y_msgs+2,x_msgs+tmp," ");
							attron(COLOR_PAIR(2));
							mvprintw(y_msgs+2,x_msgs+(W_win_msgs/2-strlen("saisie Valide :-)")/2) ,"saisie Valide :-)");
							attron(COLOR_PAIR(1));
							timeout(2000);
							getch();
							sleep(1);
							break;
						}
					}
					else
					{
						for(tmp=1;tmp<W_win_msgs-1;tmp++)
							mvprintw(y_msgs+2,x_msgs+tmp," ");
						attron(COLOR_PAIR(3));
						mvprintw(y_msgs+2,x_msgs+(W_win_msgs/2-strlen("saisie non Valide :(")/2),"saisie non Valide :(");
						attron(COLOR_PAIR(1));
						//printf("\a");
					}
				}while(1);
				
				first_exe=false;
			}
			//sleep(1);
			if(first_search)
			{		
				for(tmp=1;tmp<W_win_msgs-1;tmp++)
					mvprintw(y_msgs+2,x_msgs+tmp," ");
				attron(COLOR_PAIR(4));
				mvprintw(y_msgs+2,x_msgs+(W_win_msgs/2-strlen("Recherche en cours...")/2),"Recherche en cours...");
				attroff(COLOR_PAIR(4));
				timeout(25);
				getch();
				initialise_tabs(cryptarithme,tabs);
				int nb_chars=summe_chars(cryptarithme);
				
				int* tab_calcul;
				char* tab_chars;
				
				tab_calcul=(int*)malloc(sizeof(int*)*nb_chars);
				tab_calcul_initialise(tab_calcul,nb_chars);
				
				tab_chars=(char*)malloc(sizeof(char*)*nb_chars);
				initialise_tab_chars(cryptarithme,tab_chars);
				
				FILE * f_des=fopen("res","w");
				if (f_des==NULL)
				{
					printf("fichier res introuvable!");
					exit(-1);
				}
				
				while(recherche_non_terminee(tab_calcul,nb_chars))
				{
					
					//mvprintw(y_msgs+2,x_msgs+(W_win_msgs/2-strlen("Recherche en cours...")/2),"Recherche en cours...");
					creer_candidat_suivant(tab_calcul,nb_chars);
					if(!valeur_repeate(tab_calcul,nb_chars))
					{
						sol_suivant(cryptarithme,tabs,tab_chars,tab_calcul);
						if(estValide(cryptarithme,tabs))
						{
							int indice;
							for(indice=0;indice<strlen(cryptarithme.chaine1);indice++)
								fprintf(f_des,"%d",tabs.tab1[indice]);
							fprintf(f_des,"+");	
							for(indice=0;indice<strlen(cryptarithme.chaine2);indice++)
								fprintf(f_des,"%d",tabs.tab2[indice]);
							fprintf(f_des,"=");	
							for(indice=0;indice<strlen(cryptarithme.chaine_res);indice++)
								fprintf(f_des,"%d",tabs.tab_res[indice]);
							fprintf(f_des,"\n");
							nb_sol++;
							timeout(1);
							getch();
							mvprintw(y_solutions+1,x_solutions+1,"nombres des solutions: %d",nb_sol);
						}
							
					}
					
					//afficher_tableau(tab_calcul,nb_chars);
				}
				for(tmp=1;tmp<W_win_msgs-1;tmp++)
					mvprintw(y_msgs+2,x_msgs+tmp," ");
				attron(COLOR_PAIR(4));
				mvprintw(y_msgs+2,x_msgs+(W_win_msgs/2-strlen("Recherche terminee.")/2),"Recherche terminee.");
				attroff(COLOR_PAIR(4));
				first_search=false;
				fclose(f_des);
			}
			
			attron(COLOR_PAIR(2));
			mvprintw(y_solutions-1+H_win_solutions-2,x_solutions+1,"Taper 'ESC' pour quitter");
			mvprintw(y_solutions+H_win_solutions-2,x_solutions+1,"Utiliser les fleches pour afficher les solutions");
			
			if(nb_sol>0)
			{
				char m_sol[nb_sol][255];
				FILE * fic=fopen("res","r");
				if (fic==NULL)
				{
					//printf("fichier res introuvable!\n");
					exit(-1);
				}
				
				charger_fichier(fic,m_sol,nb_sol);
				fclose(fic);
				int sol_act=0;
				ch=0;
				attron(A_BOLD);
				attron(COLOR_PAIR(4));
				mvprintw(y_solutions+2,x_solutions+((W_win_solutions/2)-(strlen(m_sol[sol_act])/2)-8),"Solution N %d: %s ",(sol_act+1),m_sol[sol_act]);

				while(true)
				{
					noecho();
					timeout(2000);
					ch=getch();
					attroff(COLOR_PAIR(2));
					switch(ch)
					{	
						case KEY_UP:
							if(sol_act>0)
							{	
								sol_act--;
								//mvprintw(10,10,"                                             ");
								mvprintw(y_solutions+2,x_solutions+((W_win_solutions/2)-(strlen(m_sol[sol_act])/2)-8),"Solution N %d: %s ",(sol_act+1),m_sol[sol_act]);
							}
							break;
						case KEY_DOWN:
							if(sol_act<nb_sol-1)
							{
								sol_act++;
								//mvprintw(10,10,"                                             ");
								mvprintw(y_solutions+2,x_solutions+((W_win_solutions/2)-(strlen(m_sol[sol_act])/2)-8),"Solution N %d: %s ",(sol_act+1),m_sol[sol_act]);
							}
							break;
					}
					//refresh();
					if(ch==27)
						break;
				}
				attroff(COLOR_PAIR(4));
				attroff(A_BOLD);
			}
			else
			{
				noecho();
				timeout(2000);
				ch=getch();
			}
			
			/*noecho();
			timeout(2000);
			ch=getch();
			attroff(COLOR_PAIR(2));*/
			if(ch==27) 
				break;
		}
			
		endwin();			/* End curses mode		  */
	}
	return 0;
}