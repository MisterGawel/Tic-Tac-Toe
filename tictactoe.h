class TicTacToe {

public:
    int T[3][3];

    TicTacToe();
    bool plein();
    bool victoire(int joueur);
    void affichage();
    bool vide(int position);
    void jouer(int position, int joueur);
    void retourarriere(int position);
    bool occupe(int position);
    int JeuOrdi(int & bestMove);
    int JeuHumain(int & bestMove);
    int arbitre();
};