#pragma once

using namespace System;

public ref class Vertex
{
public:
    Vertex(int id, String^ name, int x, int y) : id(id), name(name), x(x), y(y), degree(0) {}
    property int Id { int get() { return id; } }
    property String^ Name { String^ get() { return name; } void set(String^ value) { name = value; } }
    property int X { int get() { return x; } void set(int value) { x = value; } }
    property int Y { int get() { return y; } void set(int value) { y = value; } }
    property int Degree { int get() { return degree; } void set(int value) { degree = value; } }
private:
    int id;
    String^ name;
    int x, y;
    int degree;
};
