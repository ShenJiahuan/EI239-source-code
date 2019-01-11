#pragma once
//
// Created by 沈嘉欢 on 2018-12-18.
//

#ifndef TOPOLOGICALSORT_DAG_H
#define TOPOLOGICALSORT_DAG_H

#include <vector>
#include <string>
#include <map>
#include <deque>
#include <set>

struct Lesson {
    std::string id;
    int credit;
    std::vector<std::string> pre;
};


using Plan = std::vector<std::set<std::string>>;
using Sequence = std::deque<std::string>;


class DAG {
private:
    size_t size;
    int maxCredit;
    size_t semesterCount;
    int link;
    double mean;
    std::map<std::string, std::set<std::string>> graph;
    std::map<std::string, size_t> inDegree;
    std::map<std::string, int> credits;
    std::vector<Sequence> topSort(Sequence &path, std::set<std::string> &notVisited);

public:
    DAG(std::vector<Lesson> lessons, int maxCredit, size_t semesterCount);
    std::vector<Sequence> topSort();
    std::vector<Plan> parse(Sequence seq, bool init, std::vector<Plan> current = std::vector<Plan>());
    double variance(Plan plan);
};


#endif //TOPOLOGICALSORT_DAG_H
