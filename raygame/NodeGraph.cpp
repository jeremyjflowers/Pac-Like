#include "NodeGraph.h"
#include <raylib.h>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	std::deque<Node*> path; \
		//Check if the start or the goal pointer is null
		if (!start || !end)
		{
			//return an empty list
			return path;
		}

	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode = start;

	//Create an open list
	std::deque<Node*> openList;

	//Create a closed list
	std::deque<Node*> closedList;

	//Add start to the open list
	openList.push_front(start);

	//Loop while the open list is not empty
	while (!openList.empty())
	{
		//Sort the items in the open list by the f score
		for (int i = 0; i < openList.size(); i++)
		{
			for (int j = openList.size(); j > i; j--)
			{
				if (openList[i]->fScore > openList[j - 1]->fScore)
				{
					Node* temp = openList[i];
					openList[i] = openList[j - 1];
					openList[j - 1] = temp;
				}
			}
		}

		//Set the iterator to be the first item in the open list
		currentNode = openList.front();

		//Check if the iterator is pointing to the goal node
		if (currentNode == end)
		{
			//Return the new path found
			return path;
		}

		//Pop the first item off the open list
		openList.pop_front();

		//Add the first item to the closed list
		closedList.push_back(currentNode);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->connections.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* currentEdgeEnd = currentNode->connections[i].target;

			//Check if node at the end of the edge is in the closed list
			if (!isInList(closedList, currentEdgeEnd))
			{

				//Create a float and set it to be the g score of the iterator plus the cost of the edge
				int tempGScore = currentNode->gScore + currentNode->connections[i].cost;

				//Create a float and set it to be the h score of the node at the end of the edge
				float tempHScore = currentEdgeEnd->hScore;

				//Create a float for the f score and set it to be the g score combined with the h score
				float tempFScore = tempGScore + tempHScore;

				//Check if the node at the end of the edge is in the open list
				if (!isInList(closedList, currentEdgeEnd))
				{
					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = tempGScore;

					//Set the nodes h score to be the h score calculated earlier
					currentEdgeEnd->hScore = tempGScore;

					//Set the nodes f score to be the f score calculated earlier
					currentEdgeEnd->fScore = tempFScore;

					//Set the nodes previous to be the iterator
					currentEdgeEnd->previous = currentNode;

					//Add the node to the open list
					openList.push_back(currentEdgeEnd);
				}

				//Otherwise if the f score is less than the node at the end of the edge's f score...
				else if (currentNode->fScore < currentEdgeEnd->fScore)
				{
					//Set its g score to be the g score calculated earlier
					currentEdgeEnd->gScore = tempGScore;

					//Set the nodes h score to be the h score calculated earlier
					currentEdgeEnd->hScore = tempHScore;

					//Set its f score to be the f score calculated earlier
					currentEdgeEnd->fScore = tempFScore;

					//Set its previous to be the current node
					currentEdgeEnd->previous = currentNode;
				}
			}
		}
	}
}

void NodeGraph::drawGraph(Node* start)
{
	std::deque<Node*>* drawnList = new std::deque<Node*>();
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void NodeGraph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void NodeGraph::drawConnectedNodes(Node* node, std::deque<Node*>* drawnList)
{
	//drawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}

bool NodeGraph::isInList(std::deque<Node*> list, Node* node)
{

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == node)
			return true;
	}
	return false;
}