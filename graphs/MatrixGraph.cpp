#include "MatrixGraph.h"


MatrixGraph::MatrixGraph(int size) {
    matrix.reserve(size);
    for (int i = 0; i < size; i++) {
        matrix.emplace_back(size);
    }
}
MatrixGraph::MatrixGraph(const IGraph &graph) {
    matrix.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); i++){
        matrix[i].resize(graph.VerticesCount(), false);
    }
    for (int i = 0; i < graph.VerticesCount(); i++) {
        for (auto t : graph.GetNextVertices(i))
            matrix[i][t] = true;
    }
}
MatrixGraph::~MatrixGraph() = default;
void MatrixGraph::AddEdge(int from, int to) {
    matrix[from][to] = true;
}
int MatrixGraph::VerticesCount() const {
    return static_cast<int>(matrix.size());
}
std::vector<int> MatrixGraph::GetNextVertices(int vertex) const  {
    std::vector<int> tmp;
    for (int i = 0; i < VerticesCount(); i++){
        if (matrix[vertex][i]) {
            tmp.push_back(i);
        }
    }
    return tmp;
}
std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> tmp;
    for (int i = 0; i < VerticesCount(); i++){
        if (matrix[i][vertex]) {
            tmp.push_back(i);
        }
    }
    return tmp;
}
