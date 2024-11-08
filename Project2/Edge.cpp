#include "Edge.h"

Edge::Edge(int id, Vertex* start, Vertex* end, int weight, const std::string& color)
    : id(id), start(start), end(end), weight(weight), color(color) {}

int Edge::getId() const {
    return id;
}

Vertex* Edge::getStart() const {
    return start;
}

Vertex* Edge::getEnd() const {
    return end;
}

int Edge::getWeight() const {
    return weight;
}

void Edge::setWeight(int newWeight) {
    weight = newWeight;
}

std::string Edge::getColor() const {
    return color;
}

void Edge::setColor(const std::string& newColor) {
    color = newColor;
}
