#include <iostream>
#include <fstream>
#include <string>
#include "liste.hpp"
using namespace std;
struct surf_tot_lvl{
    int lvl,surf;
};

void verif_fichier(int h_max,int nb_salles, int surf_tot, liste<surf_tot_lvl> l_surf_tot_lvl, string & fichierstat){
    fstream flux;
    flux.open(fichierstat, ios::out);
    if (flux.is_open()){
        flux << "Hauteur maximal : " << h_max << endl ;
        flux << "Nombre de salles : " <<  nb_salles << endl ;
        flux << "Surface totale : " << surf_tot << endl ;
        flux << "Surface total par niveau : " << endl ;
        for ( surf_tot_lvl stl : l_surf_tot_lvl){
            flux <<"niveau "<< stl.lvl << " : " << stl.surf << endl;
        }
        flux.close();
    }
     else {
       cout << "Erreur : impossible d'ecrire dans le fichier " << fichierstat << endl;
    }
}