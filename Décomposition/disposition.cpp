
#include <iostream>
#include "liste.hpp"

using namespace std;

struct Terrain{
    int x1,y1,x2,y2;
};

struct Salle{
    int lvl,x1,y1,x2,y2;
};

// Fonction qui vérifie si deux salles passées en paramètre se superposent.

bool Superposition ( Salle s1, Salle s2 ){
	return not (s2.x1 >= s1.x2 or s2.y1 >= s1.y2 or s2.x2 <= s1.x1 or s2.y2 <= s1.y1); 
}

// Procédure qui vérifie si les salles d'une liste de salle passée 
// en paramètre se superposent, et calculent son niveau.

void Disposition(liste<Salle> & liste_salle){
    liste_salle[1].lvl=0;
    for ( unsigned int i=2; i<= taille(liste_salle); i+=1 ){
        for ( unsigned int j=2; j<=i; j+=1){
			if (Superposition ( liste_salle[i], liste_salle[j-1] ) ){
				liste_salle[i].lvl=liste_salle[j-1].lvl+1;
            }
        }
    }
}


		 
	

int main (){
liste<Salle> l_salle;
Salle salle1 = {0,2,2,9,9};
Salle salle2 = {0,14,14,26,26};
inserer(l_salle, salle1, 1);
inserer(l_salle, salle2, 2);
Disposition(l_salle);
cout<<l_salle[1].lvl<< " et " << l_salle[2].lvl << endl;
}

