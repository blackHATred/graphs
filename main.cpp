#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <cassert>
#include <functional>
#include "graphs/ListGraph.h"
#include "graphs/MatrixGraph.h"
#include "graphs/SetGraph.h"
#include "graphs/ArcGraph.h"


void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)>& func) {
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty()) {
        int currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        for (int nextVertex: graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void BFS(const IGraph &graph, const std::function<void(int)>& func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            BFS(graph, i, visited, func);
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)>& func) {
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex: graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex])
            DFS(graph, nextVertex, visited, func);
    }
}

void DFS(const IGraph &graph, const std::function<void(int)>& func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            DFS(graph, i, visited, func);
    }
}

void topologicalSort(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted) {
    visited[vertex] = true;

    for (int nextVertex: graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex])
            topologicalSort(graph, nextVertex, visited, sorted);
    }

    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph) {
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            topologicalSort(graph, i, visited, sorted);
    }
    return sorted;
}

int main() {
    ArcGraph arcGraph(9);
    arcGraph.AddEdge(0, 1);
    arcGraph.AddEdge(0, 5);
    arcGraph.AddEdge(1, 2);
    arcGraph.AddEdge(1, 3);
    arcGraph.AddEdge(1, 5);
    arcGraph.AddEdge(1, 6);
    arcGraph.AddEdge(3, 2);
    arcGraph.AddEdge(3, 4);
    arcGraph.AddEdge(3, 6);
    arcGraph.AddEdge(5, 4);
    arcGraph.AddEdge(5, 6);
    arcGraph.AddEdge(6, 4);
    arcGraph.AddEdge(7, 8);
    // скопируем граф в другие реализации
    ListGraph listGraph(arcGraph);
    MatrixGraph matrixGraph(listGraph);
    SetGraph setGraph(matrixGraph);

    // убедимся, что для случайно выбранной вершины совпадает список предыдущих и следующих вершин
    int random_vertex = rand() % 9;
    assert(listGraph.GetNextVertices(random_vertex) == arcGraph.GetNextVertices(random_vertex));
    assert(arcGraph.GetNextVertices(random_vertex) == matrixGraph.GetNextVertices(random_vertex));
    assert(matrixGraph.GetNextVertices(random_vertex) == setGraph.GetNextVertices(random_vertex));

    // Теперь убедимся, что bfs и dfs работают идентично. По-хорошему нужно проверять снятие вершин по слоям, при такой
    // проверке порядок вершин может различаться. Тем не менее ввиду реализации порядок будет совпадать для любого типа
    std::vector<std::vector<int>> BFSs(4);
    std::vector<std::vector<int>> DFSs(4);
    BFS(listGraph, [&BFSs](int vertex){ BFSs[0].push_back(vertex); });
    BFS(matrixGraph, [&BFSs](int vertex){ BFSs[1].push_back(vertex); });
    BFS(arcGraph, [&BFSs](int vertex){ BFSs[2].push_back(vertex); });
    BFS(setGraph, [&BFSs](int vertex){ BFSs[3].push_back(vertex); });
    assert(BFSs[0] == BFSs[1]);
    assert(BFSs[1] == BFSs[2]);
    assert(BFSs[2] == BFSs[3]);
    DFS(listGraph, [&DFSs](int vertex){ DFSs[0].push_back(vertex); });
    DFS(matrixGraph, [&DFSs](int vertex){ DFSs[1].push_back(vertex); });
    DFS(arcGraph, [&DFSs](int vertex){ DFSs[2].push_back(vertex); });
    DFS(setGraph, [&DFSs](int vertex){ DFSs[3].push_back(vertex); });
    assert(DFSs[0] == DFSs[1]);
    assert(DFSs[1] == DFSs[2]);
    assert(DFSs[2] == DFSs[3]);

    // и напоследок проверяем работу топологической сортировки
    assert(topologicalSort(listGraph) == topologicalSort(arcGraph));
    assert(topologicalSort(arcGraph) == topologicalSort(matrixGraph));
    assert(topologicalSort(matrixGraph) == topologicalSort(setGraph));

    return 0;
}