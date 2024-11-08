
#include "MyForm.h"
#include <msclr\marshal_cppstd.h>
#include <fstream>
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

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

        // infoPanel
        this->infoPanel->Location = System::Drawing::Point(12, 425);
        this->infoPanel->Multiline = true;
        this->infoPanel->Name = L"infoPanel";
        this->infoPanel->ReadOnly = true;
        this->infoPanel->Size = System::Drawing::Size(558, 74);
        this->infoPanel->TabIndex = 1;

        // menuStrip1
        this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
            this->fileToolStripMenuItem,
                this->editToolStripMenuItem
        });
        this->menuStrip1->Location = System::Drawing::Point(0, 0);
        this->menuStrip1->Name = L"menuStrip1";
        this->menuStrip1->Size = System::Drawing::Size(582, 24);
        this->menuStrip1->TabIndex = 2;
        this->menuStrip1->Text = L"menuStrip1";

        // fileToolStripMenuItem
        this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
            this->saveToolStripMenuItem,
                this->loadToolStripMenuItem
        });
        this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
        this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
        this->fileToolStripMenuItem->Text = L"File";

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
        this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->changeEdgeColorToolStripMenuItem });
        this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
        this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
        this->editToolStripMenuItem->Text = L"Edit";

        // changeEdgeColorToolStripMenuItem
        this->changeEdgeColorToolStripMenuItem->Name = L"changeEdgeColorToolStripMenuItem";
        this->changeEdgeColorToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->changeEdgeColorToolStripMenuItem->Text = L"Change Edge Color";
        this->changeEdgeColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ChangeEdgeColor);

        // MyForm
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(582, 511);
        this->Controls->Add(this->infoPanel);
        this->Controls->Add(this->pictureBox1);
        this->Controls->Add(this->menuStrip1);
        this->MainMenuStrip = this->menuStrip1;
        this->Name = L"MyForm";
        this->Text = L"Graph Drawing";
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
        this->menuStrip1->ResumeLayout(false);
        this->menuStrip1->PerformLayout();
        this->ResumeLayout(false);
        this->PerformLayout();
    }

    void MyForm::DrawGraph(Graphics^ g)
    {
        // Draw edges
        for each (Edge ^ edge in graph->Edges)
        {
            Vertex^ start = edge->Start;
            Vertex^ end = edge->End;

            // Ensure that the color is valid
            Color edgeColor;
            try
            {
                edgeColor = ColorTranslator::FromHtml(edge->Color);
            }
            catch (System::Exception^)
            {
                edgeColor = Color::Black; // Default color if parsing fails
            }

            Pen^ pen = gcnew Pen(edgeColor);
            g->DrawLine(pen, start->X, start->Y, end->X, end->Y);
            delete pen; // Clean up the pen object
        }

        // Draw vertices
        for each (Vertex ^ vertex in graph->Vertices)
        {
            int x = vertex->X;
            int y = vertex->Y;

            // Draw the vertex as a filled circle
            g->FillEllipse(Brushes::Blue, x - 5, y - 5, 10, 10);

            // Draw the vertex name
            g->DrawString(vertex->Name, this->Font, Brushes::Black, (float)x + 5, (float)y + 5);

            // Draw the vertex degree
            g->DrawString(vertex->Degree.ToString(), this->Font, Brushes::Red, (float)x - 15, (float)y - 15);
        }

        // Draw a temporary edge if in drawing mode
        if (isDrawingEdge && selectedVertex != nullptr)
        {
            // Get the current position of the cursor in screen coordinates
            System::Drawing::Point cursorPosition = System::Windows::Forms::Cursor::Position;

            // Convert the screen coordinates to client coordinates of the picture box
            Point mousePosition = pictureBox1->PointToClient(cursorPosition);

            // Draw the temporary edge
            g->DrawLine(Pens::Gray, selectedVertex->X, selectedVertex->Y, mousePosition.X, mousePosition.Y);
        }
    }

    Vertex^ MyForm::FindVertexAtPoint(int x, int y)
    {
        for each (Vertex^ vertex in graph->Vertices)
        {
            int dx = x - vertex->X;
            int dy = y - vertex->Y;
            if (dx * dx + dy * dy <= 25) // 5^2, assuming vertex radius is 5
            {
                return vertex;
            }
        }
        return nullptr;
    }

    Edge^ MyForm::FindEdgeAtPoint(int x, int y)
    {
        for each (Edge^ edge in graph->Edges)
        {
            Vertex^ start = edge->Start;
            Vertex^ end = edge->End;
            int x1 = start->X, y1 = start->Y;
            int x2 = end->X, y2 = end->Y;

            // Calculate the distance from the point to the line segment
            double distance = Math::Abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1) /
                Math::Sqrt(Math::Pow(y2 - y1, 2) + Math::Pow(x2 - x1, 2));

            if (distance <= 5) // Assuming edge width is 5
            {
                return edge;
            }
        }
        return nullptr;
    }

    void MyForm::AddEdge(Vertex^ start, Vertex^ end)
    {
        if (start != nullptr && end != nullptr && start != end)
        {
            int id = graph->Edges->Count + 1;
            Edge^ newEdge = gcnew Edge(id, start, end, 1, currentEdgeColor.Name);
            graph->AddEdge(newEdge);
            start->Degree++;
            end->Degree++;
        }
    }

    void MyForm::DeleteVertex(Vertex^ vertex)
    {
        if (vertex != nullptr)
        {
            List<Edge^>^ edgesToRemove = gcnew List<Edge^>();
            for each (Edge^ edge in graph->Edges)
            {
                if (edge->Start == vertex || edge->End == vertex)
                {
                    edgesToRemove->Add(edge);
                }
            }
            for each (Edge^ edge in edgesToRemove)
            {
                DeleteEdge(edge);
            }
            graph->RemoveVertex(vertex->Id);
            if (selectedVertex == vertex)
            {
                selectedVertex = nullptr;
            }
        }
    }

    void MyForm::DeleteEdge(Edge^ edge)
    {
        if (edge != nullptr)
        {
            edge->Start->Degree--;
            edge->End->Degree--;
            graph->RemoveEdge(edge->Id);
        }
    }

    void MyForm::UpdateInfoPanel()
    {
        String^ info = "Graph Information:";
        info += "Vertices: " + graph->Vertices->Count + "\t";
        info += "Edges: " + graph->Edges->Count + "\n";

        info += "Vertex Details:";
        for each (Vertex^ vertex in graph->Vertices)
        {
            info += "  " + vertex->Name + " (ID: " + vertex->Id + ")\t";
            info += "    Position: (" + vertex->X + ", " + vertex->Y + ")\t";
            info += "    Degree: " + vertex->Degree + "\n";
        }

        info += "Edge Details: ";
        for each (Edge^ edge in graph->Edges)
        {
            info += "  " + edge->Start->Name + " - " + edge->End->Name + " (ID: " + edge->Id + ")";
        }

        infoPanel->Text = info;
    }

    System::Void MyForm::pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
    {
        DrawGraph(e->Graphics);
    }

    System::Void MyForm::pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left)
        {
            Vertex^ clickedVertex = FindVertexAtPoint(e->X, e->Y);
            if (clickedVertex == nullptr)
            {
                int id = graph->Vertices->Count + 1;
                Vertex^ newVertex = gcnew Vertex(id, "V" + id, e->X, e->Y);
                graph->AddVertex(newVertex);
            }
        }
        else if (e->Button == System::Windows::Forms::MouseButtons::Right)
        {
            Vertex^ clickedVertex = FindVertexAtPoint(e->X, e->Y);
            if (clickedVertex != nullptr)
            {
                DeleteVertex(clickedVertex);
            }
            else
            {
                Edge^ clickedEdge = FindEdgeAtPoint(e->X, e->Y);
                if (clickedEdge != nullptr)
                {
                    DeleteEdge(clickedEdge);
                }
            }
        }
        pictureBox1->Invalidate();
        UpdateInfoPanel();
    }

    System::Void MyForm::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (selectedVertex != nullptr && e->Button == System::Windows::Forms::MouseButtons::Left)
        {
            selectedVertex->X = e->X;
            selectedVertex->Y = e->Y;
            pictureBox1->Invalidate();
        }
        else if (isDrawingEdge && e->Button == System::Windows::Forms::MouseButtons::Left)
        {
            pictureBox1->Invalidate();
        }
    }

    System::Void MyForm::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left)
        {
            selectedVertex = FindVertexAtPoint(e->X, e->Y);
            if (selectedVertex != nullptr)
            {
                isDrawingEdge = true;
            }
        }
    }

    System::Void MyForm::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left)
        {
            if (isDrawingEdge && selectedVertex != nullptr)
            {
                Vertex^ endVertex = FindVertexAtPoint(e->X, e->Y);
                if (endVertex != nullptr && endVertex != selectedVertex)
                {
                    AddEdge(selectedVertex, endVertex);
                }
                isDrawingEdge = false;
                pictureBox1->Invalidate();
                UpdateInfoPanel();
            }
            selectedVertex = nullptr;
        }
    }

    System::Void MyForm::SaveGraph(System::Object^ sender, System::EventArgs^ e)
    {
        SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
        saveFileDialog1->Filter = "JSON files (*.json)|*.json|All files (*.*)|*.*";
        saveFileDialog1->FilterIndex = 1;
        saveFileDialog1->RestoreDirectory = true;

        if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            try
            {
                System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(saveFileDialog1->FileName);
                sw->WriteLine("{");
                sw->WriteLine("  \"vertices\": [");
                for (int i = 0; i < graph->Vertices->Count; i++)
                {
                    Vertex^ v = graph->Vertices[i];
                    sw->WriteLine("    {");
                    sw->WriteLine("      \"id\": " + v->Id + ",");
                    sw->WriteLine("      \"name\": "" + v->Name + "",");
                    sw->WriteLine("      \"x\": " + v->X + ",");
                    sw->WriteLine("      \"y\": " + v->Y + ",");
                    sw->WriteLine("      \"degree\": " + v->Degree);
                    sw->WriteLine("    }" + (i < graph->Vertices->Count - 1 ? "," : ""));
                }
                sw->WriteLine("  ],");
                sw->WriteLine("  \"edges\": [");
                for (int i = 0; i < graph->Edges->Count; i++)
                {
                    Edge^ e = graph->Edges[i];
                    sw->WriteLine("    {");
                    sw->WriteLine("      \"id\": " + e->Id + ",");
                    sw->WriteLine("      \"start\": " + e->Start->Id + ",");
                    sw->WriteLine("      \"end\": " + e->End->Id + ",");
                    sw->WriteLine("      \"weight\": " + e->Weight + ",");
                    sw->WriteLine("      \"color\": "" + e->Color + """);
                    sw->WriteLine("    }" + (i < graph->Edges->Count - 1 ? "," : ""));
                }
                sw->WriteLine("  ]");
                sw->WriteLine("}");
                sw->Close();
                MessageBox::Show("Graph saved successfully!", "Save Graph", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (System::Exception^ ex)
            {
                MessageBox::Show("Error saving graph: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    System::Void MyForm::LoadGraph(System::Object^ sender, System::EventArgs^ e)
    {
        OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
        openFileDialog1->Filter = "JSON files (*.json)|*.json|All files (*.*)|*.*";
        openFileDialog1->FilterIndex = 1;
        openFileDialog1->RestoreDirectory = true;

        if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            try
            {
                String^ jsonString = System::IO::File::ReadAllText(openFileDialog1->FileName);
                graph = gcnew Graph(); // Clear existing graph

                System::Text::RegularExpressions::Regex^ regex = gcnew System::Text::RegularExpressions::Regex("\{([^{}]|\{[^{}]*\})*\}");
                System::Text::RegularExpressions::MatchCollection^ matches = regex->Matches(jsonString);

                for each (System::Text::RegularExpressions::Match ^ match in matches)
                {
                    String^ obj = match->Value;
                    if (obj->Contains("name"))
                    {
                        // This is a vertex
                        int id = System::Convert::ToInt32(System::Text::RegularExpressions::Regex::Match(obj, "\"id\":\\s*(\\d+)")->Groups[1]->Value);
                        String^ name = System::Text::RegularExpressions::Regex::Match(obj, "\"name\":\\s*\"([^\"]*)\"")->Groups[1]->Value;
                        int x = System::Convert::ToInt32(System::Text::RegularExpressions::Regex::Match(obj, "\"x\":\\s*(\\d+)")->Groups[1]->Value);
                        int y = System::Convert::ToInt32(System::Text::RegularExpressions::Regex::Match(obj, "\"y\":\\s*(\\d+)")->Groups[1]->Value);
                        int degree = System::Convert::ToInt32(System::Text::RegularExpressions::Regex::Match(obj, "\"degree\":\\s*(\\d+)")->Groups[1]->Value);

                        Vertex^ v = gcnew Vertex(id, name, x, y);
                        v->Degree = degree;
                        graph->AddVertex(v);
                    }
                    else if (obj->Contains("start"))
                    {
                        // This is an edge
                        int id = System::Convert::ToInt32(System::Text::RegularExpressions::Regex::Match(obj, "\"id\":\\s*(\\d+)")->Groups[1]->Value);
                        int startId = System::Convert::ToInt32(System::Text::RegularExpressions::Regex::Match(obj, "\"start\":\\s*(\\d+)")->Groups[1]->Value);
                        int endId = System::Convert::ToInt32(System::Text::RegularExpressions::Regex::Match(obj, "\"end\":\\s*(\\d+)")->Groups[1]->Value);
                        int weight = System::Convert::ToInt32(System::Text::RegularExpressions::Regex::Match(obj, "\"weight\":\\s*(\\d+)")->Groups[1]->Value);
                        String^ color = System::Text::RegularExpressions::Regex::Match(obj, "\"color\":\\s*\"([^\"]*)\"")->Groups[1]->Value;

                        Vertex^ start = nullptr;
                        Vertex^ end = nullptr;
                        for each (Vertex ^ v in graph->Vertices)
                        {
                            if (v->Id == startId) start = v;
                            if (v->Id == endId) end = v;
                            if (start && end) break;
                        }

                        if (start && end)
                        {
                            Edge^ e = gcnew Edge(id, start, end, weight, color);
                            graph->AddEdge(e);
                        }
                    }
                }

                pictureBox1->Invalidate();
                UpdateInfoPanel();
                MessageBox::Show("Graph loaded successfully!", "Load Graph", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (System::Exception^ ex)
            {
                MessageBox::Show("Error loading graph: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    System::Void MyForm::ChangeEdgeColor(System::Object^ sender, System::EventArgs^ e)
    {
        ColorDialog^ colorDialog = gcnew ColorDialog();
        if (colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            currentEdgeColor = colorDialog->Color;
        }
    }
    [STAThread]
        void main(array<String^>^ args)
    {
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);
        Project2::MyForm form; // Assuming MyForm is your main form
        Application::Run(% form);
    }
}
