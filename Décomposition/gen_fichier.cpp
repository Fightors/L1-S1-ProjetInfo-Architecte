#include <iostream>
#include <fstream>
#include <string> 
#include "liste.hpp"
using namespace std;

void gen_fichier(string & nom_fichier){
    fstream flux;
    int tx1 = 0 ,ty1 = 0,tx2 = rand()%100,ty2 =rand()%100;
    int sx1,sy1,sx2,sy2;
    int nbr_salles = rand()%11;
    int cpt = 0;

    flux.open(nom_fichier, ios::out);
    if (flux.is_open()){
        flux << tx1 << " " << ty2 << " " << tx2 << " "<< ty2 << endl;
        while(cpt <= nbr_salles){
            sx1= rand()%100; 
            sy1= rand()%100;
            sx2= rand()%100;
            sy2= rand()%100;
            while( !(sx1<sx2 && sy1<sy2 && sx2<=tx2 && sy2<=ty2)){
                sx1= rand()%100; 
                sy1= rand()%100;
                sx2= rand()%100;
                sy2= rand()%100;
            }
            flux << sx1 << " " << sy2 << " " << sx2 << " "<< sy2 << endl;
            cpt++;
        }
        flux.close();
    }
    else {
       cout << "Erreur : impossible d'ecrire dans le fichier " << nom_fichier << endl;
    }
}