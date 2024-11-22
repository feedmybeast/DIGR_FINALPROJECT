#pragma once

using namespace System;
using namespace System::Drawing;

public ref class Vertex
{
public:
    property int Id { int get() { return id; } void set(int value) { id = value; } }
    property String^ Name { String^ get() { return name; } void set(String^ value) { name = value; } }
    property float X { float get() { return x; } void set(float value) { x = value; } }
    property float Y { float get() { return y; } void set(float value) { y = value; } }
    property int Degree { int get() { return degree; } void set(int value) { degree = value; } }
    property Color ColorProperty { Color get() { return color; } void set(Color value) { color = value; } }
    float Radius;
    property bool IsCoincideVertex { bool get() { return isCoincideVertex; } void set(bool value) { isCoincideVertex = value; } }

    Vertex(int id, String^ name, float x, float y) {
        this->Id = id;
        this->Name = name;
        this->X = x;
        this->Y = y;
        this->ColorProperty = Color::Black; // Use the property to set color
        this->Radius = 10.0f;
        this->IsCoincideVertex = isCoincideVertex;
    }

private:
    int id;
    String^ name;
    float x, y;
    int degree;
    Color color; // Store the color in a private member variable
    bool isCoincideVertex;
};