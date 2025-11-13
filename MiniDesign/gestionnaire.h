#pragma once
#include <vector>
#include <memory>
#include "point.h"
#include "nuage.h"
#include "strategieSurface.h"
#include "strategieAffichage.h"

class Gestionnaire {
private:
std::vector<std::shared_ptr<Point>> points;
std::vector<Nuage> nuages;
std::vector<char> texturesNuages;

public:
Gestionnaire(const std::vector<Point>& pointsInitiaux, const std::vector<char>& textures);
void afficherPointsEtNuages() const;
void afficherOrthese(const StrategieAffichage& strategie) const;
void fusionnerPoints(const std::vector<int>& ids);
void deplacerPoint(int id, int x, int y);
void supprimerPoint(int id);
void creerSurfaces(const StrategieSurface& strategie);
const std::vector<Nuage>& getNuages() const;
const std::vector<std::shared_ptr<Point>>& getPoints() const;
};