//
// Created by 沈嘉欢 on 2018-12-19.
//

#ifndef MST_MST_H
#define MST_MST_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using Node = std::string;

struct Edge {
    Node src, dest;
    uint32_t weight;
    bool operator<(const Edge &rhs) const {
        return weight < rhs.weight;
    }
    bool operator>(const Edge &rhs) const {
        return weight > rhs.weight;
    }
};

class MST {
private:
    size_t remain;
    std::unordered_map<Node, bool> used;
    std::vector<Edge> edge;
    std::unordered_map<Node, std::vector<Edge>> edgeFrom;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> available;
public:
    MST(const std::vector<Node> &nodeList, const std::vector<Edge> &edgeList);
    std::vector<Edge> prim();
};


#endif //MST_MST_H
