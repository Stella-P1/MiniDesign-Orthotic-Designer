#include "nuage.h"
#include <iostream>

int Nuage::prochainID = 0;

Nuage::Nuage(string texture) : Element(), texture(texture) {
    id = prochainID++;
}

Nuage::Nuage(Element& parent, string texture) : Element(parent), texture(texture) {
    id = prochainID++;
}

void Nuage::ajouterElement(shared_ptr<Element> element) {
    elements.push_back(element);
}

void Nuage::retirerElement(int index) {
    if (index >= 0 && index < elements.size()) {
        elements.erase(elements.begin() + index);
    }
}

int Nuage::getID() const {
    return id;
}

string Nuage::getTexture() const {
    return texture;
}

void Nuage::ajouterTexture(const string& t) {
    for (auto& element : elements) {
        element->ajouterTexture(t);
    }
}

void Nuage::afficher() const {
    cout << "Nuage '" << texture << "' contient les elements: ";
    for (const auto& elem : elements) {
        cout << elem->getID() << " ";
    }
}

const vector<shared_ptr<Element>>& Nuage::getElements() const {
    return elements;
}

vector<shared_ptr<Point>> Nuage::getPoints() const {
    vector<shared_ptr<Point>> points;
    for (const auto& elem : elements) {
        if (!elem->estComposite()) {
            points.push_back(dynamic_pointer_cast<Point>(elem));
        } else {
            auto nuage = dynamic_pointer_cast<Nuage>(elem);
            if (nuage) {
                auto pts = nuage->getPoints();
                points.insert(points.end(), pts.begin(), pts.end());
            }
        }
    }
    return points;
}

int Nuage::getNombrePoints() const {
    return getPoints().size();
}

void Nuage::resetID() {
    prochainID = 0;
}