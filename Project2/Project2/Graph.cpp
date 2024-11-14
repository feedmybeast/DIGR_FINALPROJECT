#include "Graph.h"

Graph::Graph() {
    vertices = gcnew List<Vertex^>();
    edges = gcnew List<Edge^>();
}

//void Graph::AddEdge(Vertex^ start, Vertex^ end, System::Drawing::Color color, bool directed) {
//    Edge^ edge = gcnew Edge(start, end, 0, color, directed); 
//    edges->Add(edge);
//    if (!directed) {
//        Edge^ reverseEdge = gcnew Edge(end, start, 0, color,directed);
//        edges->Add(reverseEdge);
//    }
//}
