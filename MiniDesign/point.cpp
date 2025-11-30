#include "point.h"
#include <iostream>

int Point::prochainID = 0;
const std::string TEXTURE_DEFAUT = ".";

Point::Point(int x, int y) : Element(), x(x), y(y), texture(TEXTURE_DEFAUT) {
    id = prochainID++;
}

Point::Point(const Point& other) : Element(), x(other.x), y(other.y), texture(other.texture) {
    id = prochainID++;
}

Point::Point(Element& parent, int x, int y) : Element(parent), x(x), y(y), texture(TEXTURE_DEFAUT) {
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

void Point::ajouterTexture(const string& t) {
    if (texture == TEXTURE_DEFAUT || texture.empty()) {
        texture = t;
    } else {
        if (texture.find(t) == string::npos) {
            texture += t;
        }
    }
}

void Point::afficher() const {
    cout << id << ": (" << x << "," << y << ") textures: '" << texture << "'\n";
}

void Point::resetID() {
    prochainID = 0;
}