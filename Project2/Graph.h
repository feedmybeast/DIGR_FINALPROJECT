#pragma once

using namespace System;
using namespace System::Collections::Generic;

ref class Vertex;
ref class Edge;

public ref class Graph
{
public:
    Graph() : vertices(gcnew List<Vertex^>()), edges(gcnew List<Edge^>()) {}

    property List<Vertex^>^ Vertices {
        List<Vertex^>^ get() { return vertices; }
    }

    property List<Edge^>^ Edges {
        List<Edge^>^ get() { return edges; }
    }

    void AddVertex(Vertex^ vertex) {
        vertices->Add(vertex);
    }

    void AddEdge(Edge^ edge) {
        edges->Add(edge);
    }

    void RemoveVertex(Vertex^ vertex) {
        vertices->Remove(vertex);
        edges->RemoveAll(gcnew Predicate<Edge^>(this, &Graph::EdgeContainsVertex));
        vertexToRemove = vertex;
    }

    void RemoveEdge(Edge^ edge) {
        edges->Remove(edge);
    }

    Vertex^ GetVertexById(int id) {
        idToFind = id;
        return vertices->Find(gcnew Predicate<Vertex^>(this, &Graph::VertexIdPredicate));
    }

private:
    bool EdgeContainsVertex(Edge^ e) {
        return e->Start == vertexToRemove || e->End == vertexToRemove;
    }

    bool VertexIdPredicate(Vertex^ v) {
        return v->Id == idToFind;
    }

public:
    void Clear() {
        vertices->Clear();
        edges->Clear();
    }

private:
    List<Vertex^>^ vertices;
    List<Edge^>^ edges;
    Vertex^ vertexToRemove;
    int idToFind;
};
