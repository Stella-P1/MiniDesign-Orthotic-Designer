#pragma once
#include <vector>
#include <memory>
#include <string>
#include "point.h"
using namespace std;

class StrategieAffichage {
public:
    virtual ~StrategieAffichage()=default;
    virtual string getSymbole(const std::shared_ptr<Point>& point) const =0;
};

class AffichageTexture: public StrategieAffichage {
    public:
        string getSymbole(const std::shared_ptr<Point>& point) const override;
};

class AffichageID: public StrategieAffichage {
    public:
        string getSymbole(const std::shared_ptr<Point>& point) const override;
};