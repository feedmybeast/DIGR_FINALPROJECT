#include "Vertex.h"

Vertex::Vertex(int id, const std::string& name, int x, int y)
    : id(id), name(name), x(x), y(y), degree(0) {}

int Vertex::getId() const {
    return id;
}

std::string Vertex::getName() const {
    return name;
}

void Vertex::setName(const std::string& newName) {
    name = newName;
}

int Vertex::getX() const {
    return x;
}

int Vertex::getY() const {
    return y;
}

void Vertex::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

int Vertex::getDegree() const {
    return degree;
}

void Vertex::setDegree(int newDegree) {
    degree = newDegree;
}
