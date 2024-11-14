
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "MyForm.h"
#include "Graph.h"
#include <cmath> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <msclr\marshal_cppstd.h>
#include <fstream>
using namespace System::Drawing::Drawing2D;
#using <Microsoft.VisualBasic.dll>
namespace Project2 {
    void MyForm::InitializeComponent(void)
    {
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
        this->undirectedRadioButton = (gcnew System::Windows::Forms::RadioButton());
        this->directedRadioButton = (gcnew System::Windows::Forms::RadioButton());

        // The buttons are now added directly to the toolStrip1 in the Items->AddRange call

        // Set form properties
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(800, 600);
        this->Controls->Add(this->pictureBox1);
        this->Controls->Add(this->infoPanel);
        //this->Controls->Add(this->undirectedRadioButton);
        //this->Controls->Add(this->directedRadioButton);
        //this->Controls->Add(this->menuStrip1);
        this->Controls->Add(this->toolStrip1);
        //this->MainMenuStrip = this->menuStrip1;
        this->Name = L"MyForm";
        this->Text = L"Graph Editor";
        this->ResumeLayout(false);
        this->PerformLayout();

        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
        this->menuStrip1->SuspendLayout();
        this->SuspendLayout();

        // pictureBox1
        this->pictureBox1->Location = System::Drawing::Point(12, 27);
        this->pictureBox1->Name = L"pictureBox1";
        this->pictureBox1->Size = System::Drawing::Size(558, 392);
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
        // infoPanel
        //this->infoPanel->Location = System::Drawing::Point(12, 425);
        //this->infoPanel->Multiline = true;
        //this->infoPanel->Name = L"infoPanel";
        //this->infoPanel->ReadOnly = true;
        //this->infoPanel->Size = System::Drawing::Size(558, 74);
        //this->infoPanel->TabIndex = 1;
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

        // menuStrip1
       /* this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
            this->fileToolStripMenuItem,
                this->editToolStripMenuItem
        });
        this->menuStrip1->Location = System::Drawing::Point(0, 0);
        this->menuStrip1->Name = L"menuStrip1";
        this->menuStrip1->Size = System::Drawing::Size(582, 24);
        this->menuStrip1->TabIndex = 2;
        this->menuStrip1->Text = L"menuStrip1";*/

        // fileToolStripMenuItem
        /*this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
            this->saveToolStripMenuItem,
                this->loadToolStripMenuItem
        });
        this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
        this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
        this->fileToolStripMenuItem->Text = L"File";*/

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

        // editToolStripMenuItem
        /*this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->changeEdgeColorToolStripMenuItem });
        this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
        this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
        this->editToolStripMenuItem->Text = L"Edit";*/

        // changeEdgeColorToolStripMenuItem
        this->changeEdgeColorToolStripMenuItem->Name = L"changeEdgeColorToolStripMenuItem";
        this->changeEdgeColorToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->changeEdgeColorToolStripMenuItem->Text = L"Change Edge Color";
        this->changeEdgeColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ChangeEdgeColor);

        // toolStrip1
        this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
            this->addEdgeButton,
                this->deleteEdgeButton,
                gcnew System::Windows::Forms::ToolStripButton("Save", nullptr, gcnew System::EventHandler(this, &MyForm::SaveGraph)),
                gcnew System::Windows::Forms::ToolStripButton("Load", nullptr, gcnew System::EventHandler(this, &MyForm::LoadGraph)),
                gcnew System::Windows::Forms::ToolStripButton("Run Dijkstra", nullptr, gcnew System::EventHandler(this, &MyForm::RunDijkstraButton_Click)),
                this->showGridButton,
        });
        this->toolStrip1->Location = System::Drawing::Point(0, 24);
        this->toolStrip1->Name = L"toolStrip1";
        this->toolStrip1->Size = System::Drawing::Size(582, 25);
        this->toolStrip1->TabIndex = 3;
        this->toolStrip1->Text = L"toolStrip1";

        // addEdgeButton
        this->addEdgeButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
        this->addEdgeButton->Name = L"addEdgeButton";
        this->addEdgeButton->Size = System::Drawing::Size(60, 22);
        this->addEdgeButton->Text = L"Add Edge";
        this->addEdgeButton->Click += gcnew System::EventHandler(this, &MyForm::AddEdgeButton_Click);

        // deleteEdgeButton
        this->deleteEdgeButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
        this->deleteEdgeButton->Name = L"deleteEdgeButton";
        this->deleteEdgeButton->Size = System::Drawing::Size(70, 22);
        this->deleteEdgeButton->Text = L"Delete Edge";
        this->deleteEdgeButton->Click += gcnew System::EventHandler(this, &MyForm::DeleteEdgeButton_Click);

        // showGridButton
        this->showGridButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
        this->showGridButton->Name = L"showGridButton";
        this->showGridButton->Size = System::Drawing::Size(60, 22);
        this->showGridButton->Text = L"Show Grid";
        this->showGridButton->Click += gcnew System::EventHandler(this, &MyForm::ShowGridButton_Click);

        // MyForm
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(582, 511);
        this->Controls->Add(this->infoPanel);
        this->Controls->Add(this->pictureBox1);
        //this->Controls->Add(this->menuStrip1);
        this->Controls->Add(this->toolStrip1);
        this->MainMenuStrip = this->menuStrip1;
        this->Name = L"MyForm";
        this->Text = L"Graph Drawing";
        this->Icon = gcnew System::Drawing::Icon("digr.ico");
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
        this->menuStrip1->ResumeLayout(false);
        this->menuStrip1->PerformLayout();
        this->ResumeLayout(false);
        this->PerformLayout(); 
        		// toolStrip1
		// Zoom In Zoom Out Button
        this->zoomInButton = (gcnew System::Windows::Forms::ToolStripButton("Zoom In", nullptr, gcnew System::EventHandler(this, &MyForm::ZoomIn)));
        this->zoomOutButton = (gcnew System::Windows::Forms::ToolStripButton("Zoom Out", nullptr, gcnew System::EventHandler(this, &MyForm::ZoomOut)));
        this->resetZoomButton = (gcnew System::Windows::Forms::ToolStripButton("Reset Zoom", nullptr, gcnew System::EventHandler(this, &MyForm::ResetZoom)));

        this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
            this->zoomInButton,
                this->zoomOutButton,
                this->resetZoomButton
        });
        //  undirectedRadioButton
        this->undirectedRadioButton->Location = System::Drawing::Point(600, 50);
        this->undirectedRadioButton->Name = L"undirectedRadioButton";
        this->undirectedRadioButton->Size = System::Drawing::Size(100, 20);
        this->undirectedRadioButton->TabIndex = 4;
        this->undirectedRadioButton->TabStop = true;
        this->undirectedRadioButton->Text = L"Undirected";
        this->undirectedRadioButton->UseVisualStyleBackColor = true;

        //  directedRadioButton
        //this->directedRadioButton->Location = System::Drawing::Point(600, 80);
        //this->directedRadioButton->Name = L"directedRadioButton";
        //this->directedRadioButton->Size = System::Drawing::Size(100, 20);
        //this->directedRadioButton->TabIndex = 5;
        //this->directedRadioButton->TabStop = true;
        //this->directedRadioButton->Text = L"Directed";
        //this->directedRadioButton->UseVisualStyleBackColor = true;
        this->directedRadioButton->Location = System::Drawing::Point(12, 425);
        this->directedRadioButton->Name = L"directedRadioButton";
        this->directedRadioButton->Size = System::Drawing::Size(104, 24);
        this->directedRadioButton->TabIndex = 1;
        this->directedRadioButton->TabStop = true;
        this->directedRadioButton->Text = L"Directed";
        this->directedRadioButton->UseVisualStyleBackColor = true;
        this->Controls->Add(this->directedRadioButton);
        //  directionComboBox
        this->directionComboBox = (gcnew System::Windows::Forms::ComboBox());
        this->directionComboBox->Location = System::Drawing::Point(600, 90);
        this->directionComboBox->Name = L"directionComboBox";
        this->directionComboBox->Size = System::Drawing::Size(100, 20);
        this->directionComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Start to End", L"End to Start" });
        this->directionComboBox->SelectedIndex = 0;
        this->Controls->Add(this->directionComboBox);

    }

    // Helper function to show an input box
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

    Vertex^ MyForm::FindVertexAtPoint(int x, int y) {
        for each (Vertex ^ v in graph->Vertices) {          
            if (Math::Abs(v->X - x) < 10 && Math::Abs(v->Y - y) < 10) {
                return v;
            }
        }
        return nullptr;
    }

    Edge^ MyForm::FindEdgeAtPoint(int x, int y) {
        for each (Edge ^ e in graph->Edges) {
            int x1 = e->Start->X, y1 = e->Start->Y, x2 = e->End->X, y2 = e->End->Y;
            double distance = Math::Abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1) /
                Math::Sqrt(Math::Pow(y2 - y1, 2) + Math::Pow(x2 - x1, 2));
            if (distance < 5) {
                return e;
            }
        }
        return nullptr;
    }

    void MyForm::AddEdge(Vertex^ start, Vertex^ end) {
        if (start != end) {
            int newId = graph->Edges->Count + 1;
            Edge^ newEdge = gcnew Edge(newId, start, end, 1, System::Drawing::Color::Black); // Default weight is 1, default color is Black
            graph->AddEdge(newEdge);
            UpdateInfoPanel();
            pictureBox1->Invalidate();
        }
    }
    void MyForm::AddEdge(Vertex^ start, Vertex^ end, bool isDirected)
    {
        Edge^ newEdge = gcnew Edge(start, end, currentEdgeColor);
        graph->Edges->Add(newEdge);
        if (!isDirected)
        {
            Edge^ reverseEdge = gcnew Edge(end, start, currentEdgeColor);
            graph->Edges->Add(reverseEdge);
        }
    }
    void MyForm::SomeFunction() {
    graph->AddEdge(selectedVertex, draggingVertex, currentEdgeColor, true);
    }
    void MyForm::DeleteVertex(Vertex^ vertex) {
        graph->RemoveVertex(vertex);
        UpdateInfoPanel();
        pictureBox1->Invalidate();
    }

    void MyForm::DeleteEdge(Edge^ edge) {
        graph->RemoveEdge(edge);
        UpdateInfoPanel();
        pictureBox1->Invalidate();
    }

    void MyForm::UpdateInfoPanel() {
        infoPanel->Text = "Vertices: " + graph->Vertices->Count + ", Edges: " + graph->Edges->Count;
    }

    System::Void MyForm::pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        Graphics^ g = e->Graphics;
        if (zoomFactor > 0 && !float::IsNaN(zoomFactor) && !float::IsInfinity(zoomFactor)) {
            g->ScaleTransform(zoomFactor, zoomFactor);
            g->TranslateTransform(viewOffsetX, viewOffsetY);
            //g->TranslateTransform(offset.X, offset.Y);
        }
        else {
            // Handle invalid zoomFactor case
        }
        int width = pictureBox1->Width;
        int height = pictureBox1->Height;
        if (showGrid) {
            Pen^ gridPen = gcnew Pen(Color::LightGray);
            int gridSize = static_cast<int>(20 * zoomFactor);  
            for (int x = 0; x <= pictureBox1->Width; x += gridSize) {
                g->DrawLine(gridPen, static_cast<float>(x), 0.0f, static_cast<float>(x), static_cast<float>(pictureBox1->Height));
            }
            for (int y = 0; y <= pictureBox1->Height; y += gridSize) {
                g->DrawLine(gridPen, 0.0f, static_cast<float>(y), static_cast<float>(pictureBox1->Width), static_cast<float>(y));
            }
        }
        DrawGraph(g);
        // calculate the nearest intersection point as well as while Zooming Out and In
        for each (Vertex ^ v in graph->Vertices) {
            int gridSize = 20;
            int nearestX = static_cast<int>(std::round(v->X / gridSize) * gridSize);

            int nearestY = static_cast<int>(std::round(v->Y / gridSize) * gridSize);
            g->FillEllipse(Brushes::Blue, static_cast<float>(nearestX - 5) * zoomFactor, static_cast<float>(nearestY - 5) * zoomFactor, 10.0f * zoomFactor, 10.0f * zoomFactor);
            g->DrawString(v->Name, this->Font, Brushes::Black, static_cast<float>(nearestX + 5) * zoomFactor, static_cast<float>(nearestY + 5) * zoomFactor);
            //g->FillEllipse(Brushes::Blue, static_cast<float>(nearestX - 5), static_cast<float>(nearestY - 5), 10.0f, 10.0f);
            //g->DrawString(v->Name, this->Font, Brushes::Black, static_cast<float>(nearestX + 5), static_cast<float>(nearestY + 5));
        }
        // Draw edges
        //for each (Edge ^ edge in graph->Edges) {
        //    Pen^ pen = gcnew Pen(edge->Color.IsEmpty ? currentEdgeColor : edge->Color);
        //    int nearestStartX = (edge->Start->X / 20) * 20;
        //    int nearestStartY = (edge->Start->Y / 20) * 20;
        //    int nearestEndX = (edge->End->X / 20) * 20;
        //    int nearestEndY = (edge->End->Y / 20) * 20;
        //    g->DrawLine(pen, static_cast<float>(nearestStartX), static_cast<float>(nearestStartY),
        //        static_cast<float>(nearestEndX), static_cast<float>(nearestEndY));
        //    // Draw weight
        //    int midX = (nearestStartX + nearestEndX) / 2;
        //    int midY = (nearestStartY + nearestEndY) / 2;
        //    g->DrawString(edge->Weight.ToString(), this->Font, Brushes::Red,
        //        static_cast<float>(midX), static_cast<float>(midY));
        for each (Edge ^ edge in graph->Edges) {
            Pen^ pen = gcnew Pen(edge->Color.IsEmpty ? currentEdgeColor : edge->Color);
            int gridSize = 20;
            int nearestStartX = static_cast<int>(std::round(edge->Start->X / gridSize) * gridSize);
            int nearestStartY = static_cast<int>(std::round(edge->Start->Y / gridSize) * gridSize);
            int nearestEndX = static_cast<int>(std::round(edge->End->X / gridSize) * gridSize);
            int nearestEndY = static_cast<int>(std::round(edge->End->Y / gridSize) * gridSize);
            g->DrawLine(pen, static_cast<float>(nearestStartX) * zoomFactor, static_cast<float>(nearestStartY) * zoomFactor,
                static_cast<float>(nearestEndX) * zoomFactor, static_cast<float>(nearestEndY) * zoomFactor);
            //g->DrawLine(pen, static_cast<float>(nearestStartX), static_cast<float>(nearestStartY),
                //static_cast<float>(nearestEndX), static_cast<float>(nearestEndY));
            // Draw weight
            int midX = (nearestStartX + nearestEndX) / 2;
            int midY = (nearestStartY + nearestEndY) / 2;
            g->DrawString(edge->Weight.ToString(), this->Font, Brushes::Red,
                static_cast<float>(midX) * zoomFactor, static_cast<float>(midY) * zoomFactor);
            //g->DrawString(edge->Weight.ToString(), this->Font, Brushes::Red,
            //    static_cast<float>(midX), static_cast<float>(midY));
            // Draw arrow for directed edges
            pen = gcnew Pen(Color::Black, 2.0f);  
            Pen^ pen2 = gcnew Pen(Color::Red, 2.0f);
            // Draw the line
            g->DrawLine(pen,
                PointF(static_cast<float>(nearestStartX) * zoomFactor, static_cast<float>(nearestStartY) * zoomFactor),
                PointF(static_cast<float>(nearestEndX) * zoomFactor, static_cast<float>(nearestEndY) * zoomFactor));

            // Draw the "<" icon at the end vertex if directedRadioButton is checked
            if (directedRadioButton->Checked) {
                float angle = atan2f(static_cast<float>(nearestEndY - nearestStartY), static_cast<float>(nearestEndX - nearestStartX));
                float iconSize = 10.0f; // Size of the "<" icon
                PointF point1(static_cast<float>(nearestEndX) * zoomFactor, static_cast<float>(nearestEndY) * zoomFactor);
                PointF point2(static_cast<float>(nearestEndX) * zoomFactor - iconSize * cosf(angle + static_cast<float>(M_PI) / 6),
                              static_cast<float>(nearestEndY) * zoomFactor - iconSize * sinf(angle + static_cast<float>(M_PI) / 6));
                PointF point3(static_cast<float>(nearestEndX) * zoomFactor - iconSize * cosf(angle - static_cast<float>(M_PI) / 6),
                              static_cast<float>(nearestEndY) * zoomFactor - iconSize * sinf(angle - static_cast<float>(M_PI) / 6));

                g->DrawLine(pen2, point1, point2);
                g->DrawLine(pen2, point1, point3); 
            }
        }
        g->ResetTransform();
    }
    void MyForm::AdjustVerticesToGrid()
    {
        int gridSize = 20;
        for each (Vertex ^ vertex in graph->Vertices)
        {
            vertex->X = static_cast<int>(std::round(vertex->X / (gridSize * zoomFactor)) * gridSize * zoomFactor);
            vertex->Y = static_cast<int>(std::round(vertex->Y / (gridSize * zoomFactor)) * gridSize * zoomFactor);
        }
    }
    void MyForm::DrawArrow(Graphics^ g, Pen^ pen, PointF start, PointF end)
    {
        g->DrawLine(pen, start, end);
        float dx = end.X - start.X;
        float dy = end.Y - start.Y;
        float length = sqrt(dx * dx + dy * dy);
        dx /= length;
        dy /= length;
        float arrowSize = 10.0f;
        PointF arrowPoint1(end.X - arrowSize * (dx - dy), end.Y - arrowSize * (dy + dx));
        PointF arrowPoint2(end.X - arrowSize * (dx + dy), end.Y - arrowSize * (dy - dx));
        g->DrawLine(pen, end, arrowPoint1);
        g->DrawLine(pen, end, arrowPoint2);
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
                graph->AddVertex(gcnew Vertex(id, "V" + id, x, y));
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
        // Implementation of Dijkstra's algorithm
        // This is a simplified version and might need to be adapted based on your Graph class implementation
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
        while (current != nullptr) {
            Vertex^ prev = previous[current];
            if (prev != nullptr) {
                for each (Edge ^ edge in graph->Edges) {
                    if ((edge->Start == prev && edge->End == current) ||
                        (edge->Start == current && edge->End == prev)) {
                        edge->Color = Color::Red;
                        break;
                    }
                }
            }
            current = prev;
        }

        pictureBox1->Invalidate();
    }


    void MyForm::pictureBox1_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
        Point cursorPos = e->Location;
        float zoomIncrement = 0.1f;
        if (e->Delta > 0) {
            zoomFactor += zoomIncrement;
        }
        else {
            zoomFactor -= zoomIncrement;
            if (zoomFactor < zoomIncrement) {
                zoomFactor = zoomIncrement;  
            }
        }
        zoomFactor = Math::Max(0.1f, Math::Min(zoomFactor, 10.0f));
        pictureBox1->Invalidate();
        float newCenterX = (cursorPos.X - viewOffsetX) / zoomFactor;
        float newCenterY = (cursorPos.Y - viewOffsetY) / zoomFactor;

        viewOffsetX = cursorPos.X - newCenterX * zoomFactor;
        viewOffsetY = cursorPos.Y - newCenterY * zoomFactor;

        pictureBox1->Invalidate();
    }


    void MyForm::DrawGraph(Graphics^ g)
    {
        // Draw grid if showGrid is true
        if (showGrid) {
            Pen^ gridPen = gcnew Pen(Color::LightGray);
            int gridSize = static_cast<int>(20 * zoomFactor); 
            for (int x = 0; x < static_cast<int>(pictureBox1->Width / zoomFactor); x += gridSize) {
                g->DrawLine(gridPen, static_cast<float>(x), 0.0f, static_cast<float>(x), static_cast<float>(pictureBox1->Height / zoomFactor));
            }
            for (int y = 0; y < static_cast<int>(pictureBox1->Height / zoomFactor); y += gridSize) {
                g->DrawLine(gridPen, 0.0f, static_cast<float>(y), static_cast<float>(pictureBox1->Width / zoomFactor), static_cast<float>(y));
            }
        }
        //Improve animation qualifications
        g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
        g->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAliasGridFit;

        // Draw edges
        //for each (Edge ^ edge in graph->Edges)
        //{
        //    Vertex^ start = edge->Start;
        //    Vertex^ end = edge->End;
        //    Point startCenter = Point(start->X, start->Y);
        //    Point endCenter = Point(end->X, end->Y);
        //    Pen^ pen = gcnew Pen(edge->Color, 2);
        //    g->DrawLine(pen, startCenter, endCenter);
        //    int midX = (startCenter.X + endCenter.X) / 2;
        //    int midY = (startCenter.Y + endCenter.Y) / 2;
        //    g->DrawString(edge->Weight.ToString(), this->Font, Brushes::Black, midX, midY);
        //}
        // Draw vertices
        //for each (Vertex ^ vertex in graph->Vertices)
        //{
        //    g->FillEllipse(Brushes::White, vertex->X - 15, vertex->Y - 15, 30, 30);
        //    g->DrawEllipse(Pens::Black, vertex->X - 15, vertex->Y - 15, 30, 30);
        //    g->DrawString(vertex->Name, this->Font, Brushes::Black, vertex->X - 5, vertex->Y - 7);
        //    // Draw the vertex degree
        //    String^ degreeStr = vertex->Degree.ToString();
        //    g->DrawString(degreeStr, this->Font, Brushes::Red, vertex->X - 15, vertex->Y - 30);
        //}
    }

    System::Void MyForm::AddEdgeButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
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
        for each (Vertex ^ vertex in graph->Vertices)
        {
            startComboBox->Items->Add(vertex->Name);
            endComboBox->Items->Add(vertex->Name);
        }

        // Show the form and get the result
        if (inputForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            String^ startVertexName = startComboBox->SelectedItem->ToString();
            String^ endVertexName = endComboBox->SelectedItem->ToString();
            int weight;
            bool isDirected = directedRadioButton->Checked;

            if (Int32::TryParse(weightTextBox->Text, weight))
            {
                Vertex^ startVertex = nullptr;
                Vertex^ endVertex = nullptr;

                // Find the selected vertices
                for each (Vertex ^ vertex in graph->Vertices)
                {
                    if (vertex->Name == startVertexName)
                        startVertex = vertex;
                    if (vertex->Name == endVertexName)
                        endVertex = vertex;
                }

                if (startVertex != nullptr && endVertex != nullptr)
                {
                    // Create a new edge and add it to the graph
                    Edge^ newEdge = gcnew Edge(graph->Edges->Count + 1, startVertex, endVertex, weight, currentEdgeColor, directedRadioButton->Checked);
                    graph->AddEdge(newEdge);
                    pictureBox1->Invalidate();
                    //graph->AddEdge(startVertex, endVertex, currentEdgeColor, directedRadioButton->Checked);
                    //pictureBox1->Invalidate();
                }
            }
        }
        if (selectedVertex != nullptr && draggingVertex != nullptr)
        {
            bool isDirected = directedRadioButton->Checked;
            AddEdge(selectedVertex, draggingVertex, isDirected);
            selectedVertex = nullptr;
            draggingVertex = nullptr;
            pictureBox1->Invalidate();
            if (undirectedRadioButton->Checked)
            {
                //undirected edge
                graph->AddEdge(selectedVertex, draggingVertex, currentEdgeColor, false);
            }
            else if (directedRadioButton->Checked)
            {
                //directed edge
                if (directionComboBox->SelectedIndex == 0)
                {
                    // Start to End
                    graph->AddEdge(selectedVertex, draggingVertex, currentEdgeColor, true);
                }
                else
                {
                    // Nguoc lai
                    graph->AddEdge(draggingVertex, selectedVertex, currentEdgeColor, true);
                }
            }
            pictureBox1->Invalidate();
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
    System::Void MyForm::ShowGridButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        showGrid = !showGrid;
        pictureBox1->Invalidate();
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

    System::Void MyForm::pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        //int adjustedX = e->X;
        //int adjustedY = e->Y;
        //this->mouseX = e->X; this->mouseY = e->Y; this->single_Click = true; this->clickTimer->Start();
        int adjustedX = static_cast<int>(std::round(e->X * zoomFactor));
        int adjustedY = static_cast<int>(std::round(e->Y * zoomFactor));
    if (e->Button == System::Windows::Forms::MouseButtons::Left)
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
                if (isNameExist){
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
                { MessageBox::Show("The name is too long. Please choose a name with fewer than 10 characters.", "Name Too Long", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
/*PointF MyForm::ScreenToWorld(Point screenPoint) {
    return PointF((screenPoint.X / zoomFactor) - offset.X, (screenPoint.Y / zoomFactor) - offset.Y);*/
    //}

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
    System::Void MyForm::clickTimer_Tick(System::Object^ sender, System::EventArgs^ e)
    {

        //this->clickTimer->Stop();
        //if (this->single_Click) {
        //    int adjustedX = static_cast<int>(std::round(this->mouseX * zoomFactor));
        //    int adjustedY = static_cast<int>(std::round(this->mouseY * zoomFactor));
        //    
        //    Vertex^ clickedVertex = FindVertexAtPoint(adjustedX, adjustedY);
        //    if (clickedVertex != nullptr) { String^ newVertexName = PromptForVertexName(); 
        //    if (!String::IsNullOrEmpty(newVertexName)) { if (newVertexName->Length > 20) { MessageBox::Show("The name is too long. Please choose a name with fewer than 20 characters.", "Name Too Long", MessageBoxButtons::OK, MessageBoxIcon::Error); return; } bool isNameExist = false; for each (Vertex ^ v in graph->Vertices) { if (v->Name == newVertexName) { isNameExist = true; break; } } if (isNameExist) { MessageBox::Show("The name already exists. Please choose another name.", "Duplicate Name", MessageBoxButtons::OK, MessageBoxIcon::Error); } else { clickedVertex->Name = newVertexName; pictureBox1->Invalidate(); } } }
        //    else if (draggingVertex == nullptr) 
        //    {
        //        String^ vertexName = PromptForVertexName(); 
        //        if (!String::IsNullOrEmpty(vertexName)) 
        //        { if (vertexName->Length > 10) { 
        //            MessageBox::Show("The name is too long. Please choose a name with fewer than 10 characters.", "Name Too Long", MessageBoxButtons::OK, MessageBoxIcon::Error);
        //            return; 
        //        } 
        //        bool isNameExist = false; 
        //        for each (Vertex ^ v in graph->Vertices) 
        //        { 
        //            if (v->Name == vertexName) 
        //            { 
        //                isNameExist = true; 
        //                break; 
        //            } 
        //        } if (isNameExist) 
        //        { MessageBox::Show("The name already exists. Please choose another name.", "Duplicate Name", MessageBoxButtons::OK, MessageBoxIcon::Error);
        //        }
        //        else { 
        //           int newId = graph->Vertices->Count + 1;
        //            Vertex^ newVertex = gcnew Vertex(newId, vertexName, adjustedX, adjustedY); 
        //            
        //            graph->AddVertex(newVertex); pictureBox1->Invalidate(); } } }
        //}
        
        /*PointF MyForm::ScreenToWorld(Point screenPoint) {
            return PointF((screenPoint.X / zoomFactor) - offset.X, (screenPoint.Y / zoomFactor) - offset.Y);*/

    }
        
    System::Void MyForm::pictureBox1_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        //this->single_Click = false;
        //int adjustedX = static_cast<int>(std::round(e->X * zoomFactor));
        //int adjustedY = static_cast<int>(std::round(e->Y * zoomFactor));
        //Vertex^ doubleclickedVertex = FindVertexAtPoint(adjustedX, adjustedY);
        //if (doubleclickedVertex != nullptr)
        //{
        //    String^ newVertexName = PromptForVertexName();
        //    if (!String::IsNullOrEmpty(newVertexName))
        //    {
        //        if (newVertexName->Length > 10) {
        //            MessageBox::Show("The name is too long. Please choose a name with fewer than 10 characters.", "Name Too Long",
        //                MessageBoxButtons::OK, MessageBoxIcon::Error);
        //            return;
        //        }
        //        bool isName = false;
        //        for each (Vertex ^ v in graph->Vertices) {
        //            if (v->Name == newVertexName)
        //            {
        //                isName = true;
        //                break;
        //            }
        //        }
        //        if (isName) { MessageBox::Show("The name already exists. Please choose another name.", "Duplicate Name", MessageBoxButtons::OK, MessageBoxIcon::Error); }
        //        pictureBox1->Invalidate();
        //        
        //    }
        //}
    }

    
    System::Void MyForm::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
    {
        Vertex^ hoveredVertex = FindVertexAtPoint(e->X, e->Y);
        Edge^ hoveredEdge = FindEdgeAtPoint(e->X, e->Y);
        if (isPanning) {
            Point currentMousePos = e->Location;
            viewOffsetX += currentMousePos.X - lastMousePos.X;
            viewOffsetY += currentMousePos.Y - lastMousePos.Y;
            lastMousePos = currentMousePos;
            pictureBox1->Invalidate();
        }
        if (hoveredVertex != nullptr) {
            this->Cursor = Cursors::Hand;
        }
        else if (hoveredEdge != nullptr) {
            this->Cursor = Cursors::Cross;
        }
        else {
            this->Cursor = Cursors::Default;
        }
    }
    System::Void MyForm::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left) {
            draggingVertex = FindVertexAtPoint(e->X, e->Y);
        }
        if (e->Button == System::Windows::Forms::MouseButtons::Middle) {
            isPanning = true;
            lastMousePos = e->Location;
        }
    }
    System::Void MyForm::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
    {
        if (draggingVertex != nullptr) {
            draggingVertex->X = e->X;
            draggingVertex->Y = e->Y;
            draggingVertex = nullptr;
            pictureBox1->Invalidate();
        }
        if (e->Button == System::Windows::Forms::MouseButtons::Middle) {
            isPanning = false;
        }
    }
    System::Void MyForm::SaveGraph(System::Object^ sender, System::EventArgs^ e) 
    {
        SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
        saveFileDialog1->Filter = "Text File|*.txt";
        saveFileDialog1->Title = "Save Graph";
        saveFileDialog1->ShowDialog();
        if (saveFileDialog1->FileName != "") {
            System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(saveFileDialog1->FileName);
            sw->WriteLine(graph->Vertices->Count);
            for each (Vertex ^ v in graph->Vertices) {
                sw->WriteLine(v->Id + " " + v->X + " " + v->Y);
            }
            sw->WriteLine(graph->Edges->Count);
            for each (Edge ^ e in graph->Edges) {
                sw->WriteLine(e->Start->Id + " " + e->End->Id + " " + e->Weight);
            }
            sw->Close();
        }
    }
    System::Void MyForm::ChangeEdgeColor(System::Object^ sender, System::EventArgs^ e) 
    {
        ColorDialog^ colorDialog1 = gcnew ColorDialog();
        if (colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            currentEdgeColor = colorDialog1->Color;
            for each (Edge ^ edge in graph->Edges) {
                edge->Color = currentEdgeColor;
            }
            pictureBox1->Invalidate();
        }
    }
    System::Void MyForm::ZoomIn(System::Object^ sender, System::EventArgs^ e)
    {
        //Point cursorPos = pictureBox1->PointToClient(Cursor->Position);
        //PointF cursorPosF = PointF(cursorPos.X / zoomFactor - offset.X, cursorPos.Y / zoomFactor - offset.Y);

        zoomFactor *= 1.1f;
        AdjustVerticesToGrid();
        pictureBox1->Invalidate();
    }

    System::Void MyForm::ZoomOut(System::Object^ sender, System::EventArgs^ e)
    {
        zoomFactor /= 1.1f;
        if (zoomFactor < 0.1f) zoomFactor = 0.1f;
        AdjustVerticesToGrid();
        pictureBox1->Invalidate();
    }

    System::Void MyForm::ResetZoom(System::Object^ sender, System::EventArgs^ e)
    {
        zoomFactor = 1.0f;
        pictureBox1->Invalidate();
    }
    void Project2::MyForm::ZoomInButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        zoomFactor *= 1.1f; 
        AdjustVerticesToGrid();
        pictureBox1->Invalidate();
    }

    void Project2::MyForm::ZoomOutButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        zoomFactor /= 1.1f; 
        AdjustVerticesToGrid();
        pictureBox1->Invalidate();
    }
    
    //void MyForm::Zoom(float factor) {
    //    Point cursorPos = pictureBox1->PointToClient(Cursor->Position);
    //    PointF cursorPosF = PointF(cursorPos.X / zoomFactor - offset.X, cursorPos.Y / zoomFactor - offset.Y);

    //    zoomFactor *= factor;
    //    offset = PointF(cursorPosF.X - cursorPos.X / zoomFactor, cursorPosF.Y - cursorPos.Y / zoomFactor);

    //    pictureBox1->Invalidate();
    //}

}
