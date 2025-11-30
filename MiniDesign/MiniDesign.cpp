#include "affichage.h"
#include "gestionnaire.h"
#include "strategieSurface.h"
#include "strategieAffichage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    string args;
    // On accepte des points en entrée.
    if (argc > 1) {
        ostringstream oss;
        for (int i = 1; i < argc; ++i) oss << argv[i] << " ";
        args = oss.str();
    } else {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }
    

    vector<Point> points = creerPoints(args);
    vector<string> texturesNuages = {"o", "#", "$"};
    Gestionnaire gestionnaire(points, texturesNuages);
    AffichageTexture affichageTexture;
    AffichageID affichageID;
    StrategieOrdreID strategieC1;
    StrategieDistanceMin strategieC2;
    
    string cmd;
    
    // Menu
    while (true) {
        cout << "\nCommandes:\n"
                  << "a  - Afficher les points et les nuages\n"
                  << "o1 - Afficher l'orthèse avec les textures des points\n"
                  << "o2 - Afficher l'orthèse avec les IDs des points\n"
                  << "f  - Fusionner des points dans un nuage (et appliquer texture)\n"
                  << "d  - Deplacer un point (ID)\n"
                  << "s  - Supprimer un point (ID)\n"
                  << "c1 - Créer les surfaces selon l'ordre des IDs\n"
                  << "c2 - Créer les surfaces selon la distance minimale\n"
                  << "u  - Annuler la derniere action\n"
                  << "r  - Reappliquer la derniere action annulee\n"
                  << "q  - Quitter\n> ";
        getline(std::cin, cmd);

        if (cmd == "q"){break;}
                else if (cmd == "a") {
            gestionnaire.afficherPointsEtNuages();
        }
        else if (cmd == "o1") {
            gestionnaire.afficherOrthese(affichageTexture);
        }
        else if (cmd == "o2") {
            gestionnaire.afficherOrthese(affichageID);
        }
        else if (cmd == "f") {
            cout << "Entrez les IDs des points a fusionner (separes par des espaces) :\n> ";
            string ligne;
            getline(cin, ligne);
            istringstream iss(ligne);
            vector<int> ids;
            int id;
            while (iss >> id) {
                ids.push_back(id);
            }
            gestionnaire.fusionnerPoints(ids);
        }
        else if (cmd == "d") {
            cout << "Entrez l'ID du point a deplacer :\n> ";
            int id;
            cin >> id;
            cout << "Entrez la nouvelle position (x y) :\n> ";
            int x, y;
            cin >> x >> y;
            cin.ignore(); // Ignorer le newline
            gestionnaire.deplacerPoint(id, x, y);
        }
        else if (cmd == "s") {
            cout << "Entrez l'ID du point a supprimer :\n> ";
            int id;
            cin >> id;
            cin.ignore();
            gestionnaire.supprimerPoint(id);
        }
        else if (cmd == "c1") {
            gestionnaire.creerSurfaces(strategieC1);
        }
        else if (cmd == "c2") {
            gestionnaire.creerSurfaces(strategieC2);
        }
        else if (cmd == "u") {
            gestionnaire.undo();
        } else if (cmd == "r") {
            gestionnaire.redo();
        }
        else {
            cout << "Commande inconnue\n";
        }
        
    }

    return 0;
}