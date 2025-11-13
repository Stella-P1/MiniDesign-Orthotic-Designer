#pragma once
class Point {
private:
    static int prochainID;
    int id;
    int x, y;
    char texture;
    
public:
    Point(int x, int y);
    int getID() const;
    int getX() const;
    int getY() const;
    char getTexture() const;
    void setPosition(int x, int y);
    void setTexture(char t);
};