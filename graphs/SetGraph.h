#ifndef SetGraph_H
#define SetGraph_H
#include <cassert>
#include <set>
#include "IGraph.h"

struct SetGraph: public IGraph {
public:
    explicit SetGraph(int size);
    explicit SetGraph(const IGraph &graph);
    ~SetGraph() override;
    void AddEdge(int from, int to) override;
    [[nodiscard]] int VerticesCount() const override;
    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;
private:
    // в целом можно и unordered_set юзануть, смотря какую задачу решаем и как будет оптимальнее
    // в этом решении буду использовать set, чтобы порядок вывода результата был тем же, что и у
    // MatrixGraph и ListGraph
    std::vector<std::set<int>> adjacencySets;
};
#endif