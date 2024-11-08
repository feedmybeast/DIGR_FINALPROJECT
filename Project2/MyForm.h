
#pragma once

namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

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

	public ref class Edge
	{
	public:
		Edge(int id, Vertex^ start, Vertex^ end, int weight, String^ color) : id(id), start(start), end(end), weight(weight), color(color) {}
		property int Id { int get() { return id; } }
		property Vertex^ Start { Vertex^ get() { return start; } }
		property Vertex^ End { Vertex^ get() { return end; } }
		property int Weight { int get() { return weight; } void set(int value) { weight = value; } }
		property String^ Color { String^ get() { return color; } void set(String^ value) { color = value; } }
	private:
		int id;
		Vertex^ start;
		Vertex^ end;
		int weight;
		String^ color;
	};

	public ref class Graph
	{
	public:
		Graph() : vertices(gcnew List<Vertex^>()), edges(gcnew List<Edge^>()) {}

		void AddVertex(Vertex^ vertex) { vertices->Add(vertex); }
		void AddEdge(Edge^ edge) { edges->Add(edge); }

		void RemoveVertex(int id)
		{
			this->id = id; // Set the id to be used in the predicate
			vertices->RemoveAll(gcnew Predicate<Vertex^>(this, &Graph::VertexIdPredicate));
		}

		void RemoveEdge(int id)
		{
			this->id = id; // Set the id to be used in the predicate
			edges->RemoveAll(gcnew Predicate<Edge^>(this, &Graph::EdgeIdPredicate));
		}

		property List<Vertex^>^ Vertices { List<Vertex^>^ get() { return vertices; } }
		property List<Edge^>^ Edges { List<Edge^>^ get() { return edges; } }

	private:
		List<Vertex^>^ vertices;
		List<Edge^>^ edges;

		// Store the id to be used in the predicates
		int id;

		// Predicate method for vertices
		bool VertexIdPredicate(Vertex^ v)
		{
			return v->Id == id;
		}

		// Predicate method for edges
		bool EdgeIdPredicate(Edge^ e)
		{
			return e->Id == id;
		}
	};

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			graph = gcnew Graph();
			selectedVertex = nullptr;
			isDrawingEdge = false;
			currentEdgeColor = Color::Black;
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container ^components;
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::TextBox^ infoPanel;
		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ loadToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ editToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ changeEdgeColorToolStripMenuItem;

		Graph^ graph;
		Vertex^ selectedVertex;
		bool isDrawingEdge;
		Color currentEdgeColor;

		void InitializeComponent(void);
		void DrawGraph(Graphics^ g);
		Vertex^ FindVertexAtPoint(int x, int y);
		Edge^ FindEdgeAtPoint(int x, int y);
		void AddEdge(Vertex^ start, Vertex^ end);
		void DeleteVertex(Vertex^ vertex);
		void DeleteEdge(Edge^ edge);
		void UpdateInfoPanel();

		System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void SaveGraph(System::Object^ sender, System::EventArgs^ e);
		System::Void LoadGraph(System::Object^ sender, System::EventArgs^ e);
		System::Void ChangeEdgeColor(System::Object^ sender, System::EventArgs^ e);
	};
}
