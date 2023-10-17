#include <iostream>
#include <fstream>
#include <string> 
#include "liste.hpp"
using namespace std;

struct Salle{
	int lvl,x1,y1,x2,y2;
};

struct Poteau{
    int x1,y1,z1,z2;
};

void calcul_stats( liste<Salle> l_salle , int & h_max, int & nb_salles , int & surf_tot , liste<int> & l_surf_tot_lvl ){
	// calcul de la hauteur max
	for ( Salle sle : l_salle ) {
		h_max = 10;
		if (sle.lvl*10 > h_max ){
			h_max = sle.lvl;
			}
	}
	// calcul du nombre de salle
	nb_salles = int (taille(l_salle));
	
	//calcul de la surface total
	for ( Salle sle : l_salle ) {
		surf_tot = surf_tot + (sle.x2-sle.x1)*(sle.y2-sle.y1);
	}
	//creation de la liste surf tot par niveau 
	for (int cpt = 1; cpt <= h_max ; cpt ++){
		l_surf_tot_lvl [cpt] = 0;
	}
	// 
	for ( Salle sle : l_salle) {
		l_surf_tot_lvl[sle.lvl]= l_surf_tot_lvl[sle.lvl] + (sle.x2-sle.x1)*(sle.y2-sle.y1);
	}
}
