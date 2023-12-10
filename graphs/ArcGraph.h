#ifndef ArcGraph_H
#define ArcGraph_H
#include <cassert>
#include <set>
#include <unordered_set>
#include "IGraph.h"

struct ArcGraph: public IGraph {
public:
    explicit ArcGraph(int size);
    explicit ArcGraph(const IGraph &graph);
    ~ArcGraph() override;
    void AddEdge(int from, int to) override;
    [[nodiscard]] int VerticesCount() const override;
    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::set<std::pair<int, int>> pairs;
};
#endif