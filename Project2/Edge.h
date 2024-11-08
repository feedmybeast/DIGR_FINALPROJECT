#pragma once
#include "Vertex.h"

#include <string>

class Edge {
private:
    int id;
    Vertex* start;
    Vertex* end;
    int weight;
    std::string color;

public:
    Edge(int id, Vertex* start, Vertex* end, int weight = 1, const std::string& color = "black");
    int getId() const;
    Vertex* getStart() const;
    Vertex* getEnd() const;
    int getWeight() const;
    void setWeight(int weight);
    std::string getColor() const;
    void setColor(const std::string& color);
};
