

from turtle import *

setup(600,300,20,20) #Taille de la fenetre turtle et sa position sur l'ecran
bgpic("Images/darkbg.gif")
############################################################

color("white")
#Chargement du resultats
liste_resultats=[]
	
f_sol = open('fin.txt', 'r+')
nb_sol=int(f_sol.read())
f_sol.close()
	
f_res = open('resultats.txt', 'r+')

i=0
while i<=nb_sol:
	t=[str(f_res.readline())]
	liste_resultats+=t
	i=i+1
f_res.close()

#print liste_resultats

speed(0)
ht()
home()

setup()
up()

register_shape("Images/quit.gif")
goto(250,-50)
shape("Images/quit.gif")
stamp()
	
HEADER_CHAINE="RESULTAT DU CRYPTARITHMES: "
HEADER_CHAINE+=str(nb_sol)
HEADER_CHAINE+=" Solutions"
def afficher_suivant():
	global liste_resultats,i
	if i<len(liste_resultats)-1:
		i=i+1
		clear()
		goto(-200,140)
		write(HEADER_CHAINE, move=True, align="left", font=("Arial", 20, "bold"))

		goto(-200,80)
		write(liste_resultats[0], move=True, align="left", font=("Arial", 14, "bold"))

		goto(-200,40)
		write(liste_resultats[i], move=True, align="left", font=("Arial", 17, "bold"))
		
		goto(-200,-40)
		write("Utiliser les fleches pour afficher la solution suivante", move=True, align="left", font=("Arial", 14, "bold"))

		goto(250,-50)
		shape("Images/quit.gif")
		stamp()
def afficher_precedent():
	global liste_resultats,i
	if i>1:
		i=i-1
		clear()
		goto(-200,140)
		write(HEADER_CHAINE, move=True, align="left", font=("Arial", 20, "bold"))

		goto(-200,80)
		write(liste_resultats[0], move=True, align="left", font=("Arial", 14, "bold"))

		goto(-200,40)
		write(liste_resultats[i], move=True, align="left", font=("Arial", 17, "bold"))
		
		goto(-200,-40)
		write("Utiliser les fleches pour afficher la solution suivante", move=True, align="left", font=("Arial", 14, "bold"))
		goto(250,-50)
		shape("Images/quit.gif")
		stamp()

i=1
goto(-200,140)
write(HEADER_CHAINE, move=True, align="left", font=("Arial", 20, "bold"))

goto(-200,80)
write(liste_resultats[0], move=True, align="left", font=("Arial", 14, "bold"))
	
goto(-200,40)
write(liste_resultats[i], move=True, align="left", font=("Arial", 17, "bold"))

goto(-200,-40)
write("Utiliser les fleches pour afficher la solution suivante", move=True, align="left", font=("Arial", 14, "bold"))
		
onkey(afficher_precedent,"Up")
onkey(afficher_suivant,"Down")
listen()

def quitter(x,y):
	if x<250+32 and x>250-32 and y<-50+32 and y>-50-32:
		bye()


onscreenclick(quitter)
mainloop()
