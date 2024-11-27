
// MyForm.cpp
// Implementation of the MyForm class for a graph editor application

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "MyForm.h"
#include "Graph.h"
#include <cmath> 
#include <msclr\marshal_cppstd.h>
#include<string>
#include <sstream>
#include <fstream>
#include <vcclr.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace System;
using namespace System::Drawing::Drawing2D;
using namespace System::Collections::Generic;
#using <Microsoft.VisualBasic.dll>
namespace Project2 {
	// InitializeComponent: Initializes all the UI components of the form
	void MyForm::InitializeComponent(void)
	{
		// Set KeyPreview to true
		this->KeyPreview = true;
		// Initialize and configure the default radio button
		this->defaultRadioButton = (gcnew System::Windows::Forms::RadioButton());
		this->defaultRadioButton->AutoSize = true;
		this->defaultRadioButton->Checked = true;
		this->defaultRadioButton->Location = System::Drawing::Point(700, 90);
		this->defaultRadioButton->Name = L"defaultRadioButton";
		this->defaultRadioButton->Size = System::Drawing::Size(59, 17);
		this->defaultRadioButton->TabIndex = 6;
		this->defaultRadioButton->TabStop = true;
		this->defaultRadioButton->Text = L"Default";
		this->defaultRadioButton->UseVisualStyleBackColor = true;
		this->defaultRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::defaultRadioButton_CheckedChanged);
		// Add KeyDown event handler
		this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
		// Add the defaultRadioButton to the form's controls
		this->Controls->Add(this->defaultRadioButton);

		// Dummy call to DrawArrow to force linking (compiler optimization)
		if (false) {
			DrawArrow(nullptr, nullptr, nullptr);
		}

		// Initialize other UI components
		this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
		this->infoPanel = (gcnew System::Windows::Forms::TextBox());
		this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
		this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->changeEdgeColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
		this->addEdgeButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->deleteEdgeButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->showGridButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->showGridButton->Text = L"Show Grid";
		this->showGridButton->Click += gcnew System::EventHandler(this, &MyForm::ShowGridButton_Click);
		this->undirectedRadioButton = (gcnew System::Windows::Forms::RadioButton());
		this->directedRadioButton = (gcnew System::Windows::Forms::RadioButton());
		this->directedRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::directedRadioButton_CheckedChanged);
		this->undirectedRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::undirectedRadioButton_CheckedChanged);

		// The buttons are now added directly to the toolStrip1 in the Items->AddRange call

		// Set form properties

		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(870, 700);
		this->Controls->Add(this->pictureBox1);
		this->Controls->Add(this->infoPanel);
		//this->Controls->Add(this->undirectedRadioButton);
		//this->Controls->Add(this->directedRadioButton);
		//this->Controls->Add(this->menuStrip1);
		this->Controls->Add(this->toolStrip1);
		//this->MainMenuStrip = this->menuStrip1;
		this->Name = L"MyForm";
		this->Text = L"DIGR_TEAM09_VISUAL GRAPH DRAWING PROJECT";
		this->ResumeLayout(false);
		this->PerformLayout();

		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
		this->menuStrip1->SuspendLayout();
		this->SuspendLayout();

		// pictureBox1
		this->pictureBox1->Location = System::Drawing::Point(12, 27);
		this->pictureBox1->Name = L"pictureBox1";
		this->pictureBox1->Size = System::Drawing::Size(680, 650);
		this->pictureBox1->TabIndex = 0;
		this->pictureBox1->TabStop = false;
		this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
		this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseClick);
		this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
		this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
		this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
		this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pictureBox1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseWheel);
		this->pictureBox1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDoubleClick);

		// infoPanel 2
		this->infoPanel->Location = System::Drawing::Point(12, 27);
		this->infoPanel->Name = L"infoPanel";
		this->infoPanel->Size = System::Drawing::Size(558, 392);
		this->infoPanel->TabIndex = 0;
		this->infoPanel->TabStop = false;
		// Initialize and configure infoPanel3
		this->infoPanel3 = (gcnew System::Windows::Forms::TextBox());
		this->infoPanel3->Location = System::Drawing::Point(690, 135); // Adjust the position to the middle of the right blank space
		this->infoPanel3->Name = L"infoPanel3";
		this->infoPanel3->Size = System::Drawing::Size(180, 120); // Adjust the size as needed
		this->infoPanel3->TabIndex = 1;
		this->infoPanel3->ReadOnly = true;
		this->infoPanel3->Multiline = true;
		this->infoPanel3->Enabled = false;
		this->infoPanel3->ForeColor = System::Drawing::Color::Black;	
		this->infoPanel3->Font = gcnew System::Drawing::Font(this->infoPanel3->Font, System::Drawing::FontStyle::Bold);
		this->Controls->Add(this->infoPanel3);
		// Initialize and configure infoPanel4
		this->infoPanel4 = (gcnew System::Windows::Forms::TextBox());
		this->infoPanel4->Location = System::Drawing::Point(690, 250); // Adjust the position to the middle of the right blank space
		this->infoPanel4->Name = L"infoPanel4";
		this->infoPanel4->Size = System::Drawing::Size(180, 120); // Adjust the size as needed
		this->infoPanel4->TabIndex = 1;
		this->infoPanel4->ReadOnly = true;
		this->infoPanel4->Multiline = true;
		this->infoPanel4->Enabled = false; // Add this line to make it read-only and non-interactive
		this->Controls->Add(this->infoPanel4);
		//this->infoPanel4->Font = gcnew System::Drawing::Font(this->infoPanel4->Font, System::Drawing::FontStyle::Bold);
		this->infoPanel4->ForeColor = System::Drawing::Color::Black;
		this->infoPanel4->Text = "Group_09\r\nBui Tran Tan Phat_23110052\r\nNguyen Nhat Phat_23110053\r\nTran Huynh Xuan Thanh_23110060";
		//CLick timer (for diff between single and double click)
		this->clickTimer = (gcnew System::Windows::Forms::Timer());
		this->clickTimer->Interval = SystemInformation::DoubleClickTime;
		this->clickTimer->Tick += gcnew System::EventHandler(this, &MyForm::clickTimer_Tick);

		// saveToolStripMenuItem
		this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
		this->saveToolStripMenuItem->Size = System::Drawing::Size(180, 22);
		this->saveToolStripMenuItem->Text = L"Save";
		this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::SaveGraph);

		// loadToolStripMenuItem
		this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
		this->loadToolStripMenuItem->Size = System::Drawing::Size(180, 22);
		this->loadToolStripMenuItem->Text = L"Load";
		this->loadToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::LoadGraph);

		// changeEdgeColorToolStripMenuItem
		this->changeEdgeColorToolStripMenuItem->Name = L"changeEdgeColorToolStripMenuItem";
		this->changeEdgeColorToolStripMenuItem->Size = System::Drawing::Size(180, 22);
		this->changeEdgeColorToolStripMenuItem->Text = L"Change Edge Color";

		// Event handler for changing the edge color
		this->changeEdgeColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ChangeEdgeColor);

		this->addEdgeButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->addEdgeButton->Text = L"Add Edge";

		// Event handler for adding a new edge
		this->addEdgeButton->Click += gcnew System::EventHandler(this, &MyForm::AddEdgeButton_Click);

		this->deleteEdgeButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->deleteEdgeButton->Text = L"Delete Edge";

		// Event handler for deleting an edge
		this->deleteEdgeButton->Click += gcnew System::EventHandler(this, &MyForm::DeleteEdgeButton_Click);

		this->zoomInButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->zoomInButton->Text = L"Zoom In";

		// Event handler for zooming in
		this->zoomInButton->Click += gcnew System::EventHandler(this, &MyForm::ZoomInButton_Click);

		this->zoomOutButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->zoomOutButton->Text = L"Zoom Out";
		// Event handler for zooming out
		this->zoomOutButton->Click += gcnew System::EventHandler(this, &MyForm::ZoomOutButton_Click);

		this->resetZoomButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->resetZoomButton->Text = L"Reset Zoom";

		// Event handler for resetting the zoom level
		this->resetZoomButton->Click += gcnew System::EventHandler(this, &MyForm::ResetZoomButton_Click);

		this->clearButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->clearButton->Text = L"Clear";
		// Event handler for clearing the graph or network diagram
		this->clearButton->Click += gcnew System::EventHandler(this, &MyForm::ClearButton_Click);

		this->runDijkstraButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->runDijkstraButton->Text = L"Run Dijkstra";

		// Event handler for running Dijkstra's algorithm
		this->runDijkstraButton->Click += gcnew System::EventHandler(this, &MyForm::RunDijkstraButton_Click);

		this->showGridButton = (gcnew System::Windows::Forms::ToolStripButton());
		this->showGridButton->Text = L"Show Grid";

		// fix size window
		this->WindowState = System::Windows::Forms::FormWindowState::Normal;
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Icon = gcnew System::Drawing::Icon("digr.ico");
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		// Event handler for toggling the grid visibility
		this->showGridButton->Click += gcnew System::EventHandler(this, &MyForm::ShowGridButton_Click);

		System::Collections::Generic::List<System::Windows::Forms::ToolStripItem^>^ items = gcnew System::Collections::Generic::List<System::Windows::Forms::ToolStripItem^>();

		// List of items in tools strip
		items->Add(this->addEdgeButton);
		items->Add(this->deleteEdgeButton);
		items->Add(gcnew System::Windows::Forms::ToolStripSeparator());
		items->Add(this->zoomInButton);
		items->Add(this->zoomOutButton);
		items->Add(this->resetZoomButton);
		items->Add(gcnew System::Windows::Forms::ToolStripSeparator());
		items->Add(this->showGridButton);
		items->Add(this->clearButton);
		items->Add(this->runDijkstraButton);
		items->Add(gcnew System::Windows::Forms::ToolStripSeparator());
		items->Add(gcnew System::Windows::Forms::ToolStripButton(L"Save", nullptr, gcnew System::EventHandler(this, &MyForm::SaveGraph)));
		items->Add(gcnew System::Windows::Forms::ToolStripButton(L"Load", nullptr, gcnew System::EventHandler(this, &MyForm::LoadGraph)));

		this->toolStrip1->Items->AddRange(items->ToArray());

		// undirectedRadioButton
		this->undirectedRadioButton->Location = System::Drawing::Point(700, 50);
		this->undirectedRadioButton->Name = L"undirectedRadioButton";
		this->undirectedRadioButton->Size = System::Drawing::Size(100, 20);
		this->undirectedRadioButton->TabIndex = 4;
		this->undirectedRadioButton->TabStop = true;
		this->undirectedRadioButton->Text = L"Undirected";
		this->undirectedRadioButton->UseVisualStyleBackColor = true;
		this->Controls->Add(this->undirectedRadioButton);

		// directedRadioButton
		this->directedRadioButton->Location = System::Drawing::Point(700, 70);
		this->directedRadioButton->Name = L"directedRadioButton";
		this->directedRadioButton->Size = System::Drawing::Size(104, 24);
		this->directedRadioButton->TabIndex = 1;
		this->directedRadioButton->TabStop = true;
		this->directedRadioButton->Text = L"Directed";
		this->directedRadioButton->UseVisualStyleBackColor = true;
		this->Controls->Add(this->directedRadioButton);

	}

	// ShowInputBox: Helper function to display an input dialog box
	String^ ShowInputBox(String^ prompt, String^ title, String^ defaultValue) {
		Form^ inputBox = gcnew Form();
		inputBox->Width = 300;
		inputBox->Height = 150;
		inputBox->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedDialog;
		inputBox->Text = title;
		inputBox->StartPosition = FormStartPosition::CenterScreen;

		Label^ label = gcnew Label();
		label->Left = 10;
		label->Top = 20;
		label->Text = prompt;
		label->AutoSize = true;

		TextBox^ textBox = gcnew TextBox();
		textBox->Left = 10;
		textBox->Top = 50;
		textBox->Width = 260;
		textBox->Text = defaultValue;

		Button^ okButton = gcnew Button();
		okButton->Text = "OK";
		okButton->Left = 10;
		okButton->Top = 80;
		okButton->DialogResult = System::Windows::Forms::DialogResult::OK;

		Button^ cancelButton = gcnew Button();	
		cancelButton->Text = "Cancel";
		cancelButton->Left = 90;
		cancelButton->Top = 80;
		cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;

		inputBox->Controls->Add(label);
		inputBox->Controls->Add(textBox);
		inputBox->Controls->Add(okButton);
		inputBox->Controls->Add(cancelButton);
		inputBox->AcceptButton = okButton;
		inputBox->CancelButton = cancelButton;

		return inputBox->ShowDialog() == System::Windows::Forms::DialogResult::OK ? textBox->Text : "";
	}

	// FindVertexAtPoint: Finds a vertex at the given coordinates (x, y)
	Vertex^ MyForm::FindVertexAtPoint(float x, float y) {
		for each (Vertex ^ v in graph->Vertices) {
			if (Math::Abs(v->X - x) < 10 && Math::Abs(v->Y - y) < 10) {
				return v;
			}
		}
		return nullptr;
	}

	// FindEdgeAtPoint: Finds an edge near the given coordinates (x, y)
	Edge^ MyForm::FindEdgeAtPoint(int x, int y) {
		for each (Edge ^ e in graph->Edges) {
			//float x1 = e->Start->X, y1 = e->Start->Y, x2 = e->End->X, y2 = e->End->Y;
			//double distance = Math::Abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1) /
			//	Math::Sqrt(Math::Pow(y2 - y1, 2) + Math::Pow(x2 - x1, 2));
			//if (distance < 5) {
			//	return e;
			//}
			if (e->IsCoincideEdge) {
				//// Handle curved edge (quadratic Bezier curve)
				//float midX = (e->Start->X + e->End->X) / 2;
				//float midY = (e->Start->Y + e->End->Y) / 2;
				//float dx = e->End->X - e->Start->X;
				//float dy = e->End->Y - e->Start->Y;
				//float edgeIndex = e->GetEdgeIndex();
				//float curveFactor = 30 + (edgeIndex * 10); // Adjust curvature based on edge index
				//float controlX = midX - dy * (curveFactor / std::sqrt(dx * dx + dy * dy));
				//float controlY = midY + dx * (curveFactor / std::sqrt(dx * dx + dy * dy));
				//float x1 = e->Start->X, y1 = e->Start->Y;
				//float x2 = controlX, y2 = controlY; // Control point for the curve
				//float x3 = e->End->X, y3 = e->End->Y;

				//// Check distance from point (x, y) to the Bezier curve
				//for (float t = 0; t <= 1; t += 0.01f) {
				//	float xt = (1 - t) * (1 - t) * x1 + 2 * (1 - t) * t * x2 + t * t * x3;
				//	float yt = (1 - t) * (1 - t) * y1 + 2 * (1 - t) * t * y2 + t * t * y3;
				//	float distance = std::sqrt(std::pow(xt - x, 2) + std::pow(yt - y, 2));
				//	if (distance < 5) {
				//		return e;
				//	}
				//}
				// Handle curved edge (quadratic Bezier curve)
				float midX = (e->Start->X + e->End->X) / 2;
				float midY = (e->Start->Y + e->End->Y) / 2;
				float dx = e->End->X - e->Start->X;
				float dy = e->End->Y - e->Start->Y;
				float edgeIndex = e->GetEdgeIndex();
				float curveFactor = 30 + (edgeIndex * 10); // Adjust curvature based on edge index
				float controlX = midX - dy * (curveFactor / std::sqrt(dx * dx + dy * dy));
				float controlY = midY + dx * (curveFactor / std::sqrt(dx * dx + dy * dy));
				array<PointF>^ curvePoints = { PointF(e->Start->X, e->Start->Y),
											   PointF(controlX, controlY),
											   PointF(e->End->X, e->End->Y) };

				// Iterate over the curve points to check the distance
				for (int i = 0; i < curvePoints->Length - 1; i++) {
					PointF p1 = curvePoints[i];
					PointF p2 = curvePoints[i + 1];
					for (float t = 0; t <= 1; t += 0.001f) { // Smaller step size for better precision
						float xt = p1.X + t * (p2.X - p1.X);
						float yt = p1.Y + t * (p2.Y - p1.Y);
						float distance = std::sqrt(std::pow(xt - x, 2) + std::pow(yt - y, 2));
						if (distance < 5) {
							return e;
						}
					}
				}
			}
			else {
				// Handle straight edge
				float x1 = e->Start->X, y1 = e->Start->Y, x2 = e->End->X, y2 = e->End->Y;
				double distance = Math::Abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1) /
					Math::Sqrt(Math::Pow(y2 - y1, 2) + Math::Pow(x2 - x1, 2));
				if (distance < 5) {
					return e;
				}
			}
		}
		return nullptr;
		//Find edge at point

	}


	// DeleteVertex: Removes a vertex from the graph and updates the UI
	void MyForm::DeleteVertex(Vertex^ vertex) {
		graph->RemoveVertex(vertex);
		UpdateInfoPanel();
		pictureBox1->Invalidate();
		UpdateInfoPanel3();
	}

	// DeleteEdge: Removes an edge from the graph and updates the UI
	void MyForm::DeleteEdge(Edge^ edge) {
		graph->RemoveEdge(edge);
		UpdateInfoPanel();
		pictureBox1->Invalidate();
		UpdateInfoPanel3();
	}

	// UpdateInfoPanel: Updates the information panel with current graph statistics
	void MyForm::UpdateInfoPanel() {
		infoPanel->Text = "Vertices: " + graph->Vertices->Count + "\r\n";
		infoPanel->Text += "Edges: " + graph->Edges->Count + "\r\n";
	}
	void MyForm::UpdateInfoPanel3()
	{
		int vertexCount = graph->Vertices->Count;
		int edgeCount = graph->Edges->Count;
		this->infoPanel3->Text = "Vertices: " + vertexCount + "\r\nEdges: " + edgeCount + "\n";
		this->infoPanel3->Text += shortpath;
		//this->Invalidate();
		pictureBox1->Invalidate();
	}
	//void MyForm::UpdateInfoPanel4()
	//{
	//	this->infoPanel4->Text = "Bui Tran Tan Phat - 23110052\nNguyen Nhat Phat - 23110053\nTran Huynh Xuan Thanh - 23110060";
	//	//shortpath = "";
	//	////this->Invalidate();
	//	pictureBox1->Invalidate();
	//}
	// pictureBox1_Paint: Handles the painting of the graph on the picture box
	bool flag = nullptr;
	System::Void MyForm::pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
		Graphics^ g = e->Graphics;
		g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
		g->Clear(Color::White);

		// Apply zoom and pan transformations
		g->TranslateTransform(viewOffsetX, viewOffsetY);
		g->ScaleTransform(zoomFactor, zoomFactor);

		// Draw grid if showGrid is true
		if (showGrid)
		{
			Pen^ gridPen = gcnew Pen(Color::LightGray, 1 / zoomFactor);
			int gridStep = 20; // Adjust this value to change grid density
			float width = pictureBox1->Width / zoomFactor;
			float height = pictureBox1->Height / zoomFactor;

			// Calculate the visible area in graph coordinates
			float left = -viewOffsetX / zoomFactor;
			float top = -viewOffsetY / zoomFactor;
			float right = left + width;
			float bottom = top + height;

			// Adjust grid lines to be within the visible area
			float startX = Math::Floor(left / gridStep) * gridStep;
			float startY = Math::Floor(top / gridStep) * gridStep;
			float endX = Math::Ceiling(right / gridStep) * gridStep;
			float endY = Math::Ceiling(bottom / gridStep) * gridStep;

			for (float x = startX; x <= endX; x += gridStep)
			{
				g->DrawLine(gridPen, x, top, x, bottom);
			}

			for (float y = startY; y <= endY; y += gridStep)
			{
				g->DrawLine(gridPen, left, y, right, y);
			}

			delete gridPen;
		}


		for each (Edge ^ edge in graph->Edges)
		{
			float angle2;
			if (edge->Start != edge->End)
			{

				if (edge->IsCoincideEdge == true)
				{
					Pen^ pen = gcnew Pen(edge->Color, 2 / zoomFactor);
					float midX = (edge->Start->X + edge->End->X) / 2;
					float midY = (edge->Start->Y + edge->End->Y) / 2;
					float dx = edge->End->X - edge->Start->X;
					float dy = edge->End->Y - edge->Start->Y;
					float edgeIndex = edge->GetEdgeIndex();
					float curveFactor = 30 + (edgeIndex * 10); // Adjust curvature based on edge index
					float controlX = midX - dy * (curveFactor / std::sqrt(dx * dx + dy * dy));
					float controlY = midY + dx * (curveFactor / std::sqrt(dx * dx + dy * dy));
					array<PointF>^ curvePoints = { PointF(edge->Start->X, edge->Start->Y),
						PointF(controlX, controlY),
						PointF(edge->End->X, edge->End->Y) };
					g->DrawCurve(pen, curvePoints);

					//}
					delete pen;
					PointF labelPoint(controlX, controlY);
					System::Drawing::Font^ largerFont = gcnew System::Drawing::Font(this->Font->FontFamily, this->Font->Size * 1.2f, System::Drawing::FontStyle::Bold);
					for (int dx = -1; dx <= 1; ++dx) {
						for (int dy = -1; dy <= 1; ++dy) {
							if (dx != 0 || dy != 0) {
								g->DrawString(edge->Weight.ToString(), largerFont, Brushes::White, labelPoint.X + dx, labelPoint.Y + dy);
							}
						}
					}
					
					g->DrawString(edge->Weight.ToString(), largerFont, Brushes::Black, labelPoint);

					if (edge->Directed && undirectedRadioButton->Checked)
					{
						flag = true;
					}

					if (edge->Directed && directedRadioButton->Checked)
					{
						flag = false;
						// Calculate the direction vector
						float arrowDx = edge->End->X - controlX;
						float arrowDy = edge->End->Y - controlY;
						float length = std::sqrt(arrowDx * arrowDx + arrowDy * arrowDy);
						// Normalize the direction vector
						arrowDx /= length;
						arrowDy /= length;
						// Define the size of the arrowhead
						float arrowSize = 15.0f;

						// Move the arrowhead away from the vertex point
						float offset = 7.0f; // Adjust this value to move the arrowhead further away
						PointF arrowTip = PointF(
							edge->End->X - offset * arrowDx,
							edge->End->Y - offset * arrowDy
						);

						// Calculate the points for the arrowhead
						PointF arrowPoint1 = PointF(
							arrowTip.X - arrowSize * (arrowDx * std::cos(M_PI / 6) - arrowDy * std::sin(M_PI / 6)),
							arrowTip.Y - arrowSize * (arrowDy * std::cos(M_PI / 6) + arrowDx * std::sin(M_PI / 6))
						);
						PointF arrowPoint2 = PointF(
							arrowTip.X - arrowSize * (arrowDx * std::cos(-M_PI / 6) - arrowDy * std::sin(-M_PI / 6)),
							arrowTip.Y - arrowSize * (arrowDy * std::cos(-M_PI / 6) + arrowDx * std::sin(-M_PI / 6))
						);

						// Draw the arrowhead
						array<PointF>^ arrowHead = { arrowTip, arrowPoint1, arrowPoint2 };
						g->FillPolygon(Brushes::DarkCyan, arrowHead);
					}
					if (edge->Directed && undirectedRadioButton->Checked)
					{
						flag = true;
					}
					if (edge->Directed && directedRadioButton->Checked)
					{
						flag = false;
							// Calculate the direction vector
							float arrowDx = edge->End->X - controlX;
							float arrowDy = edge->End->Y - controlY;
							float length = std::sqrt(arrowDx * arrowDx + arrowDy * arrowDy);

							// Normalize the direction vector
							arrowDx /= length;
							arrowDy /= length;

							// Define the size of the arrowhead
							float arrowSize = 15.0f;

							// Move the arrowhead away from the vertex point
							float offset = 7.0f; // Adjust this value to move the arrowhead further away
							PointF arrowTip = PointF(
								edge->End->X - offset * arrowDx,
								edge->End->Y - offset * arrowDy
							);

							// Calculate the points for the arrowhead
							PointF arrowPoint1 = PointF(
								arrowTip.X - arrowSize * (arrowDx * std::cos(M_PI / 6) - arrowDy * std::sin(M_PI / 6)),
								arrowTip.Y - arrowSize * (arrowDy * std::cos(M_PI / 6) + arrowDx * std::sin(M_PI / 6))
							);
							PointF arrowPoint2 = PointF(
								arrowTip.X - arrowSize * (arrowDx * std::cos(-M_PI / 6) - arrowDy * std::sin(-M_PI / 6)),
								arrowTip.Y - arrowSize * (arrowDy * std::cos(-M_PI / 6) + arrowDx * std::sin(-M_PI / 6))
							);

							// Draw the arrowhead
							array<PointF>^ arrowHead = { arrowTip, arrowPoint1, arrowPoint2 };
							g->FillPolygon(Brushes::DarkCyan, arrowHead);
							Pen^ boundaryPen = gcnew Pen(Color::Black, 2.0f);
							g->DrawPolygon(boundaryPen, arrowHead);
							delete boundaryPen;
					
					}
					if (edge->Directed && defaultRadioButton->Checked)
					{
						if (flag)
						{
							// Do nothing, as the edge is undirected
						}
						else
						{
							// Calculate the direction vector
							float arrowDx = edge->End->X - controlX;
							float arrowDy = edge->End->Y - controlY;
							float length = std::sqrt(arrowDx * arrowDx + arrowDy * arrowDy);

							// Normalize the direction vector
							arrowDx /= length;
							arrowDy /= length;

							// Define the size of the arrowhead
							float arrowSize = 15.0f;

							// Move the arrowhead away from the vertex point
							float offset = 8.0f; // Adjust this value to move the arrowhead further away
							PointF arrowTip = PointF(
								edge->End->X - offset * arrowDx,
								edge->End->Y - offset * arrowDy
							);

							// Calculate the points for the arrowhead
							PointF arrowPoint1 = PointF(
								arrowTip.X - arrowSize * (arrowDx * std::cos(M_PI / 6) - arrowDy * std::sin(M_PI / 6)),
								arrowTip.Y - arrowSize * (arrowDy * std::cos(M_PI / 6) + arrowDx * std::sin(M_PI / 6))
							);
							PointF arrowPoint2 = PointF(
								arrowTip.X - arrowSize * (arrowDx * std::cos(-M_PI / 6) - arrowDy * std::sin(-M_PI / 6)),
								arrowTip.Y - arrowSize * (arrowDy * std::cos(-M_PI / 6) + arrowDx * std::sin(-M_PI / 6))
							);

							// Draw the arrowhead
							array<PointF>^ arrowHead = { arrowTip, arrowPoint1, arrowPoint2 };
							g->FillPolygon(Brushes::DarkCyan, arrowHead);
							Pen^ boundaryPen = gcnew Pen(Color::Black, 2.0f);
							g->DrawPolygon(boundaryPen, arrowHead);
							delete boundaryPen;
						}
					}
				}
				else if (edge->IsCoincideEdge == false)
				{
					Pen^ pen = gcnew Pen(edge->Color, 2 / zoomFactor);//edge->Color
					g->DrawLine(pen, edge->Start->X, edge->Start->Y, edge->End->X, edge->End->Y);
					delete pen;
					//Draw arrow
					if (edge->Directed && undirectedRadioButton->Checked)
					{
						flag = true;
					}
					if (edge->Directed && directedRadioButton->Checked)
					{
						flag = false;
						DrawArrow(g, edge->Start, edge->End);
					}
					if (edge->Directed && defaultRadioButton->Checked)
					{
						if (flag)
						{
							// Do nothing, as the edge is undirected
						}
						else
						{
							DrawArrow(g, edge->Start, edge->End);
						}
					}
				}
			}
			else if (edge->Start == edge->End) {


				float loopRadius = 2.0f * gridSize; // 4 square grids
				float centerX = edge->Start->X;
				float centerY = edge->Start->Y;

				//// Determine the less crowded side by checking the density of edges around the vertex
				int leftCount = 0, rightCount = 0, topCount = 0, bottomCount = 0;
				for each (Edge ^ e in graph->Edges) {
					if (e->Start->X < centerX) leftCount++;
					if (e->Start->X > centerX) rightCount++;
					if (e->Start->Y < centerY) topCount++;
					if (e->Start->Y > centerY) bottomCount++;
				}
				//// Choose the side with the least edges
				float offsetX = centerX, offsetY = centerY;
				if (leftCount <= rightCount && leftCount <= topCount && leftCount <= bottomCount) {
					offsetX -= loopRadius;
				}
				else if (rightCount <= leftCount && rightCount <= topCount && rightCount <= bottomCount) {
					offsetX += loopRadius;
				}
				else if (topCount <= leftCount && topCount <= rightCount && topCount <= bottomCount) {
					offsetY -= loopRadius;
				}
				else {
					offsetY += loopRadius;
				}
				offsetX = round(offsetX / gridSize) * gridSize;
				offsetY = round(offsetY / gridSize) * gridSize;

				Pen^ pen = gcnew Pen(edge->Color, 2 / zoomFactor);
				g->DrawEllipse(pen, offsetX - loopRadius, offsetY - loopRadius, loopRadius * 2, loopRadius * 2);


				float arrowSize = 20;
				PointF arrowPoint1, arrowPoint2, arrowPoint3;
				float angle = atan2(centerY - offsetY, centerX - offsetX);
				angle2 = angle;
				// Rotate 90 degrees to the right
				float rightAngle = angle - M_PI / 2 - 6;
				// Rotate 90 degrees to the left
				float leftAngle = angle + M_PI / 2;
				// Choose the desired rotation direction
				float rotationAngle = rightAngle; // or leftAngle
				float arrowX = centerX;
				float arrowY = centerY;

				arrowPoint1 = PointF(arrowX, arrowY);
				arrowPoint2 = PointF(arrowX - arrowSize * cos(rotationAngle - M_PI / 6), arrowY - arrowSize * sin(rotationAngle - M_PI / 6));
				arrowPoint3 = PointF(arrowX - arrowSize * cos(rotationAngle + M_PI / 6), arrowY - arrowSize * sin(rotationAngle + M_PI / 6));
				array<PointF>^ arrowPoints = { arrowPoint1, arrowPoint2, arrowPoint3 };
				delete pen;
				//Draw arrow
				if (edge->Directed && undirectedRadioButton->Checked)
				{
					flag = true;
				}

				if (edge->Directed && directedRadioButton->Checked)
				{
					flag = false;
					g->FillPolygon(Brushes::DarkCyan, arrowPoints);
					Pen^ boundaryPen = gcnew Pen(Color::Black, 2.0f);
					g->DrawPolygon(boundaryPen, arrowPoints);
				}

				if (edge->Directed && defaultRadioButton->Checked)
				{
					if (flag)
					{
						// Do nothing, as the edge is undirected
					}
					else
					{
						g->FillPolygon(Brushes::DarkCyan, arrowPoints);
						Pen^ boundaryPen = gcnew Pen(Color::Black, 2.0f);
						g->DrawPolygon(boundaryPen, arrowPoints);
					}
				}
				//this->pictureBox1->Invalidate();
			}



			// Draw edge weight
			if (edge->Weight != 0 && edge->Start != edge->End && edge->IsCoincideEdge == false)
			{
				float midX = (edge->Start->X + edge->End->X) / 2;
				float midY = (edge->Start->Y + edge->End->Y) / 2;
				System::Drawing::Font^ largerFont = gcnew System::Drawing::Font(this->Font->FontFamily, this->Font->Size * 1.2f, System::Drawing::FontStyle::Bold);
				for (int dx = -1; dx <= 1; ++dx) {
					for (int dy = -1; dy <= 1; ++dy) {
						if (dx != 0 || dy != 0) {
							g->DrawString(edge->Weight.ToString(), largerFont, Brushes::White, midX + dx, midY + dy);
						}
					}
				}
				// Draw the weight of the edge with the larger font
				g->DrawString(edge->Weight.ToString(), largerFont, Brushes::Black, midX, midY);
			}
			else if (edge->Weight != 0 && edge->Start == edge->End)
			{
				float loopRadius = 2.0f * gridSize; // Adjust the radius as needed
				float centerX = (edge->Start->X + edge->End->X) / 2 - loopRadius * cos(angle2);
				float centerY = (edge->Start->Y + edge->End->Y) / 2 - loopRadius * sin(angle2);
				// Highlight the weight
				System::Drawing::Font^ largerFont = gcnew System::Drawing::Font(this->Font->FontFamily, this->Font->Size * 1.2f, System::Drawing::FontStyle::Bold);
				for (int dx = -1; dx <= 1; ++dx) {
					for (int dy = -1; dy <= 1; ++dy) {
						if (dx != 0 || dy != 0) {
							g->DrawString(edge->Weight.ToString(), largerFont, Brushes::White, centerX + dx, centerY + dy);
						}
					}
				}
				g->DrawString(edge->Weight.ToString(), largerFont, Brushes::Black, centerX, centerY);
			}
		}
		//Draw Vertices
		for each (Vertex ^ vertex in graph->Vertices)
		{
			SolidBrush^ brush = gcnew SolidBrush(System::Drawing::Color::DarkBlue);
			float adjustedRadius = vertex->Radius * 0.8f;
			g->FillEllipse(brush, vertex->X - adjustedRadius, vertex->Y - adjustedRadius, adjustedRadius * 2, adjustedRadius * 2);

			delete brush;

			// Highlight selected vertex
			if (defaultRadioButton->Checked && vertex == selectedVertex)//fix Vertex create && draggedVertex == nullptr && !isDragging
			{
				Pen^ highlightPen = gcnew Pen(Color::Red, 2 / zoomFactor);
				g->DrawEllipse(highlightPen, vertex->X - vertex->Radius - 2, vertex->Y - vertex->Radius - 2, (vertex->Radius + 2) * 2, (vertex->Radius + 2) * 2);
				delete highlightPen;
			}
			System::Drawing::Font^ boldLargerFont = gcnew System::Drawing::Font(this->Font->FontFamily, this->Font->Size * 1.5f, System::Drawing::FontStyle::Bold);
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; ++dy) {
					if (dx != 0 || dy != 0) {
						g->DrawString(vertex->Name, boldLargerFont, Brushes::White, vertex->X - vertex->Radius + dx, vertex->Y - vertex->Radius - 15 + dy);
					}
				}
			}

			// Draw the text with the bold font on top
			g->DrawString(vertex->Name, boldLargerFont, Brushes::Black, vertex->X - vertex->Radius, vertex->Y - vertex->Radius - 15);

		}
		// Reset transformations
		g->ResetTransform();

		
	}
	void MyForm::AdjustVerticesToGrid()
	{
		float gridSize = 20.0f;
		for each (Vertex ^ vertex in graph->Vertices)
		{
			float adjustedX = round(vertex->X / gridSize) * gridSize;
			float adjustedY = round(vertex->Y / gridSize) * gridSize;
			vertex->X = adjustedX;
			vertex->Y = adjustedY;
		}
	}
	void MyForm::AddVertexAtCursor(Point cursorPosition) {
		if (defaultRadioButton->Checked) {
			return; // Don't add vertices in default mode
		}

		float adjustedX = (cursorPosition.X - viewOffsetX) / zoomFactor;
		float adjustedY = (cursorPosition.Y - viewOffsetY) / zoomFactor;
		float gridSize = GRID_SIZE;
		adjustedX = round(adjustedX / gridSize) * gridSize;
		adjustedY = round(adjustedY / gridSize) * gridSize;

		// Check if a vertex already exists at this position
		for each (Vertex ^ vertex in graph->Vertices) {
			if (Math::Abs(vertex->X - adjustedX) < 0.001 && Math::Abs(vertex->Y - adjustedY) < 0.001) {
				return; // Don't add a new vertex if one already exists here
			}
		}
		//if (directedRadioButton->Checked || undirectedRadioButton->Checked)//XuanThanh fix PromptForVertexName reopen when closed
		//{
		//	String^ vertexName = PromptForVertexName();
		//	if (!String::IsNullOrEmpty(vertexName)) {
		//		Vertex^ newVertex = gcnew Vertex(graph->Vertices->Count + 1, vertexName, adjustedX, adjustedY);
		//		graph->AddVertex(newVertex);
		//		pictureBox1->Invalidate();
		//	}
		//}
		UpdateInfoPanel3();
	}
	System::Void MyForm::RunDijkstraButton_Click(System::Object^ sender, System::EventArgs^ e) {

		if (graph->Edges->Count < 2) {
			MessageBox::Show("Please add at least two edges to run Dijkstra's algorithm.",
				"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		for each (Edge ^ edge in graph->Edges) {
			edge->Color = Color::Black;
		}
		String^ startName = ShowInputBox("Enter the name of the start vertex:", "Start Vertex", "");
		String^ endName = ShowInputBox("Enter the name of the end vertex:", "End Vertex", "");

		Vertex^ start = graph->GetVertexByName(startName);
		Vertex^ end = graph->GetVertexByName(endName);

		if (start != nullptr && end != nullptr)
		{
			RunDijkstra(start, end); pictureBox1->Invalidate();
		}
		else
		{
			MessageBox::Show("Invalid start or end vertex ID.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}

	System::Void MyForm::LoadGraph(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "GraphML Files (*.graphml)|*.graphml|All Files (*.*)|*.*";
		openFileDialog->DefaultExt = "graphml";

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ fileName = openFileDialog->FileName;
			graph->Clear();
			graph->LoadFromFile(fileName);
			pictureBox1->Invalidate();
			MessageBox::Show("Graph loaded successfully from GraphML format.", "Load Successful", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		UpdateInfoPanel3();
	}

	void MyForm::RunDijkstra(Vertex^ start, Vertex^ end) {
		bool isDirected = directedRadioButton->Checked;

		// Initialize data structures
		Dictionary<Vertex^, int>^ distances = gcnew Dictionary<Vertex^, int>(); // Shortest distances
		Dictionary<Vertex^, Vertex^>^ previous = gcnew Dictionary<Vertex^, Vertex^>(); // Previous vertices
		List<Vertex^>^ unvisited = gcnew List<Vertex^>(); // Unvisited vertices

		// Set initial distances to infinity and previous vertices to null
		for each (Vertex ^ v in graph->Vertices) {
			distances[v] = Int32::MaxValue;
			previous[v] = nullptr;
			unvisited->Add(v);
		}
		distances[start] = 0; // Distance to the start vertex is zero

		// Main loop: Process unvisited vertices
		while (unvisited->Count > 0) {
			// Find vertex with the smallest distance in unvisited set
			Vertex^ current = nullptr;
			for each (Vertex ^ v in unvisited) {
				if (current == nullptr || distances[v] < distances[current]) {
					current = v;
				}
			}

			Console::WriteLine("Current vertex: {0}, Distance: {1}", current->Name, distances[current]);

			if (current == end) break; // Stop if we reached the end vertex

			unvisited->Remove(current);

			// Relax edges from the current vertex
			for each (Edge ^ edge in graph->Edges) {
				Vertex^ neighbor = nullptr;

				// Check edge direction
				if (edge->Start == current) {
					neighbor = edge->End; // Forward direction
				}
				else if (!isDirected && edge->End == current) {
					neighbor = edge->Start; // Reverse direction (for undirected graphs)
				}

				if (neighbor != nullptr && unvisited->Contains(neighbor)) {
					int alt = distances[current] + edge->Weight; // Calculate new distance
					Console::WriteLine("  Checking edge from {0} to {1}, Weight: {2}, Alt: {3}", current->Name, neighbor->Name, edge->Weight, alt);

					if (alt < distances[neighbor]) {
						distances[neighbor] = alt; // Update distance
						previous[neighbor] = current; // Update previous vertex
					}
				}
			}
		}

		// Reconstruct the shortest path and highlight it
		Vertex^ current = end;
		bool pathExists = distances[end] != Int32::MaxValue; // Check if path exists
		String^ path = ""; // To store the path as a string for display

		while (current != nullptr && pathExists) {
			Vertex^ prev = previous[current];
			if (prev != nullptr) {
				bool edgeFound = false;
				// Add to the path string
				path = current->Name + " -> " + path;

				// Highlight the edge in the shortest path
				for each (Edge ^ edge in graph->Edges) {
					if ((edge->Start == prev && edge->End == current) ||
						(!isDirected && edge->Start == current && edge->End == prev)) {
						edge->Color = Color::Red; // Highlight edge
						edgeFound = true;
						break;
					}
				}
				if (!edgeFound)
				{
					Console::WriteLine("Edge not found from {0} to {1}", prev->Name, current->Name);
					pathExists = false;
					break;
				}
			}
			current = prev;
		}

		// Add the starting vertex to the path string
		path = start->Name + " -> " + path;
		// Remove the trailing arrow " -> " if present
		if (path->EndsWith(" -> ")) {
			path = path->Substring(0, path->Length - 4);
		}
		// Display the path or an error message
		if (!pathExists) {
			MessageBox::Show("No path found from start to end vertex. Please check the direction of the edges.",
				"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			MessageBox::Show("Shortest path found:\n" + path,
				"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		shortpath += "\r\nThe Dijkstra Shortest Path: " + path;
		UpdateInfoPanel3();
		// Redraw the picture box to show updated edge colors
		pictureBox1->Invalidate();
	}

	void MyForm::pictureBox1_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		Point cursorPos = e->Location;
		const float zoomStep = 0.1f;

		if (e->Delta > 0) {
			zoomFactor += zoomStep;
		}
		else {
			zoomFactor = Math::Max(zoomFactor - zoomStep, zoomStep);
		}
		AdjustVerticesToGrid();
		pictureBox1->Invalidate();

	}
	//


	void ConvertStringToInt(String^& a, int& b)//XuanThanh
	{
		std::stringstream ss;//Convert String^ to string, then string to int
		std::string str = msclr::interop::marshal_as<std::string>(a);
		ss << str;
		ss >> b;
	}
	void ConvertStringTostring(String^& a, std::string& b)//XuanThanh
	{
		b = msclr::interop::marshal_as<std::string>(a);
	}
	void MyForm::DrawGraph(Graphics^ g)
	{
		// Draw grid if showGrid is true
		if (showGrid) {
			Pen^ gridPen = gcnew Pen(Color::LightGray);
			int gridSize = static_cast<int>(20 * zoomFactor);
			for (int x = 0; x < static_cast<int>(pictureBox1->Width / zoomFactor); x += gridSize) {
				//g->DrawLine(gridPen, x, 0, x, pictureBox1->Height / zoomFactor);
				g->DrawLine(gridPen, static_cast<float>(x), 0.0f, static_cast<float>(x), static_cast<float>(pictureBox1->Height / zoomFactor));
			}
			for (int y = 0; y < static_cast<int>(pictureBox1->Height / zoomFactor); y += gridSize) {
				//g->DrawLine(gridPen, 0, y, pictureBox1->Width / zoomFactor, y);
				g->DrawLine(gridPen, 0.0f, static_cast<float>(y), static_cast<float>(pictureBox1->Width / zoomFactor), static_cast<float>(y));
			}
		}
		//Improve animation qualifications
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		g->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAliasGridFit;
	}
	void MyForm::AddEdgeButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Create a new form to get user input for the edge
		Form^ inputForm = gcnew Form();
		inputForm->Text = "Add Edge";
		inputForm->Size = System::Drawing::Size(180, 300);
		inputForm->StartPosition = FormStartPosition::CenterParent;
		inputForm->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedDialog;
		inputForm->MaximizeBox = false;
		inputForm->MinimizeBox = true;

		Label^ startLabel = gcnew Label();
		startLabel->Text = "Start Vertex:";
		startLabel->Location = System::Drawing::Point(10, 10);
		inputForm->Controls->Add(startLabel);

		ComboBox^ startComboBox = gcnew ComboBox();
		startComboBox->Location = System::Drawing::Point(10, 30);
		startComboBox->Size = System::Drawing::Size(100, 20);
		inputForm->Controls->Add(startComboBox);

		Label^ endLabel = gcnew Label();
		endLabel->Text = "End Vertex:";
		endLabel->Location = System::Drawing::Point(10, 60);
		inputForm->Controls->Add(endLabel);

		ComboBox^ endComboBox = gcnew ComboBox();
		endComboBox->Location = System::Drawing::Point(10, 80);
		endComboBox->Size = System::Drawing::Size(100, 20);
		inputForm->Controls->Add(endComboBox);

		Label^ weightLabel = gcnew Label();
		weightLabel->Text = "Weight:";
		weightLabel->Location = System::Drawing::Point(10, 110);
		inputForm->Controls->Add(weightLabel);

		TextBox^ weightTextBox = gcnew TextBox();
		weightTextBox->Location = System::Drawing::Point(10, 130);
		weightTextBox->Size = System::Drawing::Size(100, 20);
		inputForm->Controls->Add(weightTextBox);

		// Add RadioButtons for edge type
		Label^ edgeTypeLabel = gcnew Label();
		edgeTypeLabel->Text = "Edge Type:";
		edgeTypeLabel->Location = System::Drawing::Point(10, 160);
		inputForm->Controls->Add(edgeTypeLabel);

		RadioButton^ undirectedRadioButton = gcnew RadioButton();
		undirectedRadioButton->Text = "Undirected";
		undirectedRadioButton->Location = System::Drawing::Point(10, 180);
		undirectedRadioButton->Checked = true; // Default to undirected
		inputForm->Controls->Add(undirectedRadioButton);

		RadioButton^ directedRadioButton = gcnew RadioButton();
		directedRadioButton->Text = "Directed";
		directedRadioButton->Location = System::Drawing::Point(10, 200);
		inputForm->Controls->Add(directedRadioButton);

		// Adjust OK button position
		Button^ okButton = gcnew Button();
		okButton->Text = "OK";
		okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		okButton->Location = System::Drawing::Point(10, 230);
		okButton->Size = System::Drawing::Size(75, 30);
		inputForm->Controls->Add(okButton);

		// Populate the combo boxes with vertex names
		for each (Vertex ^ vertex in graph->Vertices) {
			startComboBox->Items->Add(vertex->Name);
			endComboBox->Items->Add(vertex->Name);
		}

		// Show the form and get the result
		if (inputForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (startComboBox->SelectedItem != nullptr && endComboBox->SelectedItem != nullptr) {
				String^ startVertexName = startComboBox->SelectedItem->ToString();
				String^ endVertexName = endComboBox->SelectedItem->ToString();

				std::string str1;
				std::string str2;
				ConvertStringTostring(startVertexName, str1);
				ConvertStringTostring(endVertexName, str2);
				int weight;
				//Loop
				if ((str1.compare(str2) == 0) && Int32::TryParse(weightTextBox->Text, weight))
				{
					int isCoincideVertex = (startVertexName == endVertexName) ? true : false;
					if (undirectedRadioButton->Checked) {
						graph->AddEdge(isCoincideVertex, startVertexName, endVertexName, weight); // false for undirected
					}
					else if (directedRadioButton->Checked) {
						graph->AddEdge(isCoincideVertex, startVertexName, endVertexName, weight, true); // true for directed
					}
				}
				// NotLoop
				else if (Int32::TryParse(weightTextBox->Text, weight) && (str1.compare(str2) != 0))
				{
					int isCoincideVertex = (startVertexName == endVertexName) ? true : false;
					if (undirectedRadioButton->Checked) {
						graph->AddEdge(isCoincideVertex, startVertexName, endVertexName, weight); // false for undirected
					}
					else if (directedRadioButton->Checked) {
						graph->AddEdge(isCoincideVertex, startVertexName, endVertexName, weight, true); // true for directed
					}
				}
				else
				{
					MessageBox::Show("Please enter a valid integer for the weight.");
				}
			}
			else {
				MessageBox::Show("Please select both start and end vertices.");
			}
		}
		UpdateInfoPanel3();
	}

	System::Void MyForm::DeleteEdgeButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// Create a new form to get user input for the edge to delete
		Form^ inputForm = gcnew Form();
		inputForm->Text = "Delete Edge";
		inputForm->Size = System::Drawing::Size(300, 150);
		inputForm->StartPosition = FormStartPosition::CenterParent;

		Label^ edgeLabel = gcnew Label();
		edgeLabel->Text = "Select Edge:";
		edgeLabel->Location = System::Drawing::Point(10, 10);
		inputForm->Controls->Add(edgeLabel);

		ComboBox^ edgeComboBox = gcnew ComboBox();
		edgeComboBox->Location = System::Drawing::Point(10, 30);
		edgeComboBox->Size = System::Drawing::Size(200, 20);
		inputForm->Controls->Add(edgeComboBox);

		Button^ okButton = gcnew Button();
		okButton->Text = "OK";
		okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		okButton->Location = System::Drawing::Point(10, 60);
		inputForm->Controls->Add(okButton);

		// Populate the combo box with edge descriptions
		for each (Edge ^ edge in graph->Edges)
		{
			String^ edgeDescription = edge->Start->Name + " -> " + edge->End->Name + " (Weight: " + edge->Weight + ")";
			edgeComboBox->Items->Add(edgeDescription);
		}

		// Show the form and get the result
		if (inputForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			if (edgeComboBox->SelectedIndex != -1)
			{
				// Remove the selected edge from the graph
				Edge^ edgeToRemove = graph->Edges[edgeComboBox->SelectedIndex];
				graph->RemoveEdge(edgeToRemove);

				// Redraw the graph
				pictureBox1->Invalidate();
			}
		}
	}

	[STAThreadAttribute]
		int main(array<System::String^>^ args)
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Project2::MyForm form;
		Application::Run(% form);
		return 0;
	}
	void MyForm::ClearGraph() {
		// Clear the vertices and edges from the graph
		graph->Vertices->Clear();
		graph->Edges->Clear();

		// Refresh the display to reflect the changes
		pictureBox1->Invalidate();
		UpdateInfoPanel3();
	}
	void MyForm::DrawLoopDirectedEdge(Graphics^ g, Edge^ edge, float offsetX, float offsetY)
	{
		// Calculate the angle between the start and end vertices
		float dx = edge->End->X - edge->Start->X;
		float dy = edge->End->Y - edge->Start->Y;
		float angle = static_cast<float>(Math::Atan2(dy, dx) * 180 / Math::PI);

		// Calculate the distance between the start and end vertices
		float distance = static_cast<float>(Math::Sqrt(dx * dx + dy * dy));

		// Calculate the radius of the circle
		float circleRadius = 4.0f * gridSize * zoomFactor;

		// Calculate the position of the circle
		float circleX = edge->Start->X + (distance - circleRadius) * dx / distance;
		float circleY = edge->Start->Y + (distance - circleRadius) * dy / distance;

		// Check if the circle is in an obtuse angle
		bool isObtuseAngle = true;
		for each (Edge ^ e in graph->Edges)
		{
			if (e != edge)
			{
				float ex = e->End->X - e->Start->X;
				float ey = e->End->Y - e->Start->Y;
				float eAngle = static_cast<float>(Math::Atan2(ey, ex) * 180 / Math::PI);

				// Calculate the angle difference
				float angleDiff = Math::Abs(angle - eAngle);
				if (angleDiff < 90 || angleDiff > 270)
				{
					isObtuseAngle = false;
					break;
				}
			}
		}

		// Check if the circle is in a space with no vertex
		bool isSpaceWithNoVertex = true;
		for each (Vertex ^ v in graph->Vertices)
		{
			float vx = v->X - circleX;
			float vy = v->Y - circleY;
			float vertexDistance = static_cast<float>(Math::Sqrt(vx * vx + vy * vy));
			if (vertexDistance < v->Radius + circleRadius)
			{
				isSpaceWithNoVertex = false;
				break;
			}
		}

		// Draw the circle
		if (isObtuseAngle && isSpaceWithNoVertex)
		{
			float circleDiameter = 2.0f * circleRadius;
			float circleXOffset = circleX - circleRadius;
			float circleYOffset = circleY - circleRadius;
			g->FillEllipse(Brushes::White, offsetX + circleXOffset, offsetY + circleYOffset, circleDiameter, circleDiameter);
			g->DrawEllipse(Pens::Black, offsetX + circleXOffset, offsetY + circleYOffset, circleDiameter, circleDiameter);
		}

		// Draw the arrow
		float arrowSize = 5.0f / zoomFactor;
		PointF arrowPoint1(offsetX + edge->End->X, offsetY + edge->End->Y);
		PointF arrowPoint2(offsetX + edge->End->X - arrowSize, offsetY + edge->End->Y - arrowSize);
		PointF arrowPoint3(offsetX + edge->End->X + arrowSize, offsetY + edge->End->Y - arrowSize);
		array<PointF>^ arrowPoints = { arrowPoint1, arrowPoint2, arrowPoint3 };
		g->FillPolygon(Brushes::Black, arrowPoints);
	}

	// pictureBox1_MouseClick: Handles mouse click events on the picture box
	// This function manages vertex and edge creation, selection, and deletion
	System::Void MyForm::pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->mouseButtonClicked = e->Button;
		this->single_Click = true;
		this->clickTimer->Start();
		float adjustedX = (e->X - viewOffsetX) / zoomFactor;
		float adjustedY = (e->Y - viewOffsetY) / zoomFactor;
		if (e->Button == System::Windows::Forms::MouseButtons::Left && draggingVertex == nullptr)
		{
			//PointF worldPoint = ScreenToWorld(e->Location);
			Vertex^ clickedVertex = FindVertexAtPoint(adjustedX, adjustedY);
			if (clickedVertex != nullptr && (directedRadioButton->Checked || undirectedRadioButton->Checked)) //XuanThanh button
			{
				//XuanThanh fix direct Add Vertex Bug
				//String^ newVertexName = PromptForVertexName();
				//if (!String::IsNullOrEmpty(newVertexName))
				//{
				//	if (newVertexName->Length >= 10)
				//	{
				//		if (newVertexName->Length > 10) {
				//			MessageBox::Show("The name is too long. Please choose a name with fewer than 10 characters.", "Name Too Long", MessageBoxButtons::OK, MessageBoxIcon::Error);
				//			return;
				//		}
				//	}
				//	bool isNameExist = false;
				//	for each (Vertex ^ v in graph->Vertices)
				//	{
				//		if (v->Name == newVertexName)
				//		{
				//			isNameExist = true;
				//			break;
				//		}
				//	}
				//	if (isNameExist) {
				//		MessageBox::Show("The name already exists. Please choose another name.", "Duplicate Name",
				//			MessageBoxButtons::OK, MessageBoxIcon::Error);
				//	}
				//	else {
				//		clickedVertex->Name = newVertexName;
				//		pictureBox1->Invalidate();
				//	}
				//}

			}
			else if (draggingVertex == nullptr && (directedRadioButton->Checked || undirectedRadioButton->Checked)) //XuanThanh
			{
				String^ vertexName = PromptForVertexName();
				if (!String::IsNullOrEmpty(vertexName))
				{
					if (vertexName->Length >= 10)
					{
						MessageBox::Show("The name is too long. Please choose a name with fewer than 10 characters.", "Name Too Long", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}

					bool isNameExist = false;

					for each (Vertex ^ v in graph->Vertices)
					{
						if (v->Name == vertexName)
						{
							isNameExist = true;
							break;
						}
					}

					if (isNameExist)
					{
						MessageBox::Show("The name already exists. Please choose another name.", "Duplicate Name", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
					else
					{
						int newId = graph->Vertices->Count + 1;
						Vertex^ newVertex = gcnew Vertex(newId, vertexName, adjustedX, adjustedY);
						graph->AddVertex(newVertex);
						pictureBox1->Invalidate();
					}
				}
			}
		}
		else if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			Vertex^ clickedVertex = FindVertexAtPoint(adjustedX, adjustedY);

			if (clickedVertex != nullptr)
			{
				graph->RemoveVertex(clickedVertex);
			}
			else
			{
				Edge^ clickedEdge = FindEdgeAtPoint(adjustedX, adjustedY);

				if (clickedEdge != nullptr)
				{
					graph->RemoveEdge(clickedEdge);
				}
			}
			pictureBox1->Invalidate();
		}
		UpdateInfoPanel3();
		//pictureBox1->Invalidate();
	}

	String^ MyForm::PromptForVertexName()
	{
		Form^ inputForm = gcnew Form();
		inputForm->Text = "Enter Vertex Name";
		inputForm->Size = System::Drawing::Size(250, 150);
		inputForm->StartPosition = FormStartPosition::CenterParent;
		inputForm->Icon = gcnew System::Drawing::Icon("digr.ico");

		Label^ nameLabel = gcnew Label();
		nameLabel->Text = "Vertex Name:";
		nameLabel->Location = System::Drawing::Point(10, 10);
		inputForm->Controls->Add(nameLabel);

		TextBox^ nameTextBox = gcnew TextBox();
		nameTextBox->Location = System::Drawing::Point(10, 30);
		nameTextBox->Size = System::Drawing::Size(200, 20);
		inputForm->Controls->Add(nameTextBox);

		Button^ okButton = gcnew Button();
		okButton->Text = "OK";
		okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		okButton->Location = System::Drawing::Point(10, 60);
		inputForm->Controls->Add(okButton);

		inputForm->AcceptButton = okButton;

		if (inputForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			return nameTextBox->Text;
		}
		else {
			return nullptr;
		}
	}
	String^ MyForm::PromptForEditVertex(String^ title)
	{
		Form^ inputForm = gcnew Form();
		inputForm->Text = title;
		inputForm->Size = System::Drawing::Size(250, 150);
		inputForm->StartPosition = FormStartPosition::CenterParent;
		inputForm->Icon = gcnew System::Drawing::Icon("digr.ico");
		inputForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		inputForm->MaximizeBox = false;
		inputForm->MinimizeBox = false;

		Label^ nameLabel = gcnew Label();
		nameLabel->Text = "Rename Vertex:";
		nameLabel->Location = System::Drawing::Point(10, 10);
		inputForm->Controls->Add(nameLabel);

		TextBox^ nameTextBox = gcnew TextBox();
		nameTextBox->Location = System::Drawing::Point(10, 30);
		nameTextBox->Size = System::Drawing::Size(200, 20);
		inputForm->Controls->Add(nameTextBox);

		Button^ okButton = gcnew Button();
		okButton->Text = "OK";
		okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		okButton->Location = System::Drawing::Point(70, 60);
		inputForm->Controls->Add(okButton);
		inputForm->AcceptButton = okButton;

		if (inputForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			return nameTextBox->Text;
		}
		else
		{
			return nullptr;
		}
	}
	System::Void MyForm::clickTimer_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		//this->clickTimer->Stop();
		//if (this->single_Click)
		//{
		//	this->doubleClickOccured = false;
		//}
		this->clickTimer->Stop();
		float adjustedX = static_cast<float>((this->mouseX * zoomFactor));
		float adjustedY = static_cast<float>((this->mouseY * zoomFactor));
		if (this->single_Click && !this->doubleClickOccured)
		{
			if (this->mouseButtonClicked == System::Windows::Forms::MouseButtons::Left && (directedRadioButton->Checked || undirectedRadioButton->Checked)) //XuanThanh
			{
				Vertex^ clickedVertex = FindVertexAtPoint(adjustedX, adjustedY);
				if (clickedVertex != nullptr)
				{
					//
				}
				else if (draggingVertex == nullptr && (directedRadioButton->Checked || undirectedRadioButton->Checked)) //XuanThanh
				{
					//
				}
			}
			else if (this->mouseButtonClicked == System::Windows::Forms::MouseButtons::Right)
			{
				Vertex^ clickedVertex = FindVertexAtPoint(adjustedX, adjustedY);
				if (clickedVertex != nullptr)
				{
					graph->RemoveVertex(clickedVertex);
				}
				else
				{
					Edge^ clickedEdge = FindEdgeAtPoint(adjustedX, adjustedY);
					if (clickedEdge != nullptr)
					{
						graph->RemoveEdge(clickedEdge);
					}
				}
				pictureBox1->Invalidate();
			}
		}
		this->doubleClickOccured = false;
		UpdateInfoPanel3();
	}

	System::Void MyForm::pictureBox1_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			this->single_Click = false;
			this->doubleClickOccured = true;
			this->clickTimer->Stop();
			int adjustedX = static_cast<int>(std::round(e->X * zoomFactor));
			int adjustedY = static_cast<int>(std::round(e->Y * zoomFactor));

			Vertex^ doubleclickedVertex = FindVertexAtPoint(adjustedX, adjustedY);
			if (doubleclickedVertex != nullptr)
			{
				String^ newVertexName = PromptForEditVertex("Edit Vertex");
				if (!String::IsNullOrEmpty(newVertexName))
				{
					if (newVertexName->Length > 10)
					{
						MessageBox::Show("The name is too long. Please choose a name with fewer than 10 characters.",
							"Name Too Long", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}

					bool isNameExist = false;
					for each (Vertex ^ v in graph->Vertices)
					{
						if (v->Name == newVertexName)
						{
							isNameExist = true;
							break;
						}
					}

					if (isNameExist)
					{
						MessageBox::Show("The name already exists. Please choose another name.",
							"Duplicate Name", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
					else
					{
						doubleclickedVertex->Name = newVertexName;
						pictureBox1->Invalidate();
					}
				}
			}
		}
	}


	// pictureBox1_MouseMove: Handles mouse movement events on the picture box
	// This function manages vertex dragging and edge creation preview
	System::Void MyForm::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		const int DRAG_THRESHOLD = 5; // pixels

		if (defaultRadioButton->Checked)
		{
			if (e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				int dx = e->X - lastMousePosition.X;
				int dy = e->Y - lastMousePosition.Y;

				if (!isDragging && !isPanning && (Math::Abs(dx) > DRAG_THRESHOLD || Math::Abs(dy) > DRAG_THRESHOLD))
				{
					if (draggedVertex != nullptr)
					{
						isDragging = true;
					}
					else
					{
						isPanning = true;
					}
				}

				if (isDragging && draggedVertex != nullptr)
				{
					float gridSize = GRID_SIZE;
					float newX = (e->X - viewOffsetX) / zoomFactor;
					float newY = (e->Y - viewOffsetY) / zoomFactor;
					if (showGrid)
					{
						newX = round(newX / gridSize) * gridSize;
						newY = round(newY / gridSize) * gridSize;
					}
					//draggedVertex->X = newX;
					//draggedVertex->Y = newY;//Fix ZoomIn
					float adjustedX = (e->X - viewOffsetX) / zoomFactor;
					float adjustedY = (e->Y - viewOffsetY) / zoomFactor;
					draggedVertex->X = adjustedX;
					draggedVertex->Y = adjustedY;
					pictureBox1->Invalidate();
				}
				else if (isPanning)
				{
					viewOffsetX += dx;
					viewOffsetY += dy;
					pictureBox1->Invalidate();
				}

				lastMousePosition = e->Location;
			}

			// Update cursor based on whether it's over a vertex
			Vertex^ hoveredVertex = FindVertexAtPoint(e->X, e->Y);
			if (hoveredVertex != nullptr)
			{
				pictureBox1->Cursor = Cursors::Hand;
			}
			else
			{
				pictureBox1->Cursor = Cursors::Default;
			}
		}
		else
		{
			pictureBox1->Cursor = Cursors::Cross;
		}
		if (isDragging && draggedVertex==nullptr) {//add
			Vertex^ vertex = graph->FindVertexAt(e->X / zoomFactor, e->Y / zoomFactor);
			if (vertex != nullptr) {
				vertex->X = e->X / zoomFactor;
				vertex->Y = e->Y / zoomFactor;

				// Determine the less crowded side by checking the density of edges around the vertex
				int leftCount = 0, rightCount = 0, topCount = 0, bottomCount = 0;
				for each (Edge ^ edge in graph->Edges) {
					if (edge->Start->X < vertex->X) leftCount++;
					if (edge->Start->X > vertex->X) rightCount++;
					if (edge->Start->Y < vertex->Y) topCount++;
					if (edge->Start->Y > vertex->Y) bottomCount++;
				}

				// Choose the side with the least edges
				float offsetX = vertex->X, offsetY = vertex->Y;
				if (leftCount <= rightCount && leftCount <= topCount && leftCount <= bottomCount) {
					offsetX -= 20.0f / zoomFactor;
				}
				else if (rightCount <= leftCount && rightCount <= topCount && rightCount <= bottomCount) {
					offsetX += 20.0f / zoomFactor;
				}
				else if (topCount <= leftCount && topCount <= rightCount && topCount <= bottomCount) {
					offsetY -= 20.0f / zoomFactor;
				}
				else {
					offsetY += 20.0f / zoomFactor;
				}

				// Adjust the position to fit the grid
				offsetX = round(offsetX / gridSize) * gridSize;
				offsetY = round(offsetY / gridSize) * gridSize;

				vertex->X = offsetX;
				vertex->Y = offsetY;

				pictureBox1->Invalidate();
			}
		}
	}

	// ZoomIn: Increases the zoom level of the graph view
	System::Void MyForm::ZoomIn(System::Object^ sender, System::EventArgs^ e) {
		float oldZoom = zoomFactor;
		zoomFactor *= 1.2f;

		// Adjust view offset to keep the center point fixed
		int centerX = pictureBox1->Width / 2;
		int centerY = pictureBox1->Height / 2;
		viewOffsetX = (viewOffsetX - centerX) * (zoomFactor / oldZoom) + centerX;
		viewOffsetY = (viewOffsetY - centerY) * (zoomFactor / oldZoom) + centerY;

		AdjustVerticesToGrid();
		pictureBox1->Invalidate();
	}

	// ZoomInButton_Click: Handles the zoom in button click event
	System::Void MyForm::ZoomInButton_Click(System::Object^ sender, System::EventArgs^ e) {
		ZoomIn(sender, e);
	}

	// ZoomOutButton_Click: Handles the zoom out button click event
	System::Void MyForm::ZoomOutButton_Click(System::Object^ sender, System::EventArgs^ e) {
		ZoomOut(sender, e);
	}

	// ZoomOut: Decreases the zoom level of the graph view
	System::Void MyForm::ZoomOut(System::Object^ sender, System::EventArgs^ e) {
		float oldZoom = zoomFactor;
		zoomFactor /= 1.2f;

		// Adjust view offset to keep the center point fixed
		int centerX = pictureBox1->Width / 2;
		int centerY = pictureBox1->Height / 2;
		viewOffsetX = (viewOffsetX - centerX) * (zoomFactor / oldZoom) + centerX;
		viewOffsetY = (viewOffsetY - centerY) * (zoomFactor / oldZoom) + centerY;

		AdjustVerticesToGrid();
		pictureBox1->Invalidate();
	}

	// ResetZoom: Resets the zoom level and view offset to their default values
	System::Void MyForm::ResetZoom(System::Object^ sender, System::EventArgs^ e) {
		zoomFactor = 1.0f;
		viewOffsetX = 0;
		viewOffsetY = 0;
		AdjustVerticesToGrid();
		pictureBox1->Invalidate();
	}

	// ResetZoomButton_Click: Handles the reset zoom button click event
	System::Void MyForm::ResetZoomButton_Click(System::Object^ sender, System::EventArgs^ e) {
		ResetZoom(sender, e);
	}

	// ClearButton_Click: Clears all vertices and edges from the graph
	System::Void MyForm::ClearButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Clear the graph
		graph->Clear();

		// Reset view parameters
		zoomFactor = 1.0f;
		viewOffsetX = 0;
		viewOffsetY = 0;

		// Redraw the picture box
		pictureBox1->Invalidate();
		UpdateInfoPanel3();
	}

	// DrawArrow: Draws an arrow head at the end of an edge
	void MyForm::DrawArrow(Graphics^ g, Vertex^ start, Vertex^ end) {

		//// Draw the arrow head
		//g->FillPolygon(Brushes::Red, arrowHead);
		float dx = end->X - start->X;
		float dy = end->Y - start->Y;
		float angle = Math::Atan2(dy, dx);
		float length = Math::Sqrt(dx * dx + dy * dy);
		float arrowSize = 12;
		float adjustedRadius = end->Radius - 2.8f;
		float adjustedEndX = end->X - adjustedRadius * Math::Cos(angle);
		float adjustedEndY = end->Y - adjustedRadius * Math::Sin(angle);
		// Calculate the arrow head points
		array<PointF>^ arrowHead = gcnew array<PointF>(3);
		arrowHead[0] = PointF(adjustedEndX, adjustedEndY);
		arrowHead[1] = PointF(adjustedEndX - arrowSize * Math::Cos(angle - Math::PI / 6),
			adjustedEndY - arrowSize * Math::Sin(angle - Math::PI / 6));
		arrowHead[2] = PointF(adjustedEndX - arrowSize * Math::Cos(angle + Math::PI / 6),
			adjustedEndY - arrowSize * Math::Sin(angle + Math::PI / 6));
		// Calculate the boundary arrow head points
		float boundarySize = 16; // Slightly larger size for boundary
		array<PointF>^ boundaryArrowHead = gcnew array<PointF>(3);
		boundaryArrowHead[0] = PointF(adjustedEndX + 1.5, adjustedEndY);
		boundaryArrowHead[1] = PointF(adjustedEndX - 1 - boundarySize * Math::Cos(angle - Math::PI - 1 / 6),
			adjustedEndY - boundarySize * Math::Sin(angle - Math::PI / 6));
		boundaryArrowHead[2] = PointF(adjustedEndX - 1 - boundarySize * Math::Cos(angle + Math::PI / 6),
			adjustedEndY - boundarySize * Math::Sin(angle + Math::PI / 6));
		//g->FillPolygon(Brushes::Red, boundaryArrowHead);

		// Draw the arrow head
		g->FillPolygon(Brushes::DarkCyan, arrowHead);
		Pen^ boundaryPen = gcnew Pen(Color::Black, 1.0f);
		g->DrawPolygon(boundaryPen, arrowHead);
	}

	// pictureBox1_MouseDown: Handles mouse button press events on the picture box
	System::Void MyForm::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			float adjustedX = (e->X - viewOffsetX) / zoomFactor;////Fix ZoomIn
			float adjustedY = (e->Y - viewOffsetY) / zoomFactor;
			//Vertex^ clickedVertex = FindVertexAtPoint(e->X, e->Y);
			Vertex^ clickedVertex = FindVertexAtPoint(adjustedX, adjustedY);

			if (clickedVertex != nullptr) {
				selectedVertex = clickedVertex;
				if (defaultRadioButton->Checked) {
					isDragging = false;  // Set to false initially
					draggedVertex = clickedVertex;
				}
			}
			else {
				selectedVertex = nullptr;
				if (defaultRadioButton->Checked) {
					isPanning = false;  // Set to false initially
				}
			}

			lastMousePosition = e->Location;  // Always record the initial position
		}
	}

	System::Void MyForm::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {// fix vertex create
			if (defaultRadioButton->Checked) {
				if (isPanning) {
					isPanning = false;
				}
				else if (isDragging && draggedVertex != nullptr) {
					isDragging = false;
					AdjustVerticesToGrid();
					pictureBox1->Invalidate();
				}
				// Do nothing else in Default mode
			}
			else if (directedRadioButton->Checked || undirectedRadioButton->Checked) {
				float adjustedX = (e->X - viewOffsetX) / zoomFactor;//Fix ZoomIn
				float adjustedY = (e->Y - viewOffsetY) / zoomFactor;
				Vertex^ clickedVertex = FindVertexAtPoint(adjustedX, adjustedY);
				//Vertex^ clickedVertex = FindVertexAtPoint(e->X, e->Y);

				if (selectedVertex != nullptr && clickedVertex != nullptr && clickedVertex != selectedVertex) {
					// Handle edge creation
					int isCoincideVertex = (selectedVertex->Name == clickedVertex->Name) ? true : false;
					String^ weight = ShowInputBox("Enter the value of Weight:", "Weight Add", "0");
					bool isDirected = directedRadioButton->Checked;
					int weightnum;
					ConvertStringToInt(weight, weightnum);
					graph->AddEdge(isCoincideVertex, selectedVertex->Name, clickedVertex->Name, weightnum, isDirected);
					pictureBox1->Invalidate();
				}
				else if (clickedVertex == nullptr && !isDragging && draggingVertex == nullptr) {
					// Create a new vertex only if no vertex was clicked and we're not dragging
					AddVertexAtCursor(e->Location);
				}
			}
		}

		draggedVertex = nullptr;
		selectedVertex = nullptr;
		isPanning = false;
		isDragging = false;
		pictureBox1->Invalidate();
		UpdateInfoPanel3();
	}

	System::Void MyForm::SaveGraph(System::Object^ sender, System::EventArgs^ e) {
		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "GraphML Files (*.graphml)|*.graphml|All Files (*.*)|*.*";
		saveFileDialog->DefaultExt = "graphml";
		saveFileDialog->AddExtension = true;

		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ fileName = saveFileDialog->FileName;
			graph->SaveToFile(fileName);
			MessageBox::Show("Graph saved successfully in GraphML format.", "Save Successful", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	System::Void MyForm::ChangeEdgeColor(System::Object^ sender, System::EventArgs^ e) {
		ColorDialog^ colorDialog = gcnew ColorDialog();
		if (colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			currentEdgeColor = colorDialog->Color;
		}

	}

	System::Void MyForm::defaultRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (defaultRadioButton->Checked) {
			// Enable vertex selection and movement
			isDrawingEdge = false;
			selectedVertex = nullptr;
			pictureBox1->Cursor = Cursors::Default;
		}
		for each (Edge ^ edge in graph->Edges) {
			edge->Color = Color::Black;
		}
		shortpath = "";
		UpdateInfoPanel3();
	}

	System::Void MyForm::directedRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (directedRadioButton->Checked) {
			// Enable edge drawing mode (directed)
			isDrawingEdge = true;
			selectedVertex = nullptr;
			pictureBox1->Cursor = Cursors::Cross;
		}
		this->pictureBox1->Invalidate();

	}

	System::Void MyForm::undirectedRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (undirectedRadioButton->Checked) {
			// Enable edge drawing mode (undirected)
			isDrawingEdge = true;
			selectedVertex = nullptr;
			pictureBox1->Cursor = Cursors::Cross;
		}
		this->pictureBox1->Invalidate();

	}


	System::Void MyForm::ShowGridButton_Click(System::Object^ sender, System::EventArgs^ e) {
		showGrid = !showGrid;
		if (showGrid) {
			showGridButton->Text = L"Hide Grid";
		}
		else {
			showGridButton->Text = L"Show Grid";
		}
		pictureBox1->Invalidate();
	}

	// IsVertexNameExist: Checks if a vertex with the given name already exists
	bool MyForm::IsVertexNameExist(String^ name) {
		for each (Vertex ^ v in graph->Vertices) {
			if (v->Name == name) {
				return true;
			}
		}
		return false;
	}
	System::Void MyForm::MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->Control && e->KeyCode == Keys::E) {
			if (e->Shift) {
				// Ctrl + Shift + E: Delete Edge
				DeleteEdgeButton_Click(sender, e);
			}
			else {
				// Ctrl + E: Add Edge
				AddEdgeButton_Click(sender, e);
			}
			//this->pictureBox1->Invalidate();

		}
		else if (e->Control && e->KeyCode == Keys::D) {
			// Ctrl + D: Run Dijkstra's
			RunDijkstraButton_Click(sender, e);
			//this->pictureBox1->Invalidate();

		}
		else if (e->Control && e->KeyCode == Keys::Oemplus) {
			// Ctrl + '+': Zoom In
			ZoomIn(sender, e);
			//this->pictureBox1->Invalidate();

		}
		else if (e->Control && e->KeyCode == Keys::OemMinus) {
			// Ctrl + '-': Zoom Out
			ZoomOut(sender, e);
			//this->pictureBox1->Invalidate();

		}
		else if (e->Control && e->KeyCode == Keys::S) {
			// Ctrl + S: Save Graph
			SaveGraph(sender, e);
			this->pictureBox1->Invalidate();

		}
		else if (e->Control && e->KeyCode == Keys::O) {
			// Ctrl + O: Load Graph
			LoadGraph(sender, e);
			this->pictureBox1->Invalidate();

		}
		else if (e->Control && e->KeyCode == Keys::R) {
			// Ctrl + R: Reset Zoom
			ResetZoom(sender, e);
		}
		else if (e->Control && e->KeyCode == Keys::Delete) {
			// Ctrl + Delete: Clear Graph
			ClearGraph();
			//this->pictureBox1->Invalidate();

		}
		else if (e->Control && e->KeyCode == Keys::G) {
			// Ctrl + G: Show Grid
			ShowGridButton_Click(sender, e);
			//this->pictureBox1->Invalidate();
		}
		else if (e->Control && e->KeyCode == System::Windows::Forms::Keys::Z) {
			graph->Undo();
			//this->pictureBox1->Invalidate();
		}
		else if (e->Control && e->KeyCode == System::Windows::Forms::Keys::A) {//default
			//graph->Undo();
			this->defaultRadioButton->Checked = true;
			defaultRadioButton_CheckedChanged(sender, e);
			//this->pictureBox1->Invalidate();
			
		}
		else if (e->Control && e->KeyCode == System::Windows::Forms::Keys::Q) {//directed
			//graph->Undo();
			//this->pictureBox1->Invalidate();
			this->directedRadioButton->Checked = true;
			directedRadioButton_CheckedChanged(sender, e);

		}
		else if (e->Control && e->KeyCode == System::Windows::Forms::Keys::W) {//undirected
			//graph->Undo();
			//this->pictureBox1->Invalidate();
			this->undirectedRadioButton->Checked = true;
			undirectedRadioButton_CheckedChanged(sender, e);
		}
		//pictureBox1->Invalidate();
		UpdateInfoPanel3();
	}
}