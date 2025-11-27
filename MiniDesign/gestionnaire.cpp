#include "gestionnaire.h"
#include "affichage.h"
#include <iostream>
#include <algorithm>
using namespace std;

Gestionnaire::Gestionnaire(const vector<Point>& pointsInitiaux, const vector<string>& textures):texturesNuages(textures) {
    Point::resetID();
    for (const auto& p : pointsInitiaux) {
        points.push_back(make_shared<Point>(p.getX(), p.getY()));
    }
}

void Gestionnaire::afficherPointsEtNuages() const {
    cout << "\n=== Points ===\n";
    for (const auto& p : points) {
        cout << "Point " << p->getID() 
             << " : (" << p->getX() << "," << p->getY() << ") "
             << "textures: '" << p->getTexture() << "'\n";
    }
    
    cout << "\n=== Nuages ===\n";
    for (size_t i = 0; i < nuages.size(); ++i) {
        cout << "Nuage " << i << " (texture: " << nuages[i].getTexture() << ") : ";
        const auto& pts = nuages[i].getPoints();
        for (size_t j = 0; j < pts.size(); ++j) {
            cout << pts[j]->getID();
            if (j < pts.size() - 1) cout << " ";
        }
        cout << "\n";
    }
}

void Gestionnaire::afficherOrthese(const StrategieAffichage& strategie) const {
    vector<vector<string>> grille(HAUTEUR, vector<string>(LARGEUR, " "));
    for (const auto& p : points) {
        int x = p->getX();
        int y = p->getY();
        if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR) {
            grille[y][x] = strategie.getSymbole(p);
        }
    }
    cout << "\n";
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x) {
            cout << grille[y][x];
        }
        cout << '\n';
    }
}


void Gestionnaire::fusionnerPoints(const vector<int>& ids){
    if (ids.empty()) return;
    string texture = texturesNuages[nuages.size()%texturesNuages.size()];
    Nuage nouveauNuage(texture);
    for (int id : ids) {
        auto it = find_if(points.begin(), points.end(),
            [id](const shared_ptr<Point>& p) { return p->getID() == id; });
        if (it != points.end()) {
            (*it)->ajouterTexture(texture);
            nouveauNuage.ajouterPoint(*it);
            
        }
    }
    nuages.push_back(nouveauNuage);
    cout<<"Nuage cree avec texture '"<<texture<<"'\n";
}

void Gestionnaire::deplacerPoint(int id, int x, int y){
    auto it = find_if(points.begin(), points.end(),[id](const shared_ptr<Point>& p){return p->getID()==id;});
    if (it != points.end()){
        (*it)->setPosition(x,y);
        cout<<"Point "<<id<<" deplace en ("<<x<<","<<y<<")\n";
    } else {
        cout<<"Point "<<id<<" non trouve\n";
    }
}

void Gestionnaire::supprimerPoint(int id){
    auto it = find_if(points.begin(),points.end(),[id](const shared_ptr<Point>& p){return p->getID()==id;});
    if (it != points.end()){
        points.erase(it);
        cout<<"Point "<<id<<" supprime\n";
    } else {
        cout<<"Point "<<id<<" non trouve\n";
    }
}

void Gestionnaire::creerSurfaces(const StrategieSurface& strategie) {
    vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));
    for (const auto& nuage : nuages) {
        if (nuage.getNombrePoints() < 2) continue;
        auto pointsOrdres = strategie.ordonnerPoints(nuage.getPoints());
        for (size_t i = 0; i < pointsOrdres.size(); ++i) {
            size_t j = (i + 1) % pointsOrdres.size();
            tracerLigne(grille, pointsOrdres[i]->getX(), pointsOrdres[i]->getY(),pointsOrdres[j]->getX(), pointsOrdres[j]->getY());
        }
    }
    cout << "\n";
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x) {
            cout << grille[y][x];
        }
        cout << '\n';
    }
}

const vector<shared_ptr<Point>>& Gestionnaire::getPoints() const {
    return points;
}

const vector<Nuage>& Gestionnaire::getNuages() const {
    return nuages;
}

