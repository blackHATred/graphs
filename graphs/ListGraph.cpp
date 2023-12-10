#include "ListGraph.h"


ListGraph::ListGraph(int size) : adjacencyLists(size) {}
ListGraph::ListGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++) {
        adjacencyLists[i] = graph.GetNextVertices(i);
    }
}
ListGraph::~ListGraph() = default;
void ListGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from].push_back(to);
}
int ListGraph::VerticesCount() const {
    return static_cast<int>(adjacencyLists.size());
}
std::vector<int> ListGraph::GetNextVertices(int vertex) const  {
    assert(0 <= vertex && vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}
std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> tmp;
    for (int from = 0; from < adjacencyLists.size(); from++) {
        for (int to: adjacencyLists[from]) {
            if (to == vertex) {
                tmp.push_back(from);
            }
        }
    }
    return tmp;
}
