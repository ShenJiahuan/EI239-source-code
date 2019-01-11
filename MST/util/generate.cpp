//
// Created by 沈嘉欢 on 2018-12-19.
//

#include "generate.h"

std::tuple<std::vector<Node>, std::vector<Edge>> generate()  {
    std::random_device rd;
    auto gen = std::mt19937(rd());
    auto dis1 = std::uniform_int_distribution<>(2, 30);
    auto dis2 = std::uniform_int_distribution<>(1, 100);
    int vertices = dis1(gen);
    std::vector<Node> node(vertices);
    for (int i = 1; i <= vertices; ++i) {
        node[i - 1] = std::to_string(i);
    }
    std::vector<Edge> edge;
    for (int i = 1; i <= vertices; ++i) {
        for (int j = i + 1; j <= vertices; ++j) {
            edge.push_back({std::to_string(i), std::to_string(j), static_cast<uint32_t>(dis2(gen))});
        }
    }
    return std::make_tuple(node, edge);
}