// test_MyForm.cpp
// Unit tests for the MyForm class

#include "pch.h"
#include "CppUnitTest.h"
#include "../Project2/MyForm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Project2;

namespace Project2Tests
{
	TEST_CLASS(MyFormTests)
	{
	public:

		TEST_METHOD(TestAddVertexAtCursor)
		{
			// Arrange
			MyForm^ form = gcnew MyForm();
			form->InitializeComponent();
			Point cursorPosition(100, 100);

			// Act
			form->AddVertexAtCursor(cursorPosition);

			// Assert
			Assert::AreEqual(1, form->graph->Vertices->Count);
			Vertex^ vertex = form->graph->Vertices[0];
			Assert::AreEqual(100.0f, vertex->X);
			Assert::AreEqual(100.0f, vertex->Y);
		}

		TEST_METHOD(TestAddEdge)
		{
			// Arrange
			MyForm^ form = gcnew MyForm();
			form->InitializeComponent();
			Vertex^ startVertex = gcnew Vertex(1, "A", 100, 100);
			Vertex^ endVertex = gcnew Vertex(2, "B", 200, 200);
			form->graph->AddVertex(startVertex);
			form->graph->AddVertex(endVertex);

			// Act
			form->graph->AddEdge("A", "B", 10, true);

			// Assert
			Assert::AreEqual(1, form->graph->Edges->Count);
			Edge^ edge = form->graph->Edges[0];
			Assert::AreEqual(startVertex, edge->Start);
			Assert::AreEqual(endVertex, edge->End);
			Assert::AreEqual(10, edge->Weight);
			Assert::IsTrue(edge->Directed);
		}

		TEST_METHOD(TestDeleteVertex)
		{
			// Arrange
			MyForm^ form = gcnew MyForm();
			form->InitializeComponent();
			Vertex^ vertex = gcnew Vertex(1, "A", 100, 100);
			form->graph->AddVertex(vertex);

			// Act
			form->DeleteVertex(vertex);

			// Assert
			Assert::AreEqual(0, form->graph->Vertices->Count);
		}

		TEST_METHOD(TestDeleteEdge)
		{
			// Arrange
			MyForm^ form = gcnew MyForm();
			form->InitializeComponent();
			Vertex^ startVertex = gcnew Vertex(1, "A", 100, 100);
			Vertex^ endVertex = gcnew Vertex(2, "B", 200, 200);
			form->graph->AddVertex(startVertex);
			form->graph->AddVertex(endVertex);
			Edge^ edge = gcnew Edge(startVertex, endVertex, 10, Color::Black, true);
			form->graph->AddEdge(edge);

			// Act
			form->DeleteEdge(edge);

			// Assert
			Assert::AreEqual(0, form->graph->Edges->Count);
		}

		TEST_METHOD(TestZoomIn)
		{
			// Arrange
			MyForm^ form = gcnew MyForm();
			form->InitializeComponent();
			float initialZoomFactor = form->zoomFactor;

			// Act
			form->ZoomIn(nullptr, nullptr);

			// Assert
			Assert::IsTrue(form->zoomFactor > initialZoomFactor);
		}

		TEST_METHOD(TestZoomOut)
		{
			// Arrange
			MyForm^ form = gcnew MyForm();
			form->InitializeComponent();
			float initialZoomFactor = form->zoomFactor;

			// Act
			form->ZoomOut(nullptr, nullptr);

			// Assert
			Assert::IsTrue(form->zoomFactor < initialZoomFactor);
		}

		TEST_METHOD(TestResetZoom)
		{
			// Arrange
			MyForm^ form = gcnew MyForm();
			form->InitializeComponent();
			form->zoomFactor = 2.0f;
			form->viewOffsetX = 100;
			form->viewOffsetY = 100;

			// Act
			form->ResetZoom(nullptr, nullptr);

			// Assert
			Assert::AreEqual(1.0f, form->zoomFactor);
			Assert::AreEqual(0, form->viewOffsetX);
			Assert::AreEqual(0, form->viewOffsetY);
		}

		TEST_METHOD(TestShowGridButton_Click)
		{
			// Arrange
			MyForm^ form = gcnew MyForm();
			form->InitializeComponent();
			bool initialShowGrid = form->showGrid;

			// Act
			form->ShowGridButton_Click(nullptr, nullptr);

			// Assert
			Assert::AreEqual(!initialShowGrid, form->showGrid);
		}

		TEST_METHOD(TestRunDijkstra)
		{
			// Arrange
			MyForm^ form = gcnew MyForm();
			form->InitializeComponent();
			Vertex^ startVertex = gcnew Vertex(1, "A", 100, 100);
			Vertex^ endVertex = gcnew Vertex(2, "B", 200, 200);
			form->graph->AddVertex(startVertex);
			form->graph->AddVertex(endVertex);
			form->graph->AddEdge("A", "B", 10, true);

			// Act
			form->RunDijkstra(startVertex, endVertex);

			// Assert
			Edge^ edge = form->graph->Edges[0];
			Assert::AreEqual(Color::Red, edge->Color);
		}
	};
}