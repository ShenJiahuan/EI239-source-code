#include <iostream>
#include "MST.h"
#include "util/generate.h"

int main() {

    std::vector<Node> node = {"a", "b", "c", "d", "e", "f", "g", "h"};
    std::vector<Edge> edge = {
        {"a", "b", 4}, {"a", "c", 3}, {"b", "c", 5}, {"b", "d", 5},
        {"b", "e", 9}, {"c", "d", 5}, {"c", "h", 5}, {"d", "e", 7},
        {"d", "f", 6}, {"d", "g", 5}, {"d", "h", 4}, {"e", "f", 3},
        {"f", "g", 2}, {"g", "h", 6}
    };
    MST tree(node, edge);
    auto edgeList = tree.prim();
    for (auto edge : edgeList) {
        std::cout << edge.src << " -> " << edge.dest << " " << edge.weight << std::endl;
    }

    /*
    std::vector<Node> node;
    std::vector<Edge> edge;
    std::tie(node, edge) = generate();
    MST tree(node, edge);
    auto edgeList = tree.prim();
    for (auto edge : edgeList) {
        std::cout << edge.src << " -> " << edge.dest << ": " << edge.weight << std::endl;
    }
     */
    return 0;
}