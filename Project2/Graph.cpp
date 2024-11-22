#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <cmath>
using namespace System::Collections::Generic;
Graph::Graph() {
    vertices = gcnew List<Vertex^>();
    edges = gcnew List<Edge^>();
    //undoStack = gcnew System::Collections::Generic::Stack<Action^>(); // Initialize undoStack
    //graph = this;
    undoEdges = gcnew List<Edge^>();
    undoIsAddEdge = gcnew List<bool>();
    undoVertices = gcnew List<Vertex^>();
    undoIsAddVertex = gcnew List<bool>();
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
    //Vertex^ startVertex = FindVertexByName(startVertexName);
    //Vertex^ endVertex = FindVertexByName(endVertexName);

    //if (startVertex != nullptr && endVertex != nullptr) {
    //    if (isDirected) {
    //        Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black, isDirected);
    //        edges->Add(newEdge);
    //        //undoStack->Push(gcnew AddEdgeAction(this, newEdge));
    //    }
    //    else {
    //        Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black, isDirected);
    //        edges->Add(newEdge);
    //        //undoStack->Push(gcnew AddEdgeAction(this, newEdge));
    //    }
    //}
    ////if (startVertex != nullptr && endVertex != nullptr) {
    ////    Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black, isDirected);
    ////    edges->Add(newEdge);
    ////}
    Vertex^ startVertex = FindVertexByName(startVertexName);
    Vertex^ endVertex = FindVertexByName(endVertexName);

    if (startVertex != nullptr && endVertex != nullptr) {
        int edgeIndex = 0;
        Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black, isDirected);
        newEdge->SetEdgeIndex(edgeIndex);
        edges->Add(newEdge);

        // Record action for undo
        undoEdges->Add(newEdge);
        undoIsAddEdge->Add(true); // True for "add edge"
    }

}

void Graph::AddEdge(String^ start, String^ end, int weight) {
    Vertex^ startVertex = FindVertexByName(start);
    Vertex^ endVertex = FindVertexByName(end);
    if (startVertex != nullptr && endVertex != nullptr) {
        int edgeIndex = 0;
        Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black);
        newEdge->SetEdgeIndex(edgeIndex);
        edges->Add(newEdge);

        // Record action for undo
        undoEdges->Add(newEdge);
        undoIsAddEdge->Add(true); // True for "add edge"
    }
}
void Graph::AddEdge(bool isCoincideVertex, String^ startVertexName, String^ endVertexName, int weight) {
    Vertex^ startVertex = FindVertexByName(startVertexName);
    Vertex^ endVertex = FindVertexByName(endVertexName);

    if (startVertex != nullptr && endVertex != nullptr) {
        bool isCoincideEdge = false;
        int edgeIndex = 0;
        for each (Edge ^ edge in edges) {
            if ((edge->Start == startVertex && edge->End == endVertex) || (edge->Start == endVertex && edge->End == startVertex)) {
                isCoincideEdge = true;
                edge->IsCoincideEdge = true; // Mark the existing edge as coinciding
                edgeIndex++;
            }
        }
        Edge^ newEdge = gcnew Edge(startVertex, endVertex, weight, System::Drawing::Color::Black);
        edges->Add(newEdge);

        // Record action for undo
        undoEdges->Add(newEdge);
        undoIsAddEdge->Add(true); // True for "add edge"
    }
}
void Graph::AddEdge(bool isCoincideVertex, String^ startVertexName, String^ endVertexName, int weight, bool isDirected) {
    Vertex^ startVertex = FindVertexByName(startVertexName);
    Vertex^ endVertex = FindVertexByName(endVertexName);

    if (startVertex != nullptr && endVertex != nullptr) {
        bool isCoincideEdge = false;
        int edgeIndex = 0;
        for each (Edge ^ edge in edges) {
            if ((edge->Start == startVertex && edge->End == endVertex) || (edge->Start == endVertex && edge->End == startVertex)) {
                isCoincideEdge = true;
                edge->IsCoincideEdge = true; // Mark the existing edge as coinciding
                edgeIndex++;
            }
        }

        Edge^ newEdge = gcnew Edge(isCoincideEdge, startVertex, endVertex, weight, System::Drawing::Color::Black, isDirected);
        newEdge->SetEdgeIndex(edgeIndex);
        edges->Add(newEdge);

        // Record action for undo
        undoEdges->Add(newEdge);
        undoIsAddEdge->Add(true); // True for "add edge"
    }
}
void Graph::RemoveEdge(Edge^ edge) {
    edges->Remove(edge);

    // Record action for undo
    undoEdges->Add(edge);
    undoIsAddEdge->Add(false); // False for "remove edge"
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
        System::Xml::XmlWriterSettings^ settings = gcnew System::Xml::XmlWriterSettings();
        settings->Indent = true;
        System::Xml::XmlWriter^ writer = System::Xml::XmlWriter::Create(fileName, settings);

        writer->WriteStartDocument();
        writer->WriteStartElement("graphml", "http://graphml.graphdrawing.org/xmlns");

        // Write key definitions
        writer->WriteStartElement("key");
        writer->WriteAttributeString("id", "x");
        writer->WriteAttributeString("for", "node");
        writer->WriteAttributeString("attr.name", "x");
        writer->WriteAttributeString("attr.type", "double");
        writer->WriteEndElement(); // key

        writer->WriteStartElement("key");
        writer->WriteAttributeString("id", "y");
        writer->WriteAttributeString("for", "node");
        writer->WriteAttributeString("attr.name", "y");
        writer->WriteAttributeString("attr.type", "double");
        writer->WriteEndElement(); // key

        writer->WriteStartElement("key");
        writer->WriteAttributeString("id", "weight");
        writer->WriteAttributeString("for", "edge");
        writer->WriteAttributeString("attr.name", "weight");
        writer->WriteAttributeString("attr.type", "int");
        writer->WriteEndElement(); // key

        writer->WriteStartElement("key");
        writer->WriteAttributeString("id", "isDirected");
        writer->WriteAttributeString("for", "edge");
        writer->WriteAttributeString("attr.name", "isDirected");
        writer->WriteAttributeString("attr.type", "boolean");
        writer->WriteEndElement(); // key

        writer->WriteStartElement("key");
        writer->WriteAttributeString("id", "isCoincideEdge");
        writer->WriteAttributeString("for", "edge");
        writer->WriteAttributeString("attr.name", "isCoincideEdge");
        writer->WriteAttributeString("attr.type", "boolean");
        writer->WriteEndElement(); // key

        writer->WriteStartElement("key");
        writer->WriteAttributeString("id", "edgeIndex");
        writer->WriteAttributeString("for", "edge");
        writer->WriteAttributeString("attr.name", "edgeIndex");
        writer->WriteAttributeString("attr.type", "int");
        writer->WriteEndElement(); // key

        writer->WriteStartElement("graph");
        writer->WriteAttributeString("id", "G");
        writer->WriteAttributeString("edgedefault", "undirected");

        // Write vertices
        for each (Vertex ^ vertex in vertices) {
            writer->WriteStartElement("node");
            writer->WriteAttributeString("id", vertex->Name);

            writer->WriteStartElement("data");
            writer->WriteAttributeString("key", "x");
            writer->WriteString(vertex->X.ToString());
            writer->WriteEndElement(); // data

            writer->WriteStartElement("data");
            writer->WriteAttributeString("key", "y");
            writer->WriteString(vertex->Y.ToString());
            writer->WriteEndElement(); // data

            writer->WriteEndElement(); // node
        }

        // Write edges
        for each (Edge ^ edge in edges) {
            writer->WriteStartElement("edge");
            writer->WriteAttributeString("source", edge->Start->Name);
            writer->WriteAttributeString("target", edge->End->Name);

            writer->WriteStartElement("data");
            writer->WriteAttributeString("key", "weight");
            writer->WriteString(edge->Weight.ToString());
            writer->WriteEndElement(); // data

            writer->WriteStartElement("data");
            writer->WriteAttributeString("key", "directed");
            writer->WriteString(edge->Directed.ToString());
            writer->WriteEndElement(); // data

            writer->WriteStartElement("data");
            writer->WriteAttributeString("key", "isCoincideEdge");
            writer->WriteString(edge->IsCoincideEdge.ToString());
            writer->WriteEndElement(); // data

            writer->WriteStartElement("data");
            writer->WriteAttributeString("key", "edgeIndex");
            writer->WriteString(edge->GetEdgeIndex().ToString());
            writer->WriteEndElement(); // data

            writer->WriteEndElement(); // edge
        }

        writer->WriteEndElement(); // graph
        writer->WriteEndElement(); // graphml
        writer->WriteEndDocument();
        writer->Close();
    }
    catch (Exception^ ex) {
        // Handle any exceptions that occur during file writing
        Console::WriteLine("Error saving file: " + ex->Message);
    }
}
void Graph::LoadFromFile(String^ fileName) {
    try {
        Clear(); // Clear existing graph data
        System::Xml::XmlDocument^ doc = gcnew System::Xml::XmlDocument();
        doc->Load(fileName);

        System::Xml::XmlNamespaceManager^ nsmgr = gcnew System::Xml::XmlNamespaceManager(doc->NameTable);
        nsmgr->AddNamespace("g", "http://graphml.graphdrawing.org/xmlns");

        // Load vertices
        System::Xml::XmlNodeList^ nodeList = doc->SelectNodes("//g:graph/g:node", nsmgr);
        for each (System::Xml::XmlNode ^ node in nodeList) {
            String^ name = node->Attributes["id"]->Value;
            float x = System::Single::Parse(node->SelectSingleNode("g:data[@key='x']", nsmgr)->InnerText);
            float y = System::Single::Parse(node->SelectSingleNode("g:data[@key='y']", nsmgr)->InnerText);

            Vertex^ vertex = gcnew Vertex(vertices->Count, name, x, y);
            AddVertex(vertex);
        }

        // Load edges
        System::Xml::XmlNodeList^ edgeList = doc->SelectNodes("//g:graph/g:edge", nsmgr);
        for each (System::Xml::XmlNode ^ edge in edgeList) {
            String^ sourceName = edge->Attributes["source"]->Value;
            String^ targetName = edge->Attributes["target"]->Value;
            int weight = System::Int32::Parse(edge->SelectSingleNode("g:data[@key='weight']", nsmgr)->InnerText);
            bool directed = System::Boolean::Parse(edge->SelectSingleNode("g:data[@key='directed']", nsmgr)->InnerText);
            bool isCoincideEdge = System::Boolean::Parse(edge->SelectSingleNode("g:data[@key='isCoincideEdge']", nsmgr)->InnerText);
            int edgeIndex = System::Int32::Parse(edge->SelectSingleNode("g:data[@key='edgeIndex']", nsmgr)->InnerText);

            Vertex^ startVertex = FindVertexByName(sourceName);
            Vertex^ endVertex = FindVertexByName(targetName);

            if (startVertex != nullptr && endVertex != nullptr) {
                Edge^ newEdge = gcnew Edge(isCoincideEdge, startVertex, endVertex, weight, System::Drawing::Color::Black, directed);
                newEdge->SetEdgeIndex(edgeIndex);
                AddEdge(newEdge);
            }
        }
    }
    catch (System::Exception^ e) {
        // Handle any exceptions (e.g., file access issues, parsing errors)
        System::Windows::Forms::MessageBox::Show("Error loading graph: " + e->Message);
    }

}
void Graph::Undo() {
    if (undoEdges->Count > 0 && undoIsAddEdge->Count > 0) {
        Edge^ edge = undoEdges[undoEdges->Count - 1];
        bool isAddEdge = undoIsAddEdge[undoIsAddEdge->Count - 1];

        if (isAddEdge) {
            UndoAddEdge(edge);
        }
        else {
            UndoRemoveEdge(edge);
        }

        undoEdges->RemoveAt(undoEdges->Count - 1);
        undoIsAddEdge->RemoveAt(undoIsAddEdge->Count - 1);
    }
    else if (undoVertices->Count > 0 && undoIsAddVertex->Count > 0) {
        Vertex^ vertex = undoVertices[undoVertices->Count - 1];
        bool isAddVertex = undoIsAddVertex[undoIsAddVertex->Count - 1];

        if (isAddVertex) {
            vertices->Remove(vertex);
        }
        else {
            vertices->Add(vertex);
        }

        undoVertices->RemoveAt(undoVertices->Count - 1);
        undoIsAddVertex->RemoveAt(undoIsAddVertex->Count - 1);
    }
}
void Graph::Clear() {
    vertices->Clear();
    edges->Clear();
    undoEdges->Clear();
    undoIsAddEdge->Clear();

}
void Graph::UndoRemoveVertex(Vertex^ vertex) {
    vertices->Add(vertex);
    // Re-add edges connected to this vertex
    for each (Edge ^ edge in edges) {
        if (edge->Start == vertex || edge->End == vertex) {
            edges->Add(edge);
        }
    }
}

void Graph::UndoAddVertex(Vertex^ vertex) {
    vertices->Remove(vertex);
    // Remove edges connected to this vertex
    edges->RemoveAll(gcnew Predicate<Edge^>(this, &Graph::EdgeContainsVertex));
}
//void Graph::MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
//    if (e->KeyCode == Keys::Z && e->Control) {
//        Undo();
//    }
//}
