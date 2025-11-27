#pragma once
#include <string>   
#include <string>
using namespace std;
class Point {
private:
    static int prochainID;
    int id;
    int x, y;
    string texture;
    
public:
    Point(int x, int y);
    int getID() const;
    int getX() const;
    int getY() const;
    string getTexture() const;
    void setPosition(int x, int y);
    void setTexture(string t);
    void ajouterTexture(string t);

    static void resetID();
};