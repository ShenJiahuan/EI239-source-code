//
// Created by 沈嘉欢 on 2018-12-23.
//


#include "util.h"

std::set<Plan> getPlan(DAG &graph, size_t semesterCount) {
    std::vector<Sequence> sequences;
    sequences = graph.topSort();
    std::set<Plan> ans;
    for (const auto &sequence : sequences) {
        auto result = graph.parse(sequence, true, std::vector<Plan>());
        if (!result.empty()) {
            for (auto plan : result) {
                while (plan.size() < semesterCount) {
                    plan.emplace_back(std::set<std::string>());
                }
                ans.insert(plan);
            }
        }
    }
    return ans;
}

std::tuple<std::vector<Lesson>, int, int, bool> input() {
    int semesterCount;
    int maxCredit;
    std::vector<Lesson> lessons;
    bool preferAverage;
    std::cout << "Input number of semesters: ";
    std::cin >> semesterCount;
    std::cout << "Input max credits for each semester: ";
    std::cin >> maxCredit;
    int n;
    std::cout << "Input number of lessons: ";
    std::cin >> n;
    std::cout << "Input lesson details: \n";
    for (int i = 0; i < n; ++i) {
        std::string id;
        int credit;
        int m;
        std::vector<std::string> pre;
        std::cin >> id >> credit;
        std::cin >> m;
        for (int j = 0; j < m; ++j) {
            std::string pre_id;
            std::cin >> pre_id;
            pre.push_back(pre_id);
        }
        lessons.push_back({ id, credit, pre });
    }
    std::cout << "Prefer average in load? (y/n)";
    char choice;
    std::cin >> choice;
    preferAverage = choice == 'y';
    return std::make_tuple(lessons, semesterCount, maxCredit, preferAverage);
}