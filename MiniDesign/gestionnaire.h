#pragma once
#include <vector>
#include <memory>
#include <string>
#include <stack>
#include "point.h"
#include "nuage.h"
#include "element.h"
#include "commande.h"

using namespace std;

class Gestionnaire {
private:
    vector<shared_ptr<Point>> points;
    vector<shared_ptr<Nuage>> nuages;
    vector<string> texturesNuages;
    vector<vector<char>> grilleCache;
    static const int LARGEUR = 30;
    static const int HAUTEUR = 20;
    
    stack<shared_ptr<Commande>> historique;
    stack<shared_ptr<Commande>> historiqueAnnule;
    
    void tracerLigne(vector<vector<char>>& grille, int x0, int y0, int x1, int y1);
    
public:
    Gestionnaire(const vector<Point>& pointsInitiaux, const vector<string>& textures);
    void afficherPointsEtNuages() const;
    void afficherOrthese(const class StrategieAffichage& strategie) const;
    void fusionnerPoints(const vector<int>& ids);
    void deplacerPoint(int id, int x, int y);
    void supprimerPoint(int id);
    void creerSurfaces(const class StrategieSurface& strategie);
    void undo();
    void redo();
    const vector<shared_ptr<Point>>& getPoints() const;
    const vector<shared_ptr<Nuage>>& getNuages() const;
};