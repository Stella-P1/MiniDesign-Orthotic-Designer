#include "gestionnaire.h"
#include "affichage.h"
#include "strategieAffichage.h"  
#include "strategieSurface.h"
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

Gestionnaire::Gestionnaire(const vector<Point>& pointsInitiaux, const vector<string>& textures):texturesNuages(textures) {
    Point::resetID();
    for (const auto& p : pointsInitiaux) {
        points.push_back(make_shared<Point>(p.getX(), p.getY()));
    }
    grilleCache = vector<vector<char>>(HAUTEUR, vector<char>(LARGEUR, ' '));

}

void Gestionnaire::afficherPointsEtNuages() const {
    cout << "\nListe:\n";
    for (const auto& p : points) {
        p->afficher();
    }
    
    for (size_t i = 0; i < nuages.size(); ++i) {
        cout << (points.size() + i) << ": Nuage '" << nuages[i]->getTexture() 
             << "' contient les elements: ";
        for (const auto& elem : nuages[i]->getElements()) {
            if (elem->estComposite()) {
                auto nuageElem = dynamic_pointer_cast<Nuage>(elem);
                int nuageIdx = 0;
                for (size_t j = 0; j < nuages.size(); ++j) {
                    if (nuages[j]->getID() == nuageElem->getID()) {
                        nuageIdx = j;
                        break;
                    }
                }
                cout << (points.size() + nuageIdx) << " ";
            } else {
                cout << elem->getID() << " ";
            }
        }
        cout << "\n";
    }
}

void Gestionnaire::afficherOrthese(const StrategieAffichage& strategie) const {
    vector<vector<string>> grille(HAUTEUR, vector<string>(LARGEUR, " "));
    
    if (!grilleCache.empty()) {
        for (int y = 0; y < HAUTEUR; ++y) {
            for (int x = 0; x < LARGEUR; ++x) {
                if (grilleCache[y][x] != ' ') {
                    grille[y][x] = string(1, grilleCache[y][x]);
                }
            }
        }
    }
    
    for (const auto& p : points) {
        int x = p->getX();
        int y = p->getY();
        if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR) {
            grille[y][x] = strategie.getSymbole(p);
        }
    }
    
    cout << "\n";
    int maxWidth = 1;
    for (int y = 0; y < HAUTEUR; ++y) {
        for (int x = 0; x < LARGEUR; ++x) {
            if (grille[y][x].length() > maxWidth) {
                maxWidth = grille[y][x].length();
            }
        }
    }
    
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x) {
            cout << grille[y][x];
            for (int pad = grille[y][x].length(); pad < maxWidth; ++pad) {
                cout << " ";
            }
        }
        cout << '\n';
    }
}

void Gestionnaire::fusionnerPoints(const vector<int>& ids){
    if (ids.empty()) return;
    string texture = texturesNuages[nuages.size()%texturesNuages.size()];
    auto nouveauNuage = make_shared<Nuage>(texture);
    
    for (int id : ids) {
        if (id < points.size()) {
            for (const auto& p : points) {
                if (p->getID() == id) {
                    p->ajouterTexture(texture);
                    nouveauNuage->ajouterElement(p);
                    break;
                }
            }
        } else {
            int nuageIndex = id - points.size();
            if (nuageIndex >= 0 && nuageIndex < nuages.size()) {
                auto& nuage = nuages[nuageIndex];
                nuage->ajouterTexture(texture);
                nouveauNuage->ajouterElement(nuage);
            }
        }
    }
    
    nuages.push_back(nouveauNuage);
    cout<<"Nuage cree avec texture '"<<texture<<"'\n";
}

void Gestionnaire::deplacerPoint(int id, int x, int y) {
    auto cmd = make_shared<CommandeDeplacer>(points, id, x, y);
    cmd->executer();
    historique.push(cmd);
    while (!historiqueAnnule.empty()) {
        historiqueAnnule.pop();
    }
}

void Gestionnaire::supprimerPoint(int id) {
    auto cmd = make_shared<CommandeSupprimer>(points, id);
    cmd->executer();
    historique.push(cmd);
    while (!historiqueAnnule.empty()) {
        historiqueAnnule.pop();
    }
}
void Gestionnaire::creerSurfaces(const StrategieSurface& strategie) {
    grilleCache = vector<vector<char>>(HAUTEUR, vector<char>(LARGEUR, ' '));
    
    for (const auto& nuage : nuages) {
        if (nuage->getNombrePoints() < 2) continue;  // ← Utilisez ->
        auto pointsOrdres = strategie.ordonnerPoints(nuage->getPoints());  // ← Utilisez ->
        for (size_t i = 0; i < pointsOrdres.size(); ++i) {
            size_t j = (i + 1) % pointsOrdres.size();
            tracerLigne(grilleCache, pointsOrdres[i]->getX(), pointsOrdres[i]->getY(),
                       pointsOrdres[j]->getX(), pointsOrdres[j]->getY());
        }
    }
}
void Gestionnaire::tracerLigne(vector<vector<char>>& grille, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    int x = x0;
    int y = y0;
    
    while (true) {
        if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR) {
            char symbole;
            
            if (dx > dy) {
                if (dy == 0) {
                    symbole = '-';
                } else if (sy > 0) {
                    symbole = '/';
                } else {
                    symbole = '\\';
                }
            } else {
                if (dx == 0) {
                    symbole = '|';
                } else if ((sx > 0 && sy > 0) || (sx < 0 && sy < 0)) {
                    symbole = '/';
                } else {
                    symbole = '\\';
                }
            }
            
            grille[y][x] = symbole;
        }
        
        if (x == x1 && y == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}
void Gestionnaire::undo() {
    if (historique.empty()) {
        cout << "Aucune action a annuler\n";
        return;
    }
    
    auto cmd = historique.top();
    historique.pop();
    cmd->annuler();
    historiqueAnnule.push(cmd);
}

void Gestionnaire::redo() {
    if (historiqueAnnule.empty()) {
        cout << "Aucune action a reappliquer\n";
        return;
    }
    
    auto cmd = historiqueAnnule.top();
    historiqueAnnule.pop();
    cmd->executer();
    historique.push(cmd);
}



const vector<shared_ptr<Point>>& Gestionnaire::getPoints() const {
    return points;
}

const vector<shared_ptr<Nuage>>& Gestionnaire::getNuages() const {
    return nuages;
}
