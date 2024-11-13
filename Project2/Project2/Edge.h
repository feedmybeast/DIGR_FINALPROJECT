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

    Edge(int id, Vertex^ start, Vertex^ end, int weight, System::Drawing::Color color)
    {
        Id = id;
        Start = start;
        End = end;
        Weight = weight;
        Color = color;
    }

    Edge(Vertex^ start, Vertex^ end, int weight)
        : Edge(0, start, end, weight, System::Drawing::Color::Black) {}
};
