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


bool donnees_ok(liste<Salle> liste_s, Terrain trn){
	for ( Salle sle : liste_s){
		if (trn.x1>sle.x1 or trn.y1>sle.y1 or trn.x2<sle.x2 or trn.y2<sle.y2 or trn.x1!=0 or trn.y1!=0 or trn.x2 <= 0 or trn.y2 <= 0 or sle.x1 < 0 or sle.y1 < 0 or sle.x2 < 1 or sle.y2 < 1){
			return false;
		}
	}
	return true;
}

int main(){
	//liste<Salle> l_salle= {{0,0,0,50,50} , {0,0,0,75,75} };
	//Terrain terr = {0,0,90,90};
	if (donnees_ok(l_salle,terr)){
		cout << "Les données du fichier d'entrée sont valides" << endl;
	}
	else{
		cout << "Les données du fichier d'entrée ne sont pas valides" << endl;
	}
}
