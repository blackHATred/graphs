#ifndef ListGraph_H
#define ListGraph_H
#include <cassert>
#include "IGraph.h"

struct ListGraph: public IGraph {
public:
    explicit ListGraph(int size);
    explicit ListGraph(const IGraph &graph);
    ~ListGraph() override;
    void AddEdge(int from, int to) override;
    [[nodiscard]] int VerticesCount() const override;
    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<int>> adjacencyLists;
};
#endif