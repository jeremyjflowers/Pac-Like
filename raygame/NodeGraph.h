#pragma once
#include <Vector2.h>
#include <deque>
#include <vector>

namespace NodeGraph
{
	struct Node;

	struct Edge
	{
		Node* target;
		float cost;
	};

	struct Node
	{
		MathLibrary::Vector2 position;

		float gScore;
		float hScore;
		float fScore;
		Node* previous;

		std::vector<Edge> connections;
	};

	/// <summary>
	/// Find a path from the start node to the end node.
	/// IMPLEMENT this function.
	/// </summary>
	/// <param name="start">The first node in the path</param>
	/// <param name="end">The destination node</param>
	/// <returns>A deque storing the found path</returns>
	std::deque<Node*> findPath(Node* start, Node* end);

	/// <summary>
	/// Draw the entire graph. Currently has very poor performance.
	/// </summary>
	/// <param name="start">The beginning of the graph</param>
	void drawGraph(Node* start);

	/// <summary>
	/// Draw a single node on the graph.
	/// </summary>
	/// <param name="node">The node to draw</param>
	/// <param name="color">The color to use in 0xRRGGBBAA format</param>
	void drawNode(Node* node, int color = 0xFFFFFFFF);

	/// <summary>
	/// Draw all nodes connected to the given node, excluding all nodes on the drawnList.
	/// This function is called by drawGraph(Node*).
	/// </summary>
	/// <param name="node">The node to start</param>
	/// <param name="drawnList">Nodes that have already been drawn</param>
	void drawConnectedNodes(Node* node, std::deque<Node*>* drawnList = nullptr);

	bool isInList(std::deque<Node*> list, Node* node);
};