
#pragma once

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

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

	private:
		System::ComponentModel::Container^ components;
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::TextBox^ infoPanel;
		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ loadToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ editToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ changeEdgeColorToolStripMenuItem;
		System::Windows::Forms::ToolStripButton^ addEdgeButton;
		System::Windows::Forms::ToolStripButton^ showGridButton;
		System::Windows::Forms::ToolStripButton^ deleteEdgeButton;
		System::Windows::Forms::ToolStripButton^ saveButton;
		System::Windows::Forms::ToolStripButton^ loadButton;
		System::Windows::Forms::ToolStripButton^ runDijkstraButton;
		System::Windows::Forms::ToolStrip^ toolStrip1;
		String^ PromptForVertexName();
		Graph^ graph;
		Vertex^ selectedVertex;
		Vertex^ draggingVertex;
		bool isDrawingEdge;
		static Drawing::Color currentEdgeColor = Drawing::Color::Black;

	private:
		System::Void ShowGridButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void AddEdgeButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void DeleteEdgeButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void RunDijkstraButton_Click(System::Object^ sender, System::EventArgs^ e);
		void RunDijkstra(Vertex^ start, Vertex^ end);

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
		bool showGrid = false;
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
