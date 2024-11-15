#pragma once

using namespace System;

public ref class Vertex
{
public:
    property int Id { int get() { return id; } void set(int value) { id = value; } }
    property String^ Name { String^ get() { return name; } void set(String^ value) { name = value; } }
    property int X { int get() { return x; } void set(int value) { x = value; } }
    property int Y { int get() { return y; } void set(int value) { y = value; } }
    property int Degree { int get() { return degree; } void set(int value) { degree = value; } }
    float Radius;
    Vertex(int id, String^ name, float x, float y) {
        this->Id = id;
        this->Name = name;
        this->X = x;
        this->Y = y;
        this->Radius = 10.0f;
    }
private:
    int id;
    String^ name;
    int x, y;
    int degree;
};