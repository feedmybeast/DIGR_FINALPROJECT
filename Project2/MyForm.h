#pragma once
#include <cstdint>
#include <vcclr.h>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#define WM_MOUSEWHEEL 0x020A
#include<stack>

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
			draggingVertex = nullptr;
			isDrawingEdge = false;
			currentEdgeColor = System::Drawing::Color::Black;
			zoomFactor = 1.0f;
			offset = PointF(0, 0);
			viewOffsetX = 0.0f;
			viewOffsetY = 0.0f;
			isPanning = false;
			gridWidth = 1000;
			gridHeight = 1000;
			needsGridExpansion = false;
			gridSize = 20;
		}

		String^ shortpath;

	private:
		System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;


		static const float GRID_SIZE = 20.0f;
		Vertex^ draggingVertex;
		PointF offset;
		bool isDragging;

		Vertex^ draggedVertex;
		Point lastMousePosition;
		bool showGrid = false;
		bool isDrawingEdge = false;
		Vertex^ selectedVertex;
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
		System::Windows::Forms::ToolStripButton^ zoomInButton;
		System::Windows::Forms::ToolStripButton^ zoomOutButton;
		System::Windows::Forms::ToolStripButton^ resetZoomButton;
		System::Windows::Forms::ToolStripButton^ clearButton;
		System::Windows::Forms::MouseButtons mouseButtonClicked;
		System::Windows::Forms::RadioButton^ defaultRadioButton;
		System::Windows::Forms::RadioButton^ directedRadioButton;
		System::Windows::Forms::RadioButton^ undirectedRadioButton;
		System::Windows::Forms::Timer^ clickTimer;
		System::Windows::Forms::ComboBox^ directionComboBox;

		System::Void ZoomIn(System::Object^ sender, System::EventArgs^ e);
		System::Void ZoomOut(System::Object^ sender, System::EventArgs^ e);
		System::Void ResetZoom(System::Object^ sender, System::EventArgs^ e);
		System::Void defaultRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void directedRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void undirectedRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		//void MyForm::DrawArrowWithPointF(Graphics^ g, PointF start, PointF end);

		System::Windows::Forms::ToolStrip^ toolStrip1;

		String^ PromptForVertexName();
		String^ PromptForEditVertex(String^ title);

		void MyForm::AddVertexAtCursor(Point cursorPosition);
		void MyForm::ClearGraph();
		Graph^ graph;
		float zoomFactor;
		System::Drawing::Color currentEdgeColor;

		float viewOffsetX;
		float viewOffsetY;

		Point potentialDragStart;

		bool isPanning;
		Point lastMousePos;

		bool single_Click = true;
		bool doubleClickOccured = false;

		void AdjustVerticesToGrid();
		System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void ZoomInButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ZoomOutButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ResetZoomButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void pictureBox1_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void ClearButton_Click(System::Object^ sender, System::EventArgs^ e);
		int mouseX;
		int mouseY;
		void DrawArrow(Graphics^ g, Vertex^ start, Vertex^ end);


		int gridWidth;
		int gridHeight;
		bool needsGridExpansion;
		int gridSize;
	private:
		System::Void ShowGridButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void AddEdgeButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void DeleteEdgeButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void RunDijkstraButton_Click(System::Object^ sender, System::EventArgs^ e);
		void RunDijkstra(Vertex^ start, Vertex^ end);
		System::Windows::Forms::TextBox^ infoPanel3;
		System::Windows::Forms::TextBox^ infoPanel4;
		void MyForm::UpdateInfoPanel3();
		//void MyForm::UpdateInfoPanel4();
	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
		void InitializeComponent(void);
		void DrawGraph(Graphics^ g);
		Vertex^ FindVertexAtPoint(float x, float y);
		Edge^ FindEdgeAtPoint(int x, int y);
		void DeleteVertex(Vertex^ vertex);
		void DeleteEdge(Edge^ edge);
		void UpdateInfoPanel();
		void MyForm::DrawLoopDirectedEdge(Graphics^ g, Edge^ edge, float offsetX, float offsetY);
	protected:
		virtual void WndProc(System::Windows::Forms::Message% m) override {
			if (m.Msg == WM_MOUSEWHEEL) {
				int64_t lParam = m.LParam.ToInt64();
				int64_t wParam = m.WParam.ToInt64();
				int xPos = static_cast<int>(lParam & 0xFFFF);
				int yPos = static_cast<int>((lParam >> 16) & 0xFFFF);
				int delta = static_cast<int>((wParam >> 16) & 0xFFFF);
				this->OnMouseWheel(gcnew System::Windows::Forms::MouseEventArgs(System::Windows::Forms::MouseButtons::None, 0, xPos, yPos, delta));
			}
			System::Windows::Forms::Form::WndProc(m);
		}
		System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void pictureBox1_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void clickTimer_Tick(System::Object^ sender, System::EventArgs^ e);
		System::Void SaveGraph(System::Object^ sender, System::EventArgs^ e);
		System::Void LoadGraph(System::Object^ sender, System::EventArgs^ e);
		System::Void ChangeEdgeColor(System::Object^ sender, System::EventArgs^ e);
		bool IsVertexNameExist(String^ name);




	};

}
