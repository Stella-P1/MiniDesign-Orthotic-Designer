#include "affichage.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void tracerLigne(vector<vector<char>>& grille, int x0, int y0, int x1, int y1) {
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

void imprimerGrille(const vector<Point>& points) {
    vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x)
            cout << grille[y][x];
        cout << '\n';
    }
}



vector<Point> creerPoints(const string& ligne) {
    vector<Point> points;
    // On crée un flux de lecture (istringstream) à partir de la chaîne ligne.
    istringstream iss(ligne);
    string token;
    // On lit chaque point de la ligne (séparé par des espaces).
    while (iss >> token) {
        // On vérifie que le point est entre parenthèses
        if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {
            // On enlève les parenthèses au début et à la fin.
            token = token.substr(1, token.size() - 2);
            // On remplace la virgule par un espace.
            replace(token.begin(), token.end(), ',', ' ');
            // On crée un flux de lecture pour chaque point
            istringstream pair(token);
            int x, y;
            // On ajoute un point {x, y} au vecteur de points.
            if (pair >> x >> y) {
                points.push_back({x, y});
            }
        }
    }
    return points;
}