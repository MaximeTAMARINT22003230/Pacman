#include "En-têtes/params.h"
#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

#include "mingl/mingl.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/triangle.h"

#include "En-têtes/pacman.h"
#include "En-têtes/type.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;

void affichePacman(const unsigned & posX,const unsigned & posY, MinGL &window,bool boucheOuverte, string & direction,bool & pouvoirPacman, CMyParam & Param) // affiche un pacman au coordonnée donnée
{
    InitParams(Param);
    // Si pacman va vers la droite
    if (direction == "droite")
    {
        //si pacman a la bouche ouverte
        if (boucheOuverte)
        {
            if (pouvoirPacman)
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacmanEnerve")->second);
            else
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacman")->second); // corp du pacman
            window << Circle(Vec2D(posX,posY-10), 2, KBlack); // oeil du pacman
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+15,posY-14), Vec2D(posX+20,posY-7), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 1 (couleur = sol)
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+20,posY-7), Vec2D(posX+22,posY), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 2
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+22,posY), Vec2D(posX+20,posY+7), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 3
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+20,posY+7), Vec2D(posX+15,posY+14), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 4
        }
        //si pacman à la bouche fermée
        else
        {
            if (pouvoirPacman)
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacmanEnerve")->second);
            else
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacman")->second);
            window << Circle(Vec2D(posX,posY-10), 2, KBlack); // oeil du pacman
        }
    }
    // si pacman va vers la gauche
    else if (direction == "gauche")
    {
        // si pacman a la bouche ouverte
        if (boucheOuverte)
        {
            if (pouvoirPacman)
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacmanEnerve")->second);
            else
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacman")->second);
            window << Circle(Vec2D(posX,posY-10), 2, KBlack); // oeil du pacman
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-15,posY-14), Vec2D(posX-20,posY-7), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 1
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-20,posY-7), Vec2D(posX-22,posY), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 2
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-22,posY), Vec2D(posX-20,posY+7), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 3
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-20,posY+7), Vec2D(posX-15,posY+14), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 4
        }
        // si pacman a la bouche fermée
        else
        {
            if (pouvoirPacman)
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacmanEnerve")->second);
            else
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacman")->second);
            window << Circle(Vec2D(posX,posY-10), 2, KBlack); // oeil du pacman
        }
    }
    // si pacman va vers le bas
    else if (direction == "bas")
    {
        // si pacman a la bouche ouverte
        if (boucheOuverte)
        {
            if (pouvoirPacman)
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacmanEnerve")->second);
            else
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacman")->second);
            window << Circle(Vec2D(posX+10,posY), 2, KBlack); // oeil du pacman
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-14,posY+15), Vec2D(posX-7,posY+20), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 1
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-7,posY+20), Vec2D(posX,posY+22), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 2
            window << Triangle(Vec2D(posX,posY), Vec2D(posX,posY+22), Vec2D(posX+7,posY+20), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 3
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+7,posY+20), Vec2D(posX+14,posY+15), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 4
        }
        // si pacman a la bouche fermée
        else
        {
            if (pouvoirPacman)
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacmanEnerve")->second);
            else
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacman")->second);
            window << Circle(Vec2D(posX+10,posY), 2, KBlack); // oeil du pacman
        }
    }
    // si pacman va vers le haut
    else if (direction == "haut")
    {
        // si pacman a la bouche ouverte
        if (boucheOuverte)
        {
            if (pouvoirPacman)
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacmanEnerve")->second);
            else
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacman")->second);
            window << Circle(Vec2D(posX-10,posY), 2, KBlack); // oeil du pacman
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-14,posY-15), Vec2D(posX-7,posY-20), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 1
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-7,posY-20), Vec2D(posX,posY-22), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 2
            window << Triangle(Vec2D(posX,posY), Vec2D(posX,posY-22), Vec2D(posX+7,posY-20), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 3
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+7,posY-20), Vec2D(posX+14,posY-15), Param.MapParamString.find("ColorChemin")->second); // partie de bouche 4
        }
        // si pacman a la bouche fermée
        else
        {
            if (pouvoirPacman)
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacmanEnerve")->second);
            else
                window << Circle(Vec2D(posX,posY), 20, Param.MapParamString.find("ColorPacman")->second);
            window << Circle(Vec2D(posX-10,posY), 2, KBlack); // oeil du pacman
        }
    }
}
