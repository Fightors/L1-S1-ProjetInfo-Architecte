
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

void stockage_données(string nom_fic, & Terrain :terrain , & liste<salle> : liste_salle){
    fstream flux ;

    int nb, total;
    struct terrain;
    total = 0;
    flux.open(nom_fic, ios::in);
    if (flux.is_open()) {
        flux >> nb;  // première lecture avant le tant que
        while (flux.good()) { // vérification que la lecture a été effectuée correctement
            total = total + nb;  // traitement d'un élément en étant sûr que la lecture s'est bien passée 
            flux >> nb;  // lecture du suivant, déclenchant  possiblement une erreur rendant flux.good() faux 
            terrain.x1 = flux;
        }
        flux.close();   
    }
    else {
    cout << "Erreur : impossible d'ouvrir " << nom_fic << endl;
    }
     return total;
}