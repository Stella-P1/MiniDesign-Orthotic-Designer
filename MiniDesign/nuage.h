#pragma once
#include <vector>
#include <memory>
#include "point.h"
using namespace std;
class Nuage {
private:
    std::vector<std::shared_ptr<Point>> points;
    string texture;
public:
    Nuage(string texture);
    void ajouterPoint(std::shared_ptr<Point> p);
    const std::vector<std::shared_ptr<Point>>& getPoints() const;
    string getTexture() const;
    int getNombrePoints() const;
};