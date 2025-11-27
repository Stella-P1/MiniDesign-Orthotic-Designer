#include "point.h"
int Point::prochainID = 0;
std::string texture1 = ".";
std::string textureBase = "";
Point::Point(int x, int y) : x(x), y(y), texture(textureBase) {
    id = prochainID++;
}
int Point::getID() const {
    return id;
}
int Point::getX() const {
    return x;
}
int Point::getY() const {
    return y;
}
string Point::getTexture() const {
    return texture;
}
void Point::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}
void Point::setTexture(string t) {
    texture = t;
}
void Point::ajouterTexture(string t) {
    if (texture == texture1) {
        texture = t;
    } else {
        texture += t;
    }
}
void Point::resetID() {
    prochainID = 0;
}