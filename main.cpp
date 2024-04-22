#include <iostream>
#include <ctime>    
#include <chrono>
#include <thread>
#include <unistd.h>
#include "tictactoe.h"
using namespace std;

int main(int argc, char const *argv[])
{
    system("cls");
    srand(time(NULL));
    TicTacToe partie;
    cout << "Voulez-vous commencez une partie ? (O/N) : ";
    
    char reponse;
    cin >> reponse;
    system("cls");
    int piece = rand() % 2;

    if(reponse == 'O');
    else return 0;

    cout << "--------------------------------------------" << endl << endl;
    cout << "La piece est : " << piece << endl;
    if(piece == 0) cout << "Ce sera l'ordinateur qui jouera le premier" << endl;
    else cout << "Ce sera le joueur qui jouera le premier" << endl;
    cout << endl << "** Voici notre MORPION de depart **" << endl << endl;
    partie.affichage();
    cout << endl;
    cout << "--------------------------------------------" << endl << endl;
    for (int i = 10; i >= 0; --i) {
        cout << "\rLa partie va demarrer dans : " << i << " ";  
        cout.flush();  
        this_thread::sleep_for(chrono::seconds(1));
    }
    system("cls");

    cout << endl << "------------ LA PARTIE COMMENCE ------------" << endl << endl;
    if(piece == 0){
        while(partie.arbitre() == -2){

            cout << "C'est au tour de l'ordinateur de jouer : " << endl << endl;
            int bestMove;
            partie.JeuOrdi(bestMove);
            partie.jouer(bestMove, 1);
            partie.affichage();
            cout << endl;

            if(partie.arbitre() != -2) break;

            cout << "C'est au tour de l'humain de jouer : ";
            int position = 0;
            cin >> position;
            if(partie.occupe(position) ||  position > 9 || position < 0){
                while(partie.occupe(position)){
                    cout << "Mauvaise case : " << endl;
                    cin >> position;
                    continue;
                }
            }
            cout << endl;
            partie.jouer(position, -1);
            partie.affichage();
            cout << endl;
            system("cls");

        }
    }
    else if(piece == 1){
        while(partie.arbitre() == -2){

            cout << "C'est au tour de l'humain de jouer : ";
            int position = 0;
            cin >> position;
            if(partie.occupe(position) ||  position > 9 || position < 0){
                while(partie.occupe(position)){
                    cout << "Mauvaise case : " << endl;
                    cin >> position;
                    continue;
                }
            }
            partie.jouer(position, -1);
            partie.affichage();
            system("cls");
            cout << endl;
            if(partie.arbitre() != -2) break;

            cout << "C'est au tour de l'ordinateur de jouer : " << endl << endl;
            int bestMove = 0;
            partie.JeuOrdi(bestMove);
            partie.jouer(bestMove, 1);
            partie.affichage();
            cout << endl;
            

        }            
    }
    return 0;
}
