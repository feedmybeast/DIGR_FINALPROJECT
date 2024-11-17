#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <cmath>

Graph::Graph() {
    vertices = gcnew List<Vertex^>();
    edges = gcnew List<Edge^>();
}

Vertex^ Graph::FindVertexAt(float x, float y) {
    for each (Vertex ^ vertex in vertices) {
        float dx = vertex->X - x;
        float dy = vertex->Y - y;
        float distance = static_cast<float>(sqrt(dx * dx + dy * dy));
        if (distance < vertex->Radius) {
            return vertex;
        }
    }
    return nullptr;
}

void Graph::AddEdge(String^ startVertexName, String^ endVertexName, int weight, bool isDirected) {
    Vertex^ startVertex = FindVertexByName(startVertexName);
    Vertex^ endVertex = FindVertexByName(endVertexName);

    if (startVertex != nullptr && endVertex != nullptr) {
        if (isDirected) {
            Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black, isDirected);
            edges->Add(newEdge);
        }
        else {
            Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black, isDirected);
            edges->Add(newEdge);
        }
    }
    //if (startVertex != nullptr && endVertex != nullptr) {
    //    Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black, isDirected);
    //    edges->Add(newEdge);
    //}
}
void Graph::AddEdge(String^ start, String^ end, int weight) {
    Vertex^ startVertex = FindVertexByName(start);
    Vertex^ endVertex = FindVertexByName(end);
    if (startVertex != nullptr && endVertex != nullptr) {
        Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black);
        edges->Add(newEdge);
    }
}
Vertex^ Graph::FindVertexByName(String^ name) {
    for each (Vertex ^ vertex in vertices) {
        if (vertex->Name == name) {
            return vertex;
        }
    }
    return nullptr;
}

void Graph::SaveToFile(String^ fileName) {
    try {
        System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(fileName);

        // Write vertices
        for each (Vertex ^ vertex in vertices) {
            writer->WriteLine("V,{0},{1},{2},{3}", vertex->Id, vertex->Name, vertex->X, vertex->Y);
        }

        // Write edges
        for each (Edge ^ edge in edges) {
            writer->WriteLine("E,{0},{1},{2},{3},{4}",
                edge->Start->Id,
                edge->End->Id,
                edge->Weight,
                edge->Color.ToArgb(),
                edge->Directed);
        }

        writer->Close();
    }
    catch (System::Exception^ e) {
        // Handle any exceptions (e.g., file access issues)
        System::Windows::Forms::MessageBox::Show("Error saving graph: " + e->Message);
    }
}
