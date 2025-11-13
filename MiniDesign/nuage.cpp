#include "nuage.h"
Nuage::Nuage(char texture) : texture(texture) {}
void Nuage::ajouterPoint(std::shared_ptr<Point> p) {
    points.push_back(p);
}
const std::vector<std::shared_ptr<Point>>& Nuage::getPoints() const {
    return points;
}
char Nuage::getTexture() const {
    return texture;
}
int Nuage::getNombrePoints() const {
    return points.size();
}
