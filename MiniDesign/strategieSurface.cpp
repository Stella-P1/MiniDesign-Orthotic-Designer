#include "strategieSurface.h"
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;



vector<shared_ptr<Point>> StrategieOrdreID::ordonnerPoints(const vector<shared_ptr<Point>>& points) const {
    vector<shared_ptr<Point>> orderedPoints = points;
    sort(orderedPoints.begin(), orderedPoints.end(), [](const shared_ptr<Point>& a, const shared_ptr<Point>& b) {
        return a->getID() < b->getID();
    });
    return orderedPoints;
}





vector<shared_ptr<Point>> StrategieDistanceMin::ordonnerPoints(const vector<shared_ptr<Point>>& points)const{
    if(points.empty()){
        return {};
    }

    vector<shared_ptr<Point>> orderedPoints;
    vector<bool> visited(points.size(), false);

    orderedPoints.push_back(points[0]);
    visited[0] = true;

    for (size_t i = 1; i < points.size(); ++i) {
        shared_ptr<Point> lastPoint = orderedPoints.back();
        double minDistance = numeric_limits<double>::max();
        size_t minIndex = -1;

        for (size_t j = 0; j < points.size(); ++j) {
            if (visited[j]) continue;
            int dx = points[j]->getX() - lastPoint->getX();
            int dy = points[j]->getY() - lastPoint->getY();
            double distance = sqrt(dx * dx + dy * dy);
            if (distance < minDistance) {
                minDistance = distance;
                minIndex = j;
            }
        }

        if (minIndex != -1) {
            orderedPoints.push_back(points[minIndex]);
            visited[minIndex] = true;
        }
    }

    return orderedPoints;
}

