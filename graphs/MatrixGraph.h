#ifndef MatrixGraph_H
#define MatrixGraph_H
#include <cassert>
#include "IGraph.h"

struct MatrixGraph: public IGraph {
public:
    explicit MatrixGraph(int size);
    explicit MatrixGraph(const IGraph &graph);
    ~MatrixGraph() override;
    void AddEdge(int from, int to) override;
    [[nodiscard]] int VerticesCount() const override;
    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<bool>> matrix;
};
#endif