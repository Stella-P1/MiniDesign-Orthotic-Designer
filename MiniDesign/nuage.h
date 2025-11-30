#pragma once
#include <vector>
#include <memory>
#include <string>
#include "element.h"
#include "point.h"

using namespace std;

// Composite du patron Composite

class Nuage : public Element {
private:
    string texture;
    vector<shared_ptr<Element>> elements;
    int id;
    static int prochainID;
    
public:
    Nuage(string texture);
    Nuage(Element& parent, string texture);
    virtual ~Nuage() = default;
    
    void ajouterElement(shared_ptr<Element> element);
    void retirerElement(int index);
    
    virtual int getID() const override;
    virtual string getTexture() const override;
    virtual void ajouterTexture(const string& texture) override;
    virtual void afficher() const override;
    virtual bool estComposite() const override { return true; }
    
    const vector<shared_ptr<Element>>& getElements() const;
    vector<shared_ptr<Point>> getPoints() const;
    int getNombrePoints() const;
    
    static void resetID();
};