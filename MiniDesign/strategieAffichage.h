#pragma once
#include <vector>
#include <memory>
#include "point.h"


class StrategieAffichage {
public:
    virtual ~StrategieAffichage()=default;
    virtual char getSymbole(const std::shared_ptr<Point>& point) const =0;
};

class AffichageTexture: public StrategieAffichage {
    public:
        char getSymbole(const std::shared_ptr<Point>& point) const override;
};

class AffichageID: public StrategieAffichage {
    public:
        char getSymbole(const std::shared_ptr<Point>& point) const override;
};