#include "Graph.h"

Graph::Graph() {}

void Graph::addVertex(const Vertex& vertex) {
    vertices.push_back(vertex);
}

void Graph::addEdge(const Edge& edge) {
    edges.push_back(edge);
}

void Graph::removeVertex(int id) {
    vertices.erase(std::remove_if(vertices.begin(), vertices.end(),
        [id](const Vertex& v) { return v.getId() == id; }), vertices.end());
    
    edges.erase(std::remove_if(edges.begin(), edges.end(),
        [id](const Edge& e) { return e.getStart()->getId() == id || e.getEnd()->getId() == id; }), edges.end());
}

void Graph::removeEdge(int id) {
    edges.erase(std::remove_if(edges.begin(), edges.end(),
        [id](const Edge& e) { return e.getId() == id; }), edges.end());
}

std::vector<Vertex> Graph::getVertices() const {
    return vertices;
}

std::vector<Edge> Graph::getEdges() const {
    return edges;
}

std::vector<int> Graph::shortestPath(int startId, int endId) const {
    // Implement Dijkstra's algorithm here
    // This is a placeholder implementation
    return std::vector<int>();
}

bool Graph::isConnected() const {
    // Implement DFS or BFS to check connectivity
    // This is a placeholder implementation
    return false;
}

std::vector<int> Graph::findEulerCircuit() const {
    // Implement Euler circuit finding algorithm
    // This is a placeholder implementation
    return std::vector<int>();
}

std::vector<Edge> Graph::minimumSpanningTree() const {
    // Implement Kruskal's algorithm
    // This is a placeholder implementation
    return std::vector<Edge>();
}

int Graph::getVertexIndex(int id) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i].getId() == id) {
            return static_cast<int>(i);
        }
    }
    return -1; // Vertex not found
}

void Graph::updateVertexDegrees() {
    for (Vertex& v : vertices) {
        int degree = 0;
        for (const Edge& e : edges) {
            if (e.getStart()->getId() == v.getId() || e.getEnd()->getId() == v.getId()) {
                ++degree;
            }
        }
        v.setDegree(degree);
    }
}
