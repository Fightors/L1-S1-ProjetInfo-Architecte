//programme de stockage des données du fichier d'entrée en enregistrement

#include <iostream>
#include <fstream>
#include "liste.hpp"
using namespace std;

struct Terrain{
	int x1,y1,x2,y2;
	};

struct Salle{
	int lvl,x1,y1,x2,y2;
	};
	
struct Poteau{
    int x1,y1,z1,z2;
};

void stockage_donnee(string nom_fichier){
	fstream flux;
	Terrain trn;
	Salle sle;
	liste<Salle> l_salle;
	l_salle = {};
	flux.open(nom_fichier, ios::in);
		if (flux.is_open()) {
		flux >> trn.x1;
		flux >> trn.y1;
		flux >> trn.x2;
		flux >> trn.y2;
		flux >> sle.x1;
		flux >> sle.y1;
		flux >> sle.x2;
		flux >> sle.y2;
		// première lecture avant le tant que
		while (flux.good() ) { 
			inserer(l_salle,sle,taille(l_salle)+1);
			flux >> sle.x1;
			flux >> sle.y1;
			flux >> sle.x2;
			flux >> sle.y2;
			}
		flux.close();   
		}
		else {
		cout << "Erreur : impossible d'ouvrir " << nom_fichier << endl;
		}
 }
 
int main(){
	 
	 string coordonnee;
	 cout << "nom du fichier d'entiers a ouvrir" << endl;
	 cin >> coordonnee;
	 stockage_donnee(coordonnee);
 }