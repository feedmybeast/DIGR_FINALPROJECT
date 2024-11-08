#pragma once
#include <vector>
#include "Vertex.h"
#include "Edge.h"

class Graph {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

public:
    Graph();
    void addVertex(const Vertex& vertex);
    void addEdge(const Edge& edge);
    void removeVertex(int id);
    void removeEdge(int id);
    std::vector<Vertex> getVertices() const;
    std::vector<Edge> getEdges() const;

    // Advanced features
    std::vector<int> shortestPath(int startId, int endId) const; // Dijkstra's algorithm
    bool isConnected() const; // Check if the graph is connected
    std::vector<int> findEulerCircuit() const; // Find Euler circuit if it exists
    std::vector<Edge> minimumSpanningTree() const; // Kruskal's algorithm

    // Helper methods
    int getVertexIndex(int id) const;
    void updateVertexDegrees();
};
