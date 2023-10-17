/*
Programme d'exemple d'utilisation de fichiers 

  
*/
#include <iostream>
#include <fstream>
#include "liste.hpp"
using namespace std;

struct Bizarre{
    string numero, valeur;
    int x, y;
};

int lire_entiers(string nom_fic){
  fstream flux; 
  
  int nb, total;

  total = 0;

  flux.open(nom_fic, ios::in);
  if (flux.is_open()) {
    flux >> nb;  // première lecture avant le tant que
    while (flux.good()) { // vérification que la lecture a été effectuée correctement
       total = total + nb;  // traitement d'un élément en étant sûr que la lecture s'est bien passée 
       flux >> nb;  // lecture du suivant, déclenchant  possiblement une erreur rendant flux.good() faux 
    }
    flux.close();   
  }
  else {
    cout << "Erreur : impossible d'ouvrir " << nom_fic << endl;
  }
  return total;
}

// Rôle : sous algo d'illustration écrivant des entiers dans un fichier

void ecrire_entiers(string nom_fic){
    fstream flux; 
    int nb = 0;
    flux.open(nom_fic, ios::out);
    if (flux.is_open()) {
    
       while (nb < 200) {
           flux << nb << " ";
           nb += 10;
       }
       flux.close();   
   }
   else {
       cout << "Erreur : impossible d'ouvrir " << nom_fic << endl;
   }
}

// Rôle : programme principal utilisant lire_entiers et ecrire_entiers en en demandant les paramètres à l'utilisateur
int main(){
  
  string nom_fichier;
  int cumul;
  
  cout << "nom du fichier d'entiers a ouvrir" << endl;
  cin >> nom_fichier;
  cumul = lire_entiers(nom_fichier);
  cout << "somme des entiers lus : "<< cumul << endl;
 
  cout << "nom du fichier d'entiers a creer" << endl;
  cin >> nom_fichier;
  ecrire_entiers(nom_fichier);
  
  cout << "Ecriture terminée : "<< endl;
}
