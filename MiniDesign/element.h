#pragma once
#include <string>
#include <memory>

using namespace std;

class Element {
public:
    Element() : m_parent(*this) {}
    Element(Element& parent) : m_parent(parent) {}
    virtual ~Element() = default;
    
    virtual int getID() const = 0;
    virtual string getTexture() const = 0;
    virtual void ajouterTexture(const string& texture) = 0;
    virtual void afficher() const = 0;
    virtual bool estComposite() const = 0;
    
    virtual bool isRoot() const { return (&m_parent == this); }
    virtual const Element& getParent() const { return m_parent; }
    virtual Element& getParent() { return m_parent; }
    
protected:
    Element& m_parent;
};