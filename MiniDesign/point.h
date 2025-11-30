#pragma once
#include <string>
#include "element.h"

using namespace std;

class Point : public Element {
private:
    int x, y;
    int id;
    string texture;
    static int prochainID;
    
public:
    Point(int x, int y);
    Point(Element& parent, int x, int y);
    Point(const Point& other);  // ← Ajoutez ce constructeur
    virtual ~Point() = default;
    
    virtual int getID() const override;
    int getX() const;
    int getY() const;
    virtual string getTexture() const override;
    void setPosition(int x, int y);
    void setTexture(string t);
    virtual void ajouterTexture(const string& t) override;
    virtual void afficher() const override;
    virtual bool estComposite() const override { return false; }
    
    static void resetID();
};