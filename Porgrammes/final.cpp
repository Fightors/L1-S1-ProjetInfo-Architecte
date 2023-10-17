#include <iostream>
#include <fstream>
#include <string> 
#include <stdlib.h>
#include <time.h>  
#include "liste.hpp"
using namespace std;

// Définition des Enregistrements utilisés dans l'ensemble du programme

struct Terrain{
    int x1,y1,x2,y2;
};

struct Salle{
    int lvl=0,x1,y1,x2,y2;
};

struct Poteau{
    int x1,y1,z1,z2;
};

// Procédure qui génère un fichier txt conforme si le nom de fichier renseigné précedemment ne correspond 
// à aucun fichier .txt existant dans le dossier des programmes

void gen_fichier(string nom_fichier){
	srand (int(time(NULL))); 
    fstream flux;
    int tx1 = 0 ,ty1 = 0,tx2 = rand()%100+1,ty2 =rand()%100+1;
    int sx1,sy1,sx2,sy2;
    int nbr_salles = rand()%10+1;
    int cpt = 0;
    
// Ouverture du fichier en écriture

    flux.open(nom_fichier, ios::out);
    if (flux.is_open()){
        flux << tx1 << " " << ty1 << " " << tx2 << " " << ty2 << endl;
        while(cpt < nbr_salles){
            sx1= rand()%100; 
            sy1= rand()%100;
            sx2= rand()%tx2;
            sy2= rand()%ty2;
            while( !(sx1<sx2 && sy1<sy2)){
                sx1= rand()%100; 
                sy1= rand()%100;
                sx2= rand()%tx2;
                sy2= rand()%ty2;
            }
            flux << sx1 << " " << sy1 << " " << sx2 << " "<< sy2 << endl;
            cpt++;
        }
        flux.close();
        
    }
    else {
       cout << "Erreur : impossible d'ecrire dans le fichier " << nom_fichier << endl;
    }
}

// Procédure qui ouvre un fichier texte et stock les données contenues dans ce fichier à l'intérieur
// des variables utilisées dans l'ensemble du programme.

void stockage_donnee(string nom_fichier,Terrain & trn, liste<Salle> & l_salle ){
	fstream flux;
	Salle sle;

//Ouverture du fichier en lecture

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
		    gen_fichier(nom_fichier);
            stockage_donnee(nom_fichier, trn, l_salle);
		}
 }

// Procédure qui vérifie la validité des données contenus dans les variables 
// ( salle non-nul, salles contenus dans le terrain, ...)

bool donnees_ok(liste<Salle> liste_s, Terrain trn){
	for ( Salle sle : liste_s){
		if (trn.x1>sle.x1 or trn.y1>sle.y1 or trn.x2<sle.x2 or trn.y2<sle.y2 or trn.x1!=0 or trn.y1!=0 or trn.x2 <= 0 or trn.y2 <= 0 or sle.x1 < 0 or sle.y1 < 0 or sle.x2 < 1 or sle.y2 < 1){
			return false;
		}
	}
	return true;
}


// Fonction qui vérifie si deux salles passées en paramètre se superposent.

bool superposition ( Salle s1, Salle s2 ){
	return not (s2.x1 >= s1.x2 or s2.y1 >= s1.y2 or s2.x2 <= s1.x1 or s2.y2 <= s1.y1 or (s2.x1 >= s1.x2 and s2.y1 >= s1.y2 and s2.x2 <= s1.x1 and s2.y2 <= s1.y1)); 
}

// Procédure qui vérifie si les salles d'une liste de salle passée 
// en argument se superposent ( grâce à Superposition ), et calcule son niveau.

void disposition_salles(liste<Salle> & liste_salle ){
    for ( unsigned int i=2; i<= taille(liste_salle); i+=1 ){
        for ( unsigned int j=2; j<=i; j+=1 ){
			if ( superposition ( liste_salle[i], liste_salle[j-1] ) ){
				liste_salle[i].lvl=liste_salle[j-1].lvl+1;
            }
        }
    }
}

// Procédure qui défini les poteaux existants, puis les trie selo les conditions 
// ( à retrouver dans le sujet )

void disposition_poteaux( liste<Salle> & l_salle, liste<Poteau> & l_poteau, int & eco_poteaux ){
    long unsigned int cpt_ptx = 1;

// Création de tous les poteaux possibles autour de chaques salles à partir du niveau 1 
// avec un niveau en z1 à 0

    for ( Salle sle : l_salle){
        if (sle.lvl != 0){
            inserer(l_poteau, {sle.x1,sle.y1,0,sle.lvl*10}, taille(l_poteau)+1);
            inserer(l_poteau, {sle.x1,sle.y2,0,sle.lvl*10}, taille(l_poteau)+1);
            inserer(l_poteau, {sle.x2,sle.y1,0,sle.lvl*10}, taille(l_poteau)+1);
            inserer(l_poteau, {sle.x2,sle.y2,0,sle.lvl*10}, taille(l_poteau)+1);
        }
    }

// Calcul et implantation du z1 pour chaques poteaux

    for ( Poteau ptx : l_poteau){
        for (long unsigned int cpt=taille(l_salle) ; cpt >= 1 ; cpt-- ){
            if (ptx.x1 >= l_salle[cpt].x1 and 
				ptx.x1 <= l_salle[cpt].x2 and 
				ptx.y1 >= l_salle[cpt].y1 and 
				ptx.y1 <= l_salle[cpt].y2){
                if (l_salle[cpt].lvl*10 < ptx.z2) {
                    l_poteau[cpt_ptx].z1 = l_salle[cpt].lvl*10+10;
                }
            }
        }
        cpt_ptx+=1;
    }

// Suppression des poteaux dont la longueur est nulle

    cpt_ptx = 1;
    while ( cpt_ptx <= taille (l_poteau)){
        if (l_poteau[cpt_ptx].z1==l_poteau[cpt_ptx].z2){
            supprimer(l_poteau, cpt_ptx);
        }
        cpt_ptx+=1;
    }

// Marquage des poteaux qui ont une distance de 3 pixels ou moins avec la salle du niveau inférieur

    cpt_ptx = 1;
    while ( cpt_ptx <= taille(l_poteau)){
        for ( Salle sle : l_salle){
            if ( (l_poteau[cpt_ptx].z2-10)/10 == sle.lvl){
                if ( (l_poteau[cpt_ptx].x1-sle.x2 <=3 and l_poteau[cpt_ptx].x1-sle.x2 > 0 and l_poteau[cpt_ptx].y1-sle.y2 <=3) or
                     (l_poteau[cpt_ptx].y1-sle.y2 <=3 and l_poteau[cpt_ptx].y1-sle.y2 > 0 and sle.x1-l_poteau[cpt_ptx].x1 <=3) or
                     (sle.x1-l_poteau[cpt_ptx].x1 <=3 and sle.x1-l_poteau[cpt_ptx].x1 > 0 and sle.x1-l_poteau[cpt_ptx].y1 <=3) or
                     (sle.x1-l_poteau[cpt_ptx].y1 <=3 and sle.x1-l_poteau[cpt_ptx].y1 > 0 and l_poteau[cpt_ptx].x1-sle.x2 <=3) ){
                        eco_poteaux = eco_poteaux + (l_poteau[cpt_ptx].z2-l_poteau[cpt_ptx].z1);
                        l_poteau[cpt_ptx] = {-1,-1,-1,-1};
                }
            }
        }
        cpt_ptx +=1 ;
    }

//Suppression des poteaux invalides

    for ( long unsigned int cpt=taille(l_poteau) ; cpt >= 1 ; cpt-- ){
        if (l_poteau[cpt].x1 == -1) {
            supprimer ( l_poteau , cpt );
        }
    }
}

// Procédure qui calcul la longueur totale des poteaux 

void calcul_long_poteau ( int & long_poteaux, liste<Poteau> & l_poteau){
    for ( Poteau ptx : l_poteau ){
        long_poteaux=long_poteaux + ( ptx.z2 - ptx.z1 );
    }
}

// Procédure qui créer un fichier texte et renseigne les différentes valeurs 
// conformément à la structure émise dans l'énoncé

void ecriture_fichier(Terrain trn,liste<Salle> liste_salle, liste<Poteau> liste_poteaux, int long_poteau, int eco_poteau,string  nom_fichier){
    fstream flux;

    flux.open(nom_fichier, ios::out);
    if (flux.is_open()){
        flux << "terrain : " << trn.x1 <<", " << trn.y1 <<", " << trn.x2 <<", " << trn.y2 << endl;
        flux << "salles " << taille(liste_salle) << endl;
        for ( long unsigned int i = taille(liste_salle); i>=1; i--){
            flux << liste_salle[i].lvl << " : "<< liste_salle[i].x1 << ", "<< liste_salle[i].y1 << ", "<< liste_salle[i].x2 << ", "<< liste_salle[i].y2 << endl;
            }
        flux << "poteaux " << taille(liste_poteaux) << endl;
        for ( long unsigned int j = taille(liste_poteaux); j>=1; j--){
            flux << liste_poteaux[j].x1 << ", "<< liste_poteaux[j].y1 << ", "<< liste_poteaux[j].z1 << ", "<< liste_poteaux[j].z2 << endl;
            }
        flux << "longueur_poteaux : " << long_poteau << endl;
        flux << "economie_poteaux : " << eco_poteau << endl;
        flux.close();   
    }
    else {
       cout << "Erreur : impossible d'ecrire dans le fichier " << nom_fichier << endl;
    }
}

//Procédure qui calcul différentes statistiques comme
// la hauteur maximale, le nombre de salle, la surface totale de salles puis par niveau

void calcul_stats( liste<Salle> l_salle , int & h_max, int & nb_salles , int & surf_tot , liste<int> & l_surf_tot_lvl ){

// Calcul de la hauteur max

	h_max = 10;
	for ( Salle sle : l_salle ) {
		if (sle.lvl*10 + 10  > h_max ){
			h_max = sle.lvl*10 + 10;
			}
	}

// Calcul du nombre de salle

	nb_salles = int (taille(l_salle));
	
// Calcul de la surface totale
	
	for ( Salle sle : l_salle ) {
		surf_tot = surf_tot + (sle.x2-sle.x1)*(sle.y2-sle.y1);
	}

// Création de la liste surf tot par niveau de 0 à niv_max

	int niv_max =  (h_max -10) /10;
	for (int cpt = 1; cpt <= niv_max + 1 ; cpt ++){
		inserer(l_surf_tot_lvl,0,cpt);
	}
	
// Instanciation liste regroupant la surface totale par niveau
	
	for ( Salle sle : l_salle) {
		l_surf_tot_lvl[sle.lvl+1] = l_surf_tot_lvl[sle.lvl+1] + (sle.x2-sle.x1)*(sle.y2-sle.y1);
	}
}

// Procédure qui créer un fichier texte et renseigne les statistiques
// calculées précedemment dans la forme décrite dans l'énoncé

void ecriture_stats(int h_max,int nb_salles, int surf_tot, liste<int> l_surf_tot_lvl, string & fichierstats){
    fstream flux;
    flux.open(fichierstats, ios::out);
    if (flux.is_open()){
        flux << "Hauteur maximale : " << h_max << endl ;
        flux << "Nombre de salles : " <<  nb_salles << endl ;
        flux << "Surface totale : " << surf_tot << endl ;
        flux << "Surface totale par niveau : " << endl ;
        int cpt = 0;
        for ( int stl : l_surf_tot_lvl){
            flux <<"    - niveau "<< cpt << " : " << stl << endl;
            cpt++;
        }
        flux.close();
    }
     else {
       cout << "Erreur : impossible d'ecrire dans le fichier " << fichierstats << endl;
    }
}

// Début de l'execution du programme

int main (){

// Initialisations des variables

string nom_fichier = "donnees.txt" ;
string nom_stats = "donnees.stats.txt";
string nom_fichier_out = "donnees.out.txt";
Terrain trn;
liste<Salle> l_salle;
liste<Poteau> l_poteau;
liste<int> l_surf_tot_lvl;	
int eco_poteau=0;
int long_poteau=0;
int h_max=0;
int nb_salles=0;
int surf_tot=0;

// Appel des sous-programmes

stockage_donnee(nom_fichier, trn, l_salle);
assert(donnees_ok(l_salle,trn) != false);

// Initialisation du niveau des salles à 0 pour éviter une génération de valeurs aléatoires 
// lors de la disposition des salles

for ( Salle sle:l_salle){
    sle={0,sle.x1,sle.y1,sle.x2,sle.y2};
}
disposition_salles(l_salle);
disposition_poteaux(l_salle, l_poteau, eco_poteau);
calcul_long_poteau(long_poteau, l_poteau);
ecriture_fichier( trn, l_salle, l_poteau, long_poteau, eco_poteau, nom_fichier_out );
calcul_stats( l_salle, h_max, nb_salles , surf_tot, l_surf_tot_lvl );
ecriture_stats( h_max, nb_salles, surf_tot, l_surf_tot_lvl, nom_stats);

// Fin de l'exécution du programme

}

