#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

class Node {		// To store information of the Maximum Spanning Tree
public:
	int Parent, MaxFlow, VertexNo;

	Node() :Parent(-1), MaxFlow(9999), VertexNo(-1) {}
	Node(int p, int m) : Parent(p), MaxFlow(m), VertexNo(-1) {}

};

int Case = 1;		// Output the correct Case number

// This function receives a graph with negative weigted edges
// As the edges are negative the most negative will intern be the orignal maximum value
void ModifiedPrims(int** Graph, int NumberOfVertices, bool* Visited) {

	for (int i = 0; i < NumberOfVertices; i++)		// to keep track of nodes that are visited
		Visited[i] = false;				

	Node * MaximumSpanningTree = new Node[NumberOfVertices];	// Storing Max Span Tree information
	int MaximumFlow = 0, MaximumIndex = -1;

	MaximumSpanningTree[0].MaxFlow = 0;		// Initializing source 0 to max flow 0 as it will have no parent

	for (int Edges = 0; Edges < NumberOfVertices - 1; Edges++) {		// Finding the Max Span tree
		int NodesMaxFlow = 9999;

		for (int i = 0; i < NumberOfVertices; i++) {		// This part finds the Maximum node from the current Vertex it is at
			if ((!Visited[i]) && (MaximumSpanningTree[i].MaxFlow < NodesMaxFlow)) {	// so that it can move the node with max flow edge
				NodesMaxFlow = MaximumSpanningTree[i].MaxFlow;
				MaximumIndex = i;						
			}
		}

		Visited[MaximumIndex] = true;		// making that node visited true

		for (int AdjacentV = 0; AdjacentV < NumberOfVertices; AdjacentV++) {	// Enqueues the nodes that are adjacent to the current Node
			if (!Visited[AdjacentV] && Graph[MaximumIndex][AdjacentV] != 0) {	// if the node is not visited and is not a self loop
				if ((Graph[MaximumIndex][AdjacentV]) < MaximumSpanningTree[AdjacentV].MaxFlow) {
					MaximumSpanningTree[AdjacentV].MaxFlow = Graph[MaximumIndex][AdjacentV];
					MaximumSpanningTree[AdjacentV].Parent = MaximumIndex;
				}
			}
		}
	}

	for (int i = 0; i < NumberOfVertices; i++) {	// As the Graph had negative edges the max flow stored was negative
		MaximumSpanningTree[i].MaxFlow *= -1;		// converting them back to the original max flows (+ve)
		MaximumSpanningTree[i].VertexNo = i;
	}

	int count = 0;		// counting the max no of edges

	for (int i = 0; i < NumberOfVertices;i++)
		if (MaximumSpanningTree[i].Parent != -1)
			count++;

	//	Displaying the Max Span Tree
	cout << "Case #" << Case << ": " << count << endl;

	for (int i = 1; i < NumberOfVertices; i++)
		cout << MaximumSpanningTree[i].Parent << " " << MaximumSpanningTree[i].VertexNo << " " << MaximumSpanningTree[i].MaxFlow << endl;

}
int main()
{
	int NumberOfTests = 0, NumberOfVertices = 0;
	cin >> NumberOfTests;

	for (int i = 0; i < NumberOfTests;i++) {

		cin >> NumberOfVertices;

		if (NumberOfVertices > 1) {
			int** Graph = new int* [NumberOfVertices];

			for (int i = 0; i < NumberOfVertices;i++)
				Graph[i] = new int[NumberOfVertices];

			for (int i = 0; i < NumberOfVertices; i++)
				for (int j = 0; j < NumberOfVertices; j++)
					cin >> Graph[i][j];


			// This part checks wether the case is Impossible or not
			// The vector will store the edges that need to be checked
			vector< pair<int, int> > ValidEdges;

			// only take the edge once as it is an undirected graph 
			for (int i = 0; i < NumberOfTests; i++) {
				for (int j = i + 1; j < NumberOfVertices; j++) {
					if (i == j)
						continue;

					ValidEdges.push_back({ i,j });
				}
			}

			// This part finds out the common node between to pairs and uses the remaining numbers apart from the common to check the certain edge
			// { 0 1 } { 0 2 } has { 0 } common so the edge to check will be { 1 , 2 } 
			// if the max flow of the pair is greater then the edge being checked the case is Impossible
			bool Impossible = false;
			for (int i = 0; i < ValidEdges.size() - 1; i++) {
				for (int j = i + 1; j < ValidEdges.size(); j++) {

					if (ValidEdges[i].first == ValidEdges[j].first) {

						if (min(Graph[ValidEdges[i].first][ValidEdges[i].second], Graph[ValidEdges[j].first][ValidEdges[j].second]) > Graph[ValidEdges[i].second][ValidEdges[j].second]) {
							Impossible = true;
							break;
						}

					}

					if (ValidEdges[i].second == ValidEdges[j].first) {
						if (min(Graph[ValidEdges[i].first][ValidEdges[i].second], Graph[ValidEdges[j].first][ValidEdges[j].second]) > Graph[ValidEdges[i].first][ValidEdges[j].second]) {
							Impossible = true;
							break;
						}
					}
					if (ValidEdges[i].first == ValidEdges[j].second) {
						if (min(Graph[ValidEdges[i].first][ValidEdges[i].second], Graph[ValidEdges[j].first][ValidEdges[j].second]) > Graph[ValidEdges[j].first][ValidEdges[i].second]) {
							Impossible = true;
							break;
						}
					}
					else
						continue;
				}
				if (Impossible)
					break;
			}

			if (Impossible) {
				cout << "Case #" << Case << ": " << "Impossible" << endl;
				Case++;
				continue;
			}

			// Negating edges to find the maximum
			for (int i = 0; i < NumberOfVertices; i++)
				for (int j = 0; j < NumberOfVertices; j++)
					Graph[i][j] *= -1;

			bool* Visited = new bool[NumberOfVertices];

			ModifiedPrims(Graph, NumberOfVertices, Visited);

			Case++;
		}
		else {
			// If input is not a pair then no cables will be required
			int waste;
			cin >> waste;
			cout << "Case #" << Case << ": " << "0" << endl;
			Case++;
		}

	}


}
