#include "SetGraph.h"


SetGraph::SetGraph(int size) {
    adjacencySets.resize(size);
}
SetGraph::SetGraph(const IGraph &graph) : adjacencySets(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++)
        for (auto t : graph.GetNextVertices(i))
            adjacencySets[i].insert(t);
}
SetGraph::~SetGraph() = default;
void SetGraph::AddEdge(int from, int to) {
    adjacencySets[from].insert(to);
}
int SetGraph::VerticesCount() const {
    return static_cast<int>(adjacencySets.size());
}
std::vector<int> SetGraph::GetNextVertices(int vertex) const  {
    return {adjacencySets[vertex].begin(), adjacencySets[vertex].end()};
}
std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> tmp;
    for (int from = 0; from < adjacencySets.size(); from++) {
        for (int to: adjacencySets[from]) {
            if (to == vertex) {
                tmp.push_back(from);
            }
        }
    }
    return tmp;
}
