
// MyForm.cpp
// Implementation of the MyForm class for a graph editor application

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "MyForm.h"
#include "Graph.h"
#include <cmath> 
#include <msclr\marshal_cppstd.h>
#include <fstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace System::Drawing::Drawing2D;
#using <Microsoft.VisualBasic.dll>

namespace Project2 {
	// InitializeComponent: Initializes all the UI components of the form
	void MyForm::InitializeComponent(void)
	{
		// Initialize and configure the default radio button
		this->defaultRadioButton = (gcnew System::Windows::Forms::RadioButton());
		this->defaultRadioButton->AutoSize = true;
		this->defaultRadioButton->Checked = true;
		this->defaultRadioButton->Location = System::Drawing::Point(700, 90);
		this->defaultRadioButton->Name = L"defaultRadioButton";
		this->defaultRadioButton->Size = System::Drawing::Size(40, 20);
		this->defaultRadioButton->TabIndex = 6;
		this->defaultRadioButton->TabStop = true;
		this->defaultRadioButton->Text = L"Default";
		this->defaultRadioButton->UseVisualStyleBackColor = true;
		this->defaultRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::defaultRadioButton_CheckedChanged);
		//this->defaultRadioButton->Dock = System::Windows::Forms::DockStyle::Right;

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
		//this->LayoutPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
		//this->ControlPanel = (gcnew System::Windows::Forms::Panel());

		// The buttons are now added directly to the toolStrip1 in the Items->AddRange call

		// Set form properties

		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(800, 700);
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
		this->pictureBox1->Size = System::Drawing::Size(680,650);
		this->pictureBox1->TabIndex = 0;
		this->pictureBox1->TabStop = false;
		this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
		this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseClick);
		this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
		this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
		this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
		this->pictureBox1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseWheel);
		this->pictureBox1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDoubleClick);
		

		// infoPanel 2
		this->infoPanel->Location = System::Drawing::Point(12, 27);
		this->infoPanel->Name = L"infoPanel";
		this->infoPanel->Size = System::Drawing::Size(558, 392);
		this->infoPanel->TabIndex = 0;
		this->infoPanel->TabStop = false;

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
		//this->undirectedRadioButton->Dock = System::Windows::Forms::DockStyle::Fill;
		this->undirectedRadioButton->UseVisualStyleBackColor = true;
		this->Controls->Add(this->undirectedRadioButton);

		// directedRadioButton
		this->directedRadioButton->Location = System::Drawing::Point(700, 70);
		this->directedRadioButton->Name = L"directedRadioButton";
		this->directedRadioButton->Size = System::Drawing::Size(100, 20);
		this->directedRadioButton->TabIndex = 1;
		this->directedRadioButton->TabStop = true;
		this->directedRadioButton->Text = L"Directed";
		//this->directedRadioButton->Dock = System::Windows::Forms::DockStyle::Fill;
		this->directedRadioButton->UseVisualStyleBackColor = true;
		this->Controls->Add(this->directedRadioButton);

		// directionComboBox
		this->directionComboBox = (gcnew System::Windows::Forms::ComboBox());
		this->directionComboBox->Location = System::Drawing::Point(695, 110);
		this->directionComboBox->Name = L"directionComboBox";
		this->directionComboBox->Size = System::Drawing::Size(100, 20);
		this->directionComboBox->Anchor = AnchorStyles::Right;
		//this->directionComboBox->Dock = System::Windows::Forms::DockStyle::Fill;

		this->directionComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Start to End", L"End to Start" });
		this->directionComboBox->SelectedIndex = 0;
		this->Controls->Add(this->directionComboBox);
		//No fit
		this->WindowState = System::Windows::Forms::FormWindowState::Normal;
		this->MaximizeBox = false;
		this->MinimizeBox = false;


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
			float x1 = e->Start->X, y1 = e->Start->Y, x2 = e->End->X, y2 = e->End->Y;
			double distance = Math::Abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1) /
				Math::Sqrt(Math::Pow(y2 - y1, 2) + Math::Pow(x2 - x1, 2));
			if (distance < 5) {
				return e;
			}
		}
		return nullptr;
	}


	// DeleteVertex: Removes a vertex from the graph and updates the UI
	void MyForm::DeleteVertex(Vertex^ vertex) {
		graph->RemoveVertex(vertex);
		UpdateInfoPanel();
		pictureBox1->Invalidate();
	}

	// DeleteEdge: Removes an edge from the graph and updates the UI
	void MyForm::DeleteEdge(Edge^ edge) {
		graph->RemoveEdge(edge);
		UpdateInfoPanel();
		pictureBox1->Invalidate();
	}

	// UpdateInfoPanel: Updates the information panel with current graph statistics
	void MyForm::UpdateInfoPanel() {
		infoPanel->Text = "Vertices: " + graph->Vertices->Count + "\r\n";
		infoPanel->Text += "Edges: " + graph->Edges->Count + "\r\n";
	}

	// pictureBox1_Paint: Handles the painting of the graph on the picture box
	System::Void MyForm::pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
		Graphics^ g = e->Graphics;
		g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
		g->Clear(Color::White);

		// Apply zoom and pan transformations

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

		// Draw edges
		for each (Edge ^ edge in graph->Edges)
		{
			Pen^ pen = gcnew Pen(edge->Color, 2 / zoomFactor);
			g->DrawLine(pen, edge->Start->X, edge->Start->Y, edge->End->X, edge->End->Y);
			delete pen;

			// Draw arrow for directed edges
			if (edge->Directed)
			{
				DrawArrow(g, edge->Start, edge->End);
			}

			// Draw edge weight
			if (edge->Weight != 0)
			{
				float midX = (edge->Start->X + edge->End->X) / 2;
				float midY = (edge->Start->Y + edge->End->Y) / 2;
				g->DrawString(edge->Weight.ToString(), this->Font, Brushes::Black, midX, midY);
			}
		}

		// Draw vertices
		for each (Vertex ^ vertex in graph->Vertices)
		{
			SolidBrush^ brush = gcnew SolidBrush(vertex->ColorProperty);
			g->FillEllipse(brush, vertex->X - vertex->Radius, vertex->Y - vertex->Radius, vertex->Radius * 2, vertex->Radius * 2);
			delete brush;

			// Highlight selected vertex
			if (defaultRadioButton->Checked && vertex == selectedVertex)
			{
				Pen^ highlightPen = gcnew Pen(Color::Red, 2 / zoomFactor);
				g->DrawEllipse(highlightPen, vertex->X - vertex->Radius - 2, vertex->Y - vertex->Radius - 2, (vertex->Radius + 2) * 2, (vertex->Radius + 2) * 2);
				delete highlightPen;
			}

			g->DrawString(vertex->Name, this->Font, Brushes::Black, vertex->X - vertex->Radius, vertex->Y - vertex->Radius - 15);
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

		String^ vertexName = PromptForVertexName();
		if (!String::IsNullOrEmpty(vertexName)) {
			Vertex^ newVertex = gcnew Vertex(graph->Vertices->Count + 1, vertexName, adjustedX, adjustedY);
			graph->AddVertex(newVertex);
			pictureBox1->Invalidate();
		}
	}
	System::Void MyForm::RunDijkstraButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (graph->Vertices->Count < 2) {
			MessageBox::Show("Please add at least two vertices to run Dijkstra's algorithm.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		for each (Edge ^ edge in graph->Edges) {
			edge->Color = Color::Empty;
		}
		int startId, endId;
		String^ startIdStr = ShowInputBox("Enter the ID of the start vertex:", "Start Vertex", "1");
		String^ endIdStr = ShowInputBox("Enter the ID of the end vertex:", "End Vertex", "2");
		if (Int32::TryParse(startIdStr, startId) && Int32::TryParse(endIdStr, endId)) {

			Vertex^ start = graph->GetVertexById(startId);
			Vertex^ end = graph->GetVertexById(endId);

			if (start != nullptr && end != nullptr) {
				RunDijkstra(start, end);
			}
			else {
				MessageBox::Show("Invalid start or end vertex ID.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		else {
			MessageBox::Show("Invalid input. Please enter numeric IDs.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void MyForm::LoadGraph(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
		openFileDialog1->Filter = "Text File|*.txt";
		openFileDialog1->Title = "Load Graph";
		openFileDialog1->ShowDialog();

		if (openFileDialog1->FileName != "") {
			graph->Clear();
			System::IO::StreamReader^ sr = gcnew System::IO::StreamReader(openFileDialog1->FileName);
			int vertexCount = System::Int32::Parse(sr->ReadLine());
			for (int i = 0; i < vertexCount; i++) {
				array<String^>^ parts = sr->ReadLine()->Split(' ');
				int id = System::Int32::Parse(parts[0]);
				int x = System::Int32::Parse(parts[1]);
				int y = System::Int32::Parse(parts[2]);
				graph->AddVertex(gcnew Vertex(id, "V" + id, static_cast<float>(x), static_cast<float>(y)));
			}
			int edgeCount = System::Int32::Parse(sr->ReadLine());
			for (int i = 0; i < edgeCount; i++) {
				array<String^>^ parts = sr->ReadLine()->Split(' ');
				int startId = System::Int32::Parse(parts[0]);
				int endId = System::Int32::Parse(parts[1]);
				int weight = System::Int32::Parse(parts[2]);
				Vertex^ start = graph->GetVertexById(startId);
				Vertex^ end = graph->GetVertexById(endId);
				graph->AddEdge(gcnew Edge(i + 1, start, end, weight, System::Drawing::Color::Black));
			}
			sr->Close();
			UpdateInfoPanel();
			pictureBox1->Invalidate();
		}
	}

	void MyForm::RunDijkstra(Vertex^ start, Vertex^ end) {
		bool isDirected = directedRadioButton->Checked;
		// Implementation of Dijkstra's algorithm
		Dictionary<Vertex^, int>^ distances = gcnew Dictionary<Vertex^, int>();
		Dictionary<Vertex^, Vertex^>^ previous = gcnew Dictionary<Vertex^, Vertex^>();
		List<Vertex^>^ unvisited = gcnew List<Vertex^>();

		for each (Vertex ^ v in graph->Vertices) {
			distances[v] = Int32::MaxValue;
			previous[v] = nullptr;
			unvisited->Add(v);
		}
		distances[start] = 0;

		while (unvisited->Count > 0) {
			Vertex^ current = nullptr;
			for each (Vertex ^ v in unvisited) {
				if (current == nullptr || distances[v] < distances[current]) {
					current = v;
				}
			}

			if (current == end) break;

			unvisited->Remove(current);

			for each (Edge ^ edge in graph->Edges) {
				if (edge->Start == current) {
					int alt = distances[current] + edge->Weight;
					if (alt < distances[edge->End]) {
						distances[edge->End] = alt;
						previous[edge->End] = current;
					}
				}
			}
		}

		// Highlight the shortest path
		Vertex^ current = end;
		bool pathExists = true;
		while (current != nullptr) {
			Vertex^ prev = previous[current];
			if (prev != nullptr) {
				bool edgeFound = false;
				for each (Edge ^ edge in graph->Edges) {
					if ((edge->Start == prev && edge->End == current) ||
						(!isDirected && edge->Start == current && edge->End == prev)) {
						edge->Color = Color::Red;
						edgeFound = true;
						break;
					}
				}
				if (!edgeFound) {
					pathExists = false;
					break;
				}
			}
			current = prev;
		}

		if (!pathExists) {
			MessageBox::Show("No path found from start to end vertex. Please check the direction of the edges.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

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
		inputForm->MinimizeBox = false;

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
				int weight;
				if (Int32::TryParse(weightTextBox->Text, weight)) {
					if (undirectedRadioButton->Checked) {
						graph->AddEdge(startVertexName, endVertexName, weight); // false for undirected
					}
					else if (directedRadioButton->Checked) {
						graph->AddEdge(startVertexName, endVertexName, weight, true); // true for directed
					}
				}
				else {
					MessageBox::Show("Please enter a valid integer for the weight.");
				}
			}
			else {
				MessageBox::Show("Please select both start and end vertices.");
			}
		}
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

	// pictureBox1_MouseClick: Handles mouse click events on the picture box
	// This function manages vertex and edge creation, selection, and deletion
	System::Void MyForm::pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		float adjustedX = (e->X - viewOffsetX) / zoomFactor;
		float adjustedY = (e->Y - viewOffsetY) / zoomFactor;
		if (e->Button == System::Windows::Forms::MouseButtons::Left && draggingVertex == nullptr)
		{
			//PointF worldPoint = ScreenToWorld(e->Location);
			Vertex^ clickedVertex = FindVertexAtPoint(adjustedX, adjustedY);
			if (clickedVertex != nullptr)
			{
				String^ newVertexName = PromptForVertexName();
				if (!String::IsNullOrEmpty(newVertexName))
				{
					if (newVertexName->Length >= 10)
					{
						if (newVertexName->Length > 10) {
							MessageBox::Show("The name is too long. Please choose a name with fewer than 10 characters.", "Name Too Long", MessageBoxButtons::OK, MessageBoxIcon::Error);
							return;
						}
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
					if (isNameExist) {
						MessageBox::Show("The name already exists. Please choose another name.", "Duplicate Name",
							MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
					else {
						clickedVertex->Name = newVertexName;
						pictureBox1->Invalidate();
					}
				}
			}
			else if (draggingVertex == nullptr)
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
		UpdateInfoPanel();
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
		this->clickTimer->Stop();
		float adjustedX = static_cast<float>((this->mouseX * zoomFactor));
		float adjustedY = static_cast<float>((this->mouseY * zoomFactor));
		if (this->single_Click && !this->doubleClickOccured)
		{
			if (this->mouseButtonClicked == System::Windows::Forms::MouseButtons::Left)
			{
				Vertex^ clickedVertex = FindVertexAtPoint(adjustedX, adjustedY);
				if (clickedVertex != nullptr)
				{
					String^ newVertexName = PromptForVertexName();
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
					}
				}
				else if (draggingVertex == nullptr)
				{
					String^ vertexName = PromptForVertexName();
					if (!String::IsNullOrEmpty(vertexName))
					{
						if (vertexName->Length > 10)
						{
							MessageBox::Show("The name is too long. Please choose a name with fewer than 10 characters.",
								"Name Too Long", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
							MessageBox::Show("The name already exists. Please choose another name.",
								"Duplicate Name", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
		UpdateInfoPanel();
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
			//float adjustedX = static_cast<float>((this->mouseX * zoomFactor));
			//float adjustedY = static_cast<float>((this->mouseY * zoomFactor));
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
					draggedVertex->X = newX;
					draggedVertex->Y = newY;
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
	}

	// DrawArrow: Draws an arrow head at the end of an edge
	void MyForm::DrawArrow(Graphics^ g, Vertex^ start, Vertex^ end) {
		float dx = end->X - start->X;
		float dy = end->Y - start->Y;
		float angle = Math::Atan2(dy, dx);
		float length = Math::Sqrt(dx * dx + dy * dy);

		// Calculate the arrow head points
		array<PointF>^ arrowHead = gcnew array<PointF>(3);
		arrowHead[0] = PointF(end->X, end->Y);
		arrowHead[1] = PointF(end->X - 15 * Math::Cos(angle - Math::PI / 6), end->Y - 15 * Math::Sin(angle - Math::PI / 6));
		arrowHead[2] = PointF(end->X - 15 * Math::Cos(angle + Math::PI / 6), end->Y - 15 * Math::Sin(angle + Math::PI / 6));

		// Draw the arrow head
		g->FillPolygon(Brushes::Black, arrowHead);
	}

	// pictureBox1_MouseDown: Handles mouse button press events on the picture box
	System::Void MyForm::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			Vertex^ clickedVertex = FindVertexAtPoint(e->X, e->Y);
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
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
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
				Vertex^ clickedVertex = FindVertexAtPoint(e->X, e->Y);
				if (selectedVertex != nullptr && clickedVertex != nullptr && clickedVertex != selectedVertex) {
					// Handle edge creation
					bool isDirected = directedRadioButton->Checked;
					graph->AddEdge(selectedVertex->Name, clickedVertex->Name, 0, isDirected);
					pictureBox1->Invalidate();
				}
				else if (clickedVertex == nullptr && !isDragging) {
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
	}

	System::Void MyForm::SaveGraph(System::Object^ sender, System::EventArgs^ e) {
		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "Graph Files (*.graph)|*.graph|All Files (*.*)|*.*";
		saveFileDialog->DefaultExt = "graph";
		saveFileDialog->AddExtension = true;

		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ fileName = saveFileDialog->FileName;
			graph->SaveToFile(fileName);
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
	}

	System::Void MyForm::directedRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (directedRadioButton->Checked) {
			// Enable edge drawing mode (directed)
			isDrawingEdge = true;
			selectedVertex = nullptr;
			pictureBox1->Cursor = Cursors::Cross;
		}
	}

	System::Void MyForm::undirectedRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (undirectedRadioButton->Checked) {
			// Enable edge drawing mode (undirected)
			isDrawingEdge = true;
			selectedVertex = nullptr;
			pictureBox1->Cursor = Cursors::Cross;
		}
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
}






