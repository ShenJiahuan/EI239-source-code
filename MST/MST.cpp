//
// Created by 沈嘉欢 on 2018-12-19.
//

#include <iostream>
#include "MST.h"

MST::MST(const std::vector<Node> &nodeList, const std::vector<Edge> &edgeList): remain(nodeList.size() - 1), edge(edgeList) {
    for (const auto &edge : edgeList) {
        edgeFrom[edge.src].push_back(edge);
        edgeFrom[edge.dest].push_back(edge);
    }
    for (const auto &node : nodeList) {
        used[node] = false;
    }
}

std::vector<Edge> MST::prim() {
    std::vector<Edge> primMST;
    Node first = (used.begin())->first;
    used[first] = true;
    for (const auto &edge : edgeFrom[first]) {
        available.push(edge);
    }
    while (remain) {
        if (available.size() == 0) {
            return std::vector<Edge>();
        }
        Edge next = available.top();
        available.pop();
        while (used[next.src] && used[next.dest]) {
            next = available.top();
            available.pop();
        }
        Node newNode = next.src;
        if (used[next.src]) {
            newNode = next.dest;
        }
        used[newNode] = true;
        for (const auto &edge : edgeFrom[newNode]) {
            if (!used[edge.src] || !used[edge.dest]) {
                available.push(edge);
            }
        }
        primMST.push_back(next);
        --remain;
    }
    return primMST;
}