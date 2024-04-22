#include "tictactoe.h"
#include <iostream>
using namespace std;


TicTacToe::TicTacToe(){                     // CONSTRUCTEUR
    for(int i=0;i<3;i++){                   // INITIALISATION DE LA GRILLE DE JEU A 0
        for(int j=0;j<3;j++){               
            T[i][j]=0;                      
        }
    }
}


void TicTacToe::affichage(){                // AFFICHAGE DE LA GRILLE DE JEU
    for (int i = 0; i < 3; i++) {         
        for (int j = 0; j < 3; j++) {   
            cout << T[i][j];
            if (j < 2) {

                cout << " | ";
            }
        }
        cout << endl;
        if (i < 2) {
            cout << "---------" << endl;
        }
    }
}


bool TicTacToe::plein(){                    // VERIFIE SI LA GRILLE EST PLEINE
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3 ; j++){
            if(vide(i*3+j)) return false;   // SI UNE CASE EST VIDE RETOURNE FALSE                                             
        }                                   // (LA GRILLE N'EST PAS PLEINE)
    }   
    return true;              
}


bool TicTacToe::victoire(int joueur){
    for(int i = 0; i < 3; i++){             // TRAITEMENT DES LIGNES
        if(T[i][0] == T[i][1] && T[i][1] == T[i][2] && T[i][0] == joueur){
            return true;
        }
    }
    for(int i = 0; i < 3; i++){             // TRAITEMENT DES COLONNES
        if(T[0][i] == T[1][i] && T[1][i] == T[2][i] && T[0][i] == joueur){
            return true;
        }
    }                                       // TRAITEMENT DES DIAGONALES
    if(T[0][0] == T[1][1] && T[1][1] == T[2][2] && T[0][0] == joueur){
        return true;
    }
    if(T[0][2] == T[1][1] && T[1][1] == T[2][0] && T[0][2] == joueur){
        return true;
    }
    return false;
}


bool TicTacToe::vide(int pos) {             // VERIFIE SI UNE CASE EST VIDE
    int i = pos / 3;
    int j = pos % 3;
    return T[i][j] == 0;
}


void TicTacToe::jouer(int pos, int joueur){ // JOUE UN COUP
    int i = pos / 3;
    int j = pos % 3;
    T[i][j] = joueur;
}


void TicTacToe::retourarriere(int pos){     // RETOUR EN ARRIERE
    int i = pos / 3;
    int j = pos % 3;
    T[i][j] = 0;
}


bool TicTacToe::occupe(int pos) {           // VERIFIE SI UNE CASE EST OCCUPEE
    return !vide(pos);                  
}


int TicTacToe::JeuOrdi(int &bestMove) {     // ALGORITHME MINIMAX JEUORDI
    int arg = 9999;                         // ARGUMENT DE LA FONCTION

    if (plein()) {                              
        return 0;
    }

    if (victoire(-1)) {                     
        return -1000;
    }

    int val = -1;

    for (int i = 0; i < 9; i++) {           // PARCOURS DE LA GRILLE
        if (vide(i)) {                      // SI LA CASE EST VIDE
            jouer(i, 1);                    // JOUE UN COUP
            int res = JeuHumain(arg);       // APPEL RECURSIF DE LA FONCTION JEUHUMAIN         
            retourarriere(i);               // RETOUR EN ARRIERE

            if (res > val) {                // SI LE RESULTAT EST SUPERIEUR A LA VALEUR
                val = res;                  // ON AFFECTE LA VALEUR AU RESULTAT 
                bestMove = i;               // ET ON AFFECTE LA CASE A JOUER A LA CASE COURANTE
            }
        }
    }

    return val;
}


int TicTacToe::JeuHumain(int &bestMove) {   // ALGORITHME MINIMAX JEUHUMAIN
    int arg = -9999;                        // ARGUMENT DE LA FONCTION

    if (plein()) {
        return 0;
    }

    if (victoire(1)) {
        return +1000;
    }

    int val = 1;

    for (int i = 0; i < 9; i++) {           // PARCOURS DE LA GRILLE
        if (vide(i)) {                      // SI LA CASE EST VIDE
            jouer(i, -1);                   // JOUE UN COUP
            int res = JeuOrdi(arg);         // APPEL RECURSIF DE LA FONCTION JEUORDI
            retourarriere(i);               // RETOUR EN ARRIERE

            if (res < val) {                // SI LE RESULTAT EST INFERIEUR A LA VALEUR
                val = res;                  // ON AFFECTE LA VALEUR AU RESULTAT
                bestMove = i;               // ET ON AFFECTE LA CASE A JOUER A LA CASE COURANTE
            }
        }
    }

    return val;
}


int TicTacToe::arbitre(){                   // ARBITRE LA PARTIE
    if(victoire(1)){                        // SI L'ORDINATEUR GAGNE
        cout << "ETAT : L'ORDINATEUR A GAGNE" << endl;
        return 1;                           // RETOURNE 1
    }
    if(victoire(-1)){                       // SI L'HUMAIN GAGNE
        cout << "ETAT : L'HUMAIN A GAGNE" << endl;
        return -1;                          // RETOURNE -1
    }
    if(plein()){                            // SI LA GRILLE EST PLEINE
        cout << "ETAT : MATCH NUL" << endl;
        return 0;                           // RETOURNE 0
    }
    else {                                  // LA PARTIE CONTINUE             
        cout << "ETAT : LA PARTIE CONTINUE" << endl;
        return -2;                          // RETOURNE -2
    }
}