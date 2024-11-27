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
        actionTypes->Add("AddVertex"); // Record action type
        actionVertices->Add(vertex); // Record vertex involved in action
        actionEdges->Add(nullptr);
    }

    void AddEdge(Edge^ edge) {
        edges->Add(edge);
        undoEdges->Add(edge);
        undoIsAddEdge->Add(true);
    }

    void RemoveVertex(Vertex^ vertex) {
        Licc->Clear();
        for each (Edge ^ e in edges) {
            if ((e->Start == vertex || e->End == vertex)&&e != nullptr) {
                //RemoveEdge(e);
                //edges->Remove(e);
                Licc->Add(e);
            }
        }
        for each (Edge ^ e in Licc) {
            edges->Remove(e);
        }
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
    void RemoveEdge(Edge^ edge) {
        int hasMultiEdge = 0;
        for each (Edge ^ e in edges) {
            if ((e->Start == edge->Start && e->End == edge->End) || (e->Start == edge->End && e->End == edge->Start)) {
                hasMultiEdge++;
                //break;
            }
        }
        // If no multi-edge remains, reset the edge type to straight
        if (hasMultiEdge <= 2) {
            for each (Edge ^ e in edges) {
                if ((e->Start == edge->Start && e->End == edge->End) || (e->Start == edge->End && e->End == edge->Start)) {
                    e->IsCoincideEdge = false;
                }
            }
            edge->IsCoincideEdge = false;
        }
        edges->Remove(edge);
        // Record action for undo
        undoEdges->Add(edge);
        undoIsAddEdge->Add(false); // False for "remove edge"
        actionTypes->Add("RemoveEdge"); // Record action type
        actionVertices->Add(nullptr); // No vertex involved in this action
        actionEdges->Add(edge);
    }
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
    List<String^>^ actionTypes; // List to store action types
    List<Vertex^>^ actionVertices; // List to store vertices involved in actions
    List<Edge^>^ actionEdges;
    List<Edge^>^ Licc;
    int idToFind;
    //System::Collections::Generic::Stack<Action^>^ undoStack;
    Graph^ graph;
};
