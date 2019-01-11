#include <iostream>
#include <fstream>
#include <algorithm>
#include "DAG.h"
#include "util/util.h"

int main() {
    std::vector<Lesson> lessons;
    int semesterCount;
    int maxCredit;
    bool preferAverage;
    std::tie(lessons, semesterCount, maxCredit, preferAverage) = input();
    DAG graph(lessons, maxCredit, semesterCount);
    auto ans = getPlan(graph, semesterCount);
    std::vector<std::pair<Plan, double>> variance;
    for (auto plan : ans) {
        variance.emplace_back(std::make_pair(plan, graph.variance(plan)));
    }
    if (ans.empty()) {
        std::cout << "No solution!\n";
        return 0;
    }
    if (preferAverage) {
        std::sort(variance.begin(), variance.end(), [](std::pair<Plan, double> lhs, std::pair<Plan, double> rhs) {return lhs.second < rhs.second; });
    }
    else {
        std::sort(variance.begin(), variance.end(), [](std::pair<Plan, double> lhs, std::pair<Plan, double> rhs) {return lhs.second > rhs.second; });
    }
    std::ofstream out("data.txt", std::ios::out);
    for (const auto &item : variance) {
        Plan plan = item.first;
        for (size_t i = 0; i < plan.size(); ++i) {
            out << i + 1 << ": ";
            for (const auto &lesson : plan[i]) {
                out << lesson << " ";
            }
            out << std::endl;
        }
        out << std::endl;
    }
    return 0;
}