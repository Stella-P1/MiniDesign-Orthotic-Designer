#include "strategieAffichage.h"
using namespace std;

string AffichageTexture::getSymbole(const shared_ptr<Point>& point) const {
    return point->getTexture();
}

string AffichageID::getSymbole(const shared_ptr<Point>& point) const {
    int id = point->getID();
    char symbole = (id < 10) ? ('0' + id) : ('A' + (id - 10));
    return string(&symbole, 1);
}