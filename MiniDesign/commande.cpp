#include "commande.h"
#include <algorithm>
#include <iostream>

CommandeDeplacer::CommandeDeplacer(vector<shared_ptr<Point>>& pts, int id, int x, int y)
    : points(pts), id(id), nouveauX(x), nouveauY(y), executed(false) {}

void CommandeDeplacer::executer() {
    auto it = find_if(points.begin(), points.end(),
        [this](const shared_ptr<Point>& p) { return p->getID() == id; });
    
    if (it != points.end()) {
        ancienX = (*it)->getX();
        ancienY = (*it)->getY();
        (*it)->setPosition(nouveauX, nouveauY);
        executed = true;
        cout << "Point " << id << " deplace en (" << nouveauX << "," << nouveauY << ")\n";
    } else {
        cout << "Point " << id << " non trouve\n";
    }
}

void CommandeDeplacer::annuler() {
    if (!executed) return;
    
    auto it = find_if(points.begin(), points.end(),
        [this](const shared_ptr<Point>& p) { return p->getID() == id; });
    
    if (it != points.end()) {
        (*it)->setPosition(ancienX, ancienY);
        cout << "Deplacement de Point " << id << " annule\n";
    }
}

CommandeSupprimer::CommandeSupprimer(vector<shared_ptr<Point>>& pts, int id)
    : points(pts), id(id), pointSupprime(nullptr), indexSupprime(0) {}

void CommandeSupprimer::executer() {
    auto it = find_if(points.begin(), points.end(),
        [this](const shared_ptr<Point>& p) { return p->getID() == id; });
    
    if (it != points.end()) {
        indexSupprime = distance(points.begin(), it);
        pointSupprime = *it;
        points.erase(it);
        cout << "Point " << id << " supprime\n";
    } else {
        cout << "Point " << id << " non trouve\n";
    }
}

void CommandeSupprimer::annuler() {
    if (pointSupprime) {
        points.insert(points.begin() + indexSupprime, pointSupprime);
        cout << "Suppression de Point " << id << " annulee\n";
    }
}