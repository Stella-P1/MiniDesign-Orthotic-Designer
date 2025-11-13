#include "strategieAffichage.h"
using namespace std;


char AffichageTexture::getSymbole(const shared_ptr<Point>& point) const {
    return point->getTexture();
}

char AffichageID::getSymbole(const shared_ptr<Point>& point) const {
    int id= point->getID();
    if (id <10)return '0' + id;
    return 'A' + (id -10);
}