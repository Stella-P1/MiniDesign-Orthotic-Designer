#pragma once
#include <memory>
#include <vector>
#include <string>
#include "point.h"
#include "nuage.h"

using namespace std;

class Commande {
public:
    virtual ~Commande() = default;
    virtual void executer() = 0;
    virtual void annuler() = 0;
};

class CommandeDeplacer : public Commande {
private:
    vector<shared_ptr<Point>>& points;
    int id;
    int nouveauX, nouveauY;
    int ancienX, ancienY;
    bool executed;
    
public:
    CommandeDeplacer(vector<shared_ptr<Point>>& pts, int id, int x, int y);
    void executer() override;
    void annuler() override;
};

class CommandeSupprimer : public Commande {
private:
    vector<shared_ptr<Point>>& points;
    int id;
    shared_ptr<Point> pointSupprime;
    size_t indexSupprime;
    
public:
    CommandeSupprimer(vector<shared_ptr<Point>>& pts, int id);
    void executer() override;
    void annuler() override;
};