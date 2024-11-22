#pragma once

using namespace System;
using namespace System::Drawing;

ref class Vertex; // Forward declaration

public ref class Edge
{
public:
    property int Id;
    property Vertex^ Start;
    property Vertex^ End;
    property int Weight;
    property System::Drawing::Color Color;
    property bool Directed;
    property bool IsCoincideEdge;
private:
    int edgeIndex;
public:
    void SetEdgeIndex(int index) {
        edgeIndex = index;
    }
    int GetEdgeIndex() {
        return edgeIndex;
    }
    Edge(Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color, bool directed)
    {
        Id = 0;
        Start = start;
        End = end;
        Weight = weight;
        Color = color;
        Directed = directed;
        IsCoincideEdge = false;
    }
    Edge(bool isCoincideEdge, Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color, bool directed)
    {
        IsCoincideEdge = isCoincideEdge;
        Id = 0;
        Start = start;
        End = end;
        Weight = weight;
        Color = color;
        Directed = directed;
    }
    //Edge(bool isCoincideEdge, Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color, bool directed)
    //{
    //    IsCoincideEdge = isCoincideEdge;
    //    Id = 0;
    //    Start = start;
    //    End = end;
    //    Weight = weight;
    //    Color = color;
    //    Directed = directed;
    //}

    Edge(int id, Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color, bool directed)
    {
        Id = id;
        Start = start;
        End = end;
        Weight = weight;
        Color = color;
        Directed = directed;
    }

    Edge(Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color)
        : Edge(start, end, weight, color, false) {}

    Edge(Vertex^ start, Vertex^ end, int weight)
        : Edge(start, end, weight, System::Drawing::Color::Blue, false) {}
    //Edge(Vertex^ start, Vertex^ end, int weight, bool directed)
    //    : Edge(start, end, weight, System::Drawing::Color::Black) {}

    Edge(Vertex^ start, Vertex^ end, bool directed)
        : Edge(start, end, 0, System::Drawing::Color::Blue, directed) {}

    Edge(int id, Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color)
        : Edge(id, start, end, weight, color, false) {}
    Edge(bool isCoincideEdge, Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color)
        : Edge(isCoincideEdge, start, end, weight, color, false) {}
};
