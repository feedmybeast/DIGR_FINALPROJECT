#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <stack>
#include <vector>
#include <cstdint>
#include <vcclr.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;


public ref class Graph
{
public:
    Graph();
    Vertex^ FindVertexAt(float x, float y);
    void AddEdge(String^ startVertexName, String^ endVertexName, int weight, bool isDirected);
    void AddEdge(String^ startVertexName, String^ endVertexName, int weight);
    void Graph::AddEdge(bool isCoincideVertex, String^ start, String^ end, int weight, bool isDirected);
    void Graph::AddEdge(bool isCoincideVertex, String^ start, String^ end, int weight);
    //void AddEdge(Vertex^ start, Vertex^ end, Color color, bool directed);
    Vertex^ FindVertexByName(String^ name);
    Vertex^ Graph::GetVertexByName(String^ name) {
        for each (Vertex ^ vertex in Vertices) {
            if (vertex->Name == name) {
                return vertex;
            }
        }
        return nullptr;
    }
    property List<Vertex^>^ Vertices {
        List<Vertex^>^ get() { return vertices; }
    }

    property List<Edge^>^ Edges {
        List<Edge^>^ get() { return edges; }
    }

    void AddVertex(Vertex^ vertex) {
        vertices->Add(vertex);
        undoVertices->Add(vertex);
        undoIsAddVertex->Add(true);
    }

    void AddEdge(Edge^ edge) {
        edges->Add(edge);
    }

    void RemoveVertex(Vertex^ vertex) {
        vertices->Remove(vertex);
        // Record action for undo
        undoVertices->Add(vertex);
        undoIsAddVertex->Add(false); // False for "remove vertex"
        edges->RemoveAll(gcnew Predicate<Edge^>(this, &Graph::EdgeContainsVertex));
        vertexToRemove = vertex;
    }

    //void RemoveEdge(Edge^ edge) {
    //    edges->Remove(edge);
    //}
    void RemoveEdge(Edge^ edge);
    Vertex^ GetVertexById(int id) {
        idToFind = id;
        return vertices->Find(gcnew Predicate<Vertex^>(this, &Graph::VertexIdPredicate));
    }

    void Undo();
private:
    bool EdgeContainsVertex(Edge^ e) {
        return e->Start == vertexToRemove || e->End == vertexToRemove;
    }

    bool VertexIdPredicate(Vertex^ v) {
        return v->Id == idToFind;
    }
public:
    //void Clear() {
    //    vertices->Clear();
    //    edges->Clear();
    //}
    void Clear();
    void SaveToFile(String^ fileName);
    void LoadFromFile(String^ fileName);
    void Graph::UndoAddEdge(Edge^ edge) {
        edges->Remove(edge); // Remove the edge to undo an add
    }
    void UndoRemoveVertex(Vertex^ vertex);
    void UndoAddVertex(Vertex^ vertex);
    void Graph::UndoRemoveEdge(Edge^ edge) {
        edges->Add(edge); // Re-add the edge to undo a remove
    }
    //void Undo();
    //void Graph::MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
private:
    List<Vertex^>^ vertices;
    List<Edge^>^ edges;
    //List<Action^>^ actionHistory;
    // History tracking
    List<Edge^>^ undoEdges;      // Stores edges for undo
    List<bool>^ undoIsAddEdge;
    List<Vertex^>^ undoVertices;
    List<bool>^ undoIsAddVertex;
    Vertex^ vertexToRemove;
    int idToFind;
    //System::Collections::Generic::Stack<Action^>^ undoStack;
    Graph^ graph;
};
