#pragma once
#include <string>

class Vertex {
private:
    int id;
    std::string name;
    int x, y;
    int degree;

public:
    Vertex(int id, const std::string& name, int x, int y);
    int getId() const;
    std::string getName() const;
    void setName(const std::string& name);
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);
    int getDegree() const;
    void setDegree(int degree);
};
