#include "nuage.h"
Nuage::Nuage(string texture) : texture(texture) {}
void Nuage::ajouterPoint(std::shared_ptr<Point> p) {
    points.push_back(p);
}
const std::vector<std::shared_ptr<Point>>& Nuage::getPoints() const {
    return points;
}
string Nuage::getTexture() const {
    return texture;
}
int Nuage::getNombrePoints() const {
    return points.size();
}
