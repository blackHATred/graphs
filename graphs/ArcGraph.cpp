#include "ArcGraph.h"


ArcGraph::ArcGraph(int size) {
    // Увы, у set нельзя зарезервировать память. В целом, можно было бы использовать вектор, но set кажется более уместным
}
ArcGraph::ArcGraph(const IGraph &graph) {
    for (int i = 0; i < graph.VerticesCount(); i++)
        for (auto t : graph.GetNextVertices(i))
            pairs.insert({i, t});
}
ArcGraph::~ArcGraph() = default;
void ArcGraph::AddEdge(int from, int to) {
    pairs.insert({from, to});
}
int ArcGraph::VerticesCount() const {
    std::unordered_set<int> tmp;
    for (auto pair : pairs){
        tmp.insert(pair.first);
        tmp.insert(pair.second);
    }
    return static_cast<int>(tmp.size());
}
std::vector<int> ArcGraph::GetNextVertices(int vertex) const  {
    std::vector<int> tmp;
    for (auto pair : pairs)
        if (pair.first == vertex)
            tmp.push_back(pair.second);
    return tmp;
}
std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> tmp;
    for (auto pair : pairs)
        if (pair.second == vertex)
            tmp.push_back(pair.first);
    return tmp;
}
