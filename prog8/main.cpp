#include "En-têtes/params.h"
#define FPS_LIMIT 60

//bibliotheque c++
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <map>

//Mingl 2
#include "mingl/mingl.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/rectangle.h"
#include "mingl/gui/sprite.h"

//En-tetes
#include "En-têtes/pacman.h"
#include "En-têtes/type.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;
using namespace chrono;
using namespace this_thread;
using namespace nsGui;

Vec2D PacmanPos;
CMyParam Param;


void matriceInitPacman(vector <vector <char>> & matriceMap) /*source: Maxime TAMARIN*/
{
    matriceMap = {{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}, // X : mur , 0 : chemin avec pièce, - : porte fantome, ' ' : chemin sans pièce
                  {'X','0','0','0','0','0','0','X','0','0','0','0','0','0','X',}, // * : pouvoir parcman sur 10s
                  {'X','0','X','0','X','X','0','X','0','X','X','*','X','0','X',}, // / : intersection
                  {'X','0','*','0','0','0','0','0','0','*','0','0','0','0','X',},
                  {'X','0','X','X','X','X','X','0','X','X','X','X','X','0','X',},
                  {'X','0','0','0','0','*','0','0','0','0','0','0','0','0','X',},
                  {'X','X','0','X','0','X','X','-','X','X','0','X','0','X','X',},
                  {'0','0','0','X','0','X',' ',' ',' ','X','0','X','0','0','0',}, //millieu
                  {'X','0','X','X','0','X',' ',' ',' ','X','*','X','X','0','X',},
                  {'X','0','0','X','0','X','X','X','X','X','0','X','0','0','X',},
                  {'X','X','0','0','*','X','0','0','0','X','0','0','0','X','X',},
                  {'X','X','0','X','0','0','*','X','0','0','0','X','*','X','X',},
                  {'X','X','*','X','X','X','0','X','0','X','X','X','0','X','X',},
                  {'X','X','0','0','0','0','0','0','0','0','0','0','0','X','X',},
                  {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}};

}

void matriceInitFantome(vector <vector <char>> & matriceMap) /*source: Maxime TAMARIN*/
{
    matriceMap = {{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}, // X : mur , - : porte fantome, ' ' : chemin sans pièce
                  {'X','/',' ','/',' ',' ','/','X','/',' ',' ','/',' ','/','X',}, // / : intersection
                  {'X',' ','X',' ','X','X',' ','X',' ','X','X',' ','X',' ','X',}, // . : sorti de la cage (direction mise à "haut")
                  {'X','/',' ','/',' ',' ','/','/','/',' ',' ','/',' ','/','X',},
                  {'X',' ','X','X','X','X','X',' ','X','X','X','X','X',' ','X',},
                  {'X','/','/',' ','/',' ',' ','/',' ',' ','/',' ','/','/','X',},
                  {'X','X',' ','X',' ','X','X','-','X','X',' ','X',' ','X','X',},
                  {' ','/','/','X',' ','X',' ','.',' ','X',' ','X','/','/',' ',}, //millieu
                  {'X',' ','X','X',' ','X',' ',' ',' ','X',' ','X','X',' ','X',},
                  {'X','/','/','X',' ','X','X','X','X','X',' ','X','/','/','X',},
                  {'X','X','/',' ','/','X','/',' ','/','X','/',' ','/','X','X',},
                  {'X','X',' ','X','/',' ','/','X','/',' ','/','X',' ','X','X',},
                  {'X','X',' ','X','X','X',' ','X',' ','X','X','X',' ','X','X',},
                  {'X','X','/',' ',' ',' ','/',' ','/',' ',' ',' ','/','X','X',},
                  {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}};

}

void afficheMat(vector <vector< char>> & mat) /*source: Maxime TAMARIN*/
{
    for (unsigned y = 0; y < mat.size(); ++y)
    {
        for (unsigned x = 0; x < mat[y].size(); ++x)
        {
            cout << mat[y][x];
        }
        cout << endl;
    }
}

void afficheMap(MinGL &window, vector <vector <char>> & mat,unsigned & pointMap) /*source: Maxime TAMARIN*/
{
    pointMap = 0;
    for (unsigned y = 0; y < mat.size(); ++y)
    {
        for (unsigned x = 0; x < mat[y].size(); ++x)
        {
            if (mat[y][x] == 'X')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorMur")->second);
            }

            else if (mat[y][x] == '0')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorChemin")->second);
                window << Circle(Vec2D(x*50+25,y*50+25), 5, Param.MapParamString.find("ColorPiece")->second);

                ++pointMap;
            }
            else if (mat[y][x] == '-')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorChemin")->second);
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+20), Param.MapParamString.find("ColorPorte")->second);

            }
            else if (mat[y][x] == ' ')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorChemin")->second);
            }

            else if (mat[y][x] == '*')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorChemin")->second);
                window << Circle(Vec2D(x*50+25,y*50+25), 13, Param.MapParamString.find("ColorPiece")->second);

                ++pointMap;
            }
        }
    }
}

bool verificationCollision(vector <vector <char>> & mat, string & direction) /*Source: Maxime TAMARIN*/
{
    // regarde le haut
    if (direction == "haut")
    {
        if (mat[(PacmanPos.getY()-24)/50][PacmanPos.getX()/50] == 'X')
            return false;
        if (mat[(PacmanPos.getY()-24)/50][PacmanPos.getX()/50] == '-')
            return false;
        return true;
    }

    //regarde le bas
    if (direction == "bas")
    {
        if (mat[(PacmanPos.getY()+24)/50][PacmanPos.getX()/50] == 'X')
            return false;
        if (mat[(PacmanPos.getY()+24)/50][PacmanPos.getX()/50] == '-')
            return false;
        return true;
    }

    //regarde la droite
    if (direction == "droite")
    {
        if (mat[PacmanPos.getY()/50][(PacmanPos.getX()+25)/50] == 'X')
            return false;
        if (mat[PacmanPos.getY()/50][(PacmanPos.getX()+25)/50] == '-')
            return false;
        return true;
    }

    //regarde la droite
    if (direction == "gauche")
    {
        if (mat[PacmanPos.getY()/50][(PacmanPos.getX()-24)/50] == 'X')
            return false;
        if (mat[PacmanPos.getY()/50][(PacmanPos.getX()-24)/50] == '-')
            return false;
        return true;
    }
    return false; // au cas normalement non possible ou direction a une autre valeur
}

void deplacementPacman(MinGL & window, string & direction,vector <vector <char>> & mat,bool & pouvoirPacman) /* source: Alain casali + Maxime TAMARIN*/
{
    if (mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] == '*')
        pouvoirPacman = true;

    if ((PacmanPos.getX()+55)/50 == 0) // téléporte le pacman à droite
        PacmanPos.setX(800);

    if ((PacmanPos.getX()-55)/50 == 15) // téléporte le pacman à gauche
        PacmanPos.setX(0);

    if (verificationCollision(mat,direction))
    {

        // On vérifie si ZQSD est pressé, et met a jour la position et la direction
        if (window.isPressed({Param.MapParamChar.find("KeyUp")->second, false})) // regarde si prochaine case n'est pas interdite
        {
            direction = "haut";
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setY(PacmanPos.getY() - 3);
            else
                PacmanPos.setY(PacmanPos.getY() - 2);
        }
        else if (window.isPressed({Param.MapParamChar.find("KeyDown")->second, false}))
        {
            direction = "bas";
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setY(PacmanPos.getY() + 3);
            else
                PacmanPos.setY(PacmanPos.getY() + 2);
        }
        else if (window.isPressed({Param.MapParamChar.find("KeyLeft")->second, false}))
        {
            direction = "gauche";
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setX(PacmanPos.getX() - 3);
            else
                PacmanPos.setX(PacmanPos.getX() - 2);
        }
        else if (window.isPressed({Param.MapParamChar.find("KeyRight")->second, false}))
        {
            direction = "droite";
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setX(PacmanPos.getX() + 3);
            else
                PacmanPos.setX(PacmanPos.getX() + 2);
        }
        // si pas de touche pressé on continue à aller dans la même direction
        else if (direction == "haut")
        {
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setY(PacmanPos.getY() - 3);
            else
                PacmanPos.setY(PacmanPos.getY() - 2);
        }
        else if (direction == "bas" )
        {
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setY(PacmanPos.getY() + 3);
            else
                PacmanPos.setY(PacmanPos.getY() + 2);
        }
        else if (direction == "gauche")
        {
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setX(PacmanPos.getX() - 3);
            else
                PacmanPos.setX(PacmanPos.getX() - 2);
        }
        else if (direction == "droite")
        {
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setX(PacmanPos.getX() + 3);
            else
                PacmanPos.setX(PacmanPos.getX() + 2);
        }
    }
    else
    {
        //si bloqué dans un mur
        if (direction == "haut")
        {
            PacmanPos.setY(PacmanPos.getY() + 1);
        }
        else if (direction == "bas")
        {
            PacmanPos.setY(PacmanPos.getY() - 1);
        }
        else if (direction == "droite")
        {
            PacmanPos.setX(PacmanPos.getX() - 1);
        }
        else if (direction == "gauche")
        {
            PacmanPos.setX(PacmanPos.getX() + 1);
        }
    }
}


int main()  /* source: Alain casali + Maxime TAMARIN*/
{
    // Initialise le système
    MinGL window("SAE 1.02", Vec2D(750, 750), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();

//=====| Initialisation Map |=====

    vector <vector <char>> map;
    matriceInitPacman(map);
    afficheMat(map);

//=====| Initialisation struct des fantomes |=====

    struct fantome
    {
        string direction;
    };

//=====| Initialisation Pacman |=====

    //Initialise la position du pacman
    PacmanPos.setX(75);
    PacmanPos.setY(75);

    //Initialise la bouche du pacman à false
    bool boucheOuverte = false;

    //Initialisation direction pacman
    string direction = "droite";

    //Initialisation pouvoir pacman à false
    bool pouvoirPacman = false;
    unsigned PouvoirTemp = 1;

//=====| Initialisation Fantome |=====

    //initialisation des fantomes via le struct
    fantome fantome1;
    fantome fantome2;
    fantome fantome3;

    //initialisation vec2D
    Vec2D fantome1Pos;
    Vec2D fantome2Pos;
    Vec2D fantome3Pos;

    //Initialise la position du fantome
    fantome1Pos.setX(325);
    fantome1Pos.setY(375);

    fantome2Pos.setX(375);
    fantome2Pos.setY(325);

    fantome3Pos.setX(275);
    fantome3Pos.setY(325);

    //Initialise la directionc
    fantome1.direction = "haut";
    fantome2.direction = "gauche";
    fantome3.direction = "droite";

//=====| Autre Initialisation |=====

    //initialisation paramètre
    InitParams(Param);

    // nombre de point sur la map (quand = 0 fin)
    unsigned pointMap;

    // frame = nombre d'execution (comme 60FPS alors 60 execution / seconde)
    unsigned frame = 0;

    // Variable qui tient le temps de frame
    microseconds frameTime = microseconds::zero();

//=====| Boucle infini de la fenêtre |=====

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        time_point<steady_clock> start = steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On execute les processus

        afficheMap(window,map,pointMap); //affiche le visuel de la map

        deplacementPacman(window,direction,map,pouvoirPacman); //regarde les touches appuyées et si la direction du pacman doit changer ou non

        affichePacman(PacmanPos.getX(),PacmanPos.getY(),window, boucheOuverte,direction,pouvoirPacman,Param); // affiche pacman en fonction d'une position
        if (frame%15 == 0) // toute les 15 execution (1/4 de seconde) on change l'état de la bouche
            boucheOuverte = !boucheOuverte;

        if (pointMap == 0) //quand plus de point sur la map à manger
            matriceInitPacman(map);

        if (pouvoirPacman)
        {
            if (PouvoirTemp%360 == 0) // 360 images = 6 secondes
            {
                pouvoirPacman = false;
                PouvoirTemp = 1;
            }
            else
                ++PouvoirTemp;
        }

        //affichage console
        cout << "X: " << PacmanPos.getX()/50 << " Y: " << PacmanPos.getY()/50 << endl; // coordonée
        cout << "point restant: " <<pointMap << endl; // point restant sur la map à manger
        cout << "statut pouvoir pacman: " <<pouvoirPacman << endl << endl;

        //instancie sprite
        Sprite fantome1("../prog8/autre fichier/fantome4.si2", Vec2D(fantome1Pos.getX()+25,fantome1Pos.getY()+25 ));
        Sprite fantome2("../prog8/autre fichier/fantome4.si2", Vec2D(fantome2Pos.getX()+25,fantome2Pos.getY()+25 ));
        Sprite fantome3("../prog8/autre fichier/fantome4.si2", Vec2D(fantome3Pos.getX()+25,fantome3Pos.getY()+25 ));
        window << fantome1 << fantome2 << fantome3;

        ++frame;

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        sleep_for(milliseconds(1000 / FPS_LIMIT) - duration_cast<microseconds>(steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = duration_cast<microseconds>(steady_clock::now() - start);
    }
    return 0;
}
