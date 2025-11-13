#pragma once
#include <vector>
#include <memory>
#include "point.h"

class StrategieSurface {
public:
virtual ~StrategieSurface()=default;
virtual std::vector<std::shared_ptr<Point>> ordonnerPoints(const std::vector<std::shared_ptr<Point>>& points) const =0;
};

class StrategieOrdreID: public StrategieSurface {
public:
    std::vector<std::shared_ptr<Point>> ordonnerPoints(const std::vector<std::shared_ptr<Point>>& points) const override;
};

class StrategieDistanceMin: public StrategieSurface {
public:
    std::vector<std::shared_ptr<Point>> ordonnerPoints(const std::vector<std::shared_ptr<Point>>& points) const override;
};