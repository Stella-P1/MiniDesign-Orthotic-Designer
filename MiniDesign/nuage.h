#pragma once
#include <vector>
#include <memory>
#include "point.h"

class Nuage {
private:
    std::vector<std::shared_ptr<Point>> points;
    char texture;
public:
    Nuage(char texture);
    void ajouterPoint(std::shared_ptr<Point> p);
    const std::vector<std::shared_ptr<Point>>& getPoints() const;
    char getTexture() const;
    int getNombrePoints() const;
};