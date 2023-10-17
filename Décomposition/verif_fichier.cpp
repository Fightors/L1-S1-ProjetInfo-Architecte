#include <iostream>
#include <fstream>
#include <string>
#include "liste.hpp"
using namespace std;

void verif_fichier(string nom_fichier){
    fstream flux;
    flux.open(nom_fichier, ios::in);
    if (flux.is_open(){
        while (flux.getline(flux, line)){
            flux.iss(line);
            int x1,y1,x2,y2;
            if (!(iss >> x1 >> y1>> x2>> y2)) { 
                break; // error
            } 
        }
    flux.close();
    }
    else{
    gen_fichier(nom_fichier);
    }
}