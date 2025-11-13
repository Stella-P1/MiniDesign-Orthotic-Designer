#include "point.h"
int Point::prochainID = 0;
Point::Point(int x, int y) : x(x), y(y), texture('.') {
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
char Point::getTexture() const {
    return texture;
}
void Point::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}
void Point::setTexture(char t) {
    texture = t;
}