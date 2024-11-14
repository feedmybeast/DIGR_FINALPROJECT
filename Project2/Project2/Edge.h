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

    Edge(Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color, bool directed)
    {
        Id = 0;
        Start = start;
        End = end;
        Weight = weight;
        Color = color;
        Directed = directed;
    }
    Edge(int id, Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color, bool directed)
    {
        Id = id;
        Start = start;
        End = end;
        Weight = weight;
        Color = color;
        Directed = directed;
    }
    Edge(int id, Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color)
    {
        Id = id;
        Start = start;
        End = end;
        Weight = weight;
        Color = color;
        Directed = false;
    }
    Edge(Vertex^ start, Vertex^ end, System::Drawing::Color color)
    {
        Start = start;
        End = end;
        Color = color;
        Directed = false;
    }
    //Edge(Vertex^ start, Vertex^ end, int weight)
    //    : Edge(0, start, end, weight, System::Drawing::Color::Black) {}

    Edge(Vertex^ start, Vertex^ end, int weight)
        : Edge(start, end, weight, System::Drawing::Color::Black, false) {}
    Edge(Vertex^ start, Vertex^ end, bool directed)
        : Edge(start, end,System::Drawing::Color::Black) {}
};
