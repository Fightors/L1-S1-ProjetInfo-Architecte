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

void ecriture_fichier(Terrain trn,liste<Salle> liste_salle, liste<poteau> liste_poteaux, int long_poteau, int eco_poteau,string  nom_fichier){
    fstream flux;

    flux.open(nom_fichier, ios::out);
    if (flux.is_open()){
        flux << "terrain : " << trn.x1 <<", " << trn.y1 <<", " << trn.x2 <<", " << trn.y2 << endl;
        flux << "salles " << taille(liste_salle) << endl;
        for ( Salle sle : liste_salle){
            flux << sle.lvl << " : "<< sle.x1 << ", "<< sle.y1 << ", "<< sle.x2 << ", "<< sle.y2 << endl;
            }
        flux << "poteaux " << taille(liste_poteaux) << endl;
        for ( Poteau ptx : liste_poteaux){
            flux << ptx.x1 << ", "<< ptx.y1 << ", "<< ptx.z1 << ", "<< ptx.z2 << endl;
            }
        flux << "longueur_poteaux : " << long_poteau << endl;
        flux << "economie_poteaux : " << eco_poteau << endl;
        flux.close();   
    }
    else {
       cout << "Erreur : impossible d'ecrire dans le fichier " << nom_fichier << endl;
    }
}