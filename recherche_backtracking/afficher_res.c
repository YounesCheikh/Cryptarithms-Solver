	//Ce programme affiche les solutions avec la bibliotheque ncurses


#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char chaine_solved[255];

void charger_fichier(FILE* f, char m_sol[][255],int nb_sol);

WINDOW *create_newwin(int height, int width, int starty, int startx);

void destroy_win(WINDOW *local_win);


int main(int argc, char *argv[])
{
	
	initscr();			/* Start curses mode 		*/
	
	cbreak();			/* Line buffering disabled, Pass on
						 * everty thing to me 		*/
						 
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	
	WINDOW *win_principale;
	WINDOW *win_menu;
	WINDOW *win_main;
	//WINDOW *win_forme;
	//WINDOW *win_msgs;
	//WINDOW *win_solutions;
	WINDOW *win_footer;

	//printw("Util");
	
	int startx, starty, width, height;
	int H_win_menu,W_win_menu,H_win_main,W_win_main,H_win_footer,W_win_footer;
	int H_win_msgs,W_win_msgs,H_win_forme,W_win_forme;
	int H_win_solutions,W_win_solutions;
		
	starty = 1;	/* Calculating for a center placement */
		startx = 1;	/* of the window		*/
	
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
		//win_msgs = create_newwin(H_win_msgs, W_win_msgs, y_msgs, x_msgs);
		//win_forme = create_newwin(H_win_forme, W_win_forme, y_forme, x_forme);
		//win_solutions = create_newwin(H_win_solutions, W_win_solutions, y_solutions, x_solutions);
		
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
		mvprintw(y_forme,x_forme+1,"Utiliser Les fleches pour afficher les solutions: ");
		move(y_msgs,x_msgs+1);
		

	FILE * f_fin=fopen("fin.txt","r");
	if (f_fin==NULL)
	{
		endwin();
		printf("impossible de ouvrir le fichier fin.txt");
		exit(-1);
	}
	
	int nb_sol,ch;
	fscanf(f_fin,"%d",&nb_sol);
	fclose(f_fin);
	
	if(nb_sol>0)
			{
				char m_sol[nb_sol][255];
				FILE * f_res=fopen("resultats.txt","r");
				if (f_res==NULL)
				{
					endwin();
					printf("fichier resultats.txt introuvable!\n");
					exit(-1);
				}
				
				charger_fichier(f_res,m_sol,nb_sol);
				fclose(f_res);
				
				int sol_act=0;
				ch=0;
				attron(A_BOLD);
				attron(COLOR_PAIR(4));
				mvprintw(y_solutions,x_solutions+((W_win_solutions/2)-(strlen(m_sol[sol_act])/2)-8),"       %s ",chaine_solved);
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

	endwin();			/* End curses mode		  */	
	return 0;
}

void charger_fichier(FILE* f, char m_sol[][255],int nb_sol)
{
	fscanf(f,"%s",chaine_solved);
	int i=0;
	while(i<nb_sol)
	{
		fscanf(f,"%s",m_sol[i]);
		i++;
	}
}
	
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

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
	
	
	
	
	
	

