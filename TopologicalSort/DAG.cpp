//
// Created by 沈嘉欢 on 2018-12-18.
//

#include "DAG.h"

std::vector<Sequence> DAG::topSort() {
    Sequence path;
    std::set<std::string> notVisited;
    for (const auto &item : graph) {
        auto lesson = item.first;
        notVisited.insert(lesson);
    }
    return topSort(path, notVisited);
}

std::vector<Sequence> DAG::topSort(Sequence &path, std::set<std::string> &notVisited) {
    std::vector<Sequence> result;
    if (link == 0 && path.size() == size) {
        result.push_back(path);
        return result;
    }
    auto beforeNotVisited = notVisited;
    for (const auto &lesson : beforeNotVisited) {
        std::set<std::string> out;
        out = graph[lesson];
        if (inDegree[lesson] == 0) {
            auto outDegree = out.size();
            graph[lesson] = std::set<std::string>();
            path.push_back(lesson);
            notVisited.erase(lesson);
            link -= outDegree;
            for (const auto &nextLesson : out) {
                --inDegree[nextLesson];
            }
            std::vector<Sequence> newPath;
            newPath = topSort(path, notVisited);
            result.insert(result.end(), newPath.begin(), newPath.end());
            path.pop_back();
            notVisited.insert(lesson);
            link += outDegree;
            for (const auto &nextLesson : out) {
                ++inDegree[nextLesson];
            }
            graph[lesson] = out;
        }
    }
    return result;
}

DAG::DAG(std::vector<Lesson> lessons, int maxCredit, size_t semesterCount) {
    this->maxCredit = maxCredit;
    this->semesterCount = semesterCount;
    this->link = 0;
    double tot_credits = 0;
    for (const auto &lesson : lessons) {
        graph[lesson.id] = std::set<std::string>();
        credits[lesson.id] = lesson.credit;
        tot_credits += lesson.credit;
    }
    for (const auto &lesson1 : lessons) {
        inDegree[lesson1.id] = lesson1.pre.size();
        for (const auto &pre : lesson1.pre) {
            graph[pre].insert(lesson1.id);
            this->link++;
        }
    }
    size = lessons.size();
    mean = tot_credits / credits.size();
}

std::vector<Plan> DAG::parse(Sequence seq, bool init, std::vector<Plan> current) {
    if (seq.empty()) {
        return current;
    }
    if (current.empty() && init) {
        std::vector<Plan> result;
        result.push_back({ { seq[0] } });
        seq.pop_front();
        return parse(seq, false, result);
    }
    std::vector<Plan> result;
    for (const auto &plan : current) {
        bool append = true;
        if (plan.empty()) {
            append = false;
        }
        else {
            int credit = 0;
            for (const auto &lesson : plan.back()) {
                if (graph[lesson].count(seq[0])) {
                    append = false;
                }
                credit += credits[lesson];
            }
            credit += credits[seq[0]];
            if (credit > maxCredit) {
                append = false;
            }
        }
        if (append) {
            auto newPlan = plan;
            newPlan.back().insert(seq[0]);
            result.push_back(newPlan);
        }
        if (plan.size() < semesterCount) {
            auto newPlan = plan;
            newPlan.push_back({ seq[0] });
            result.push_back(newPlan);
        }
    }
    seq.pop_front();
    return parse(seq, false, result);
}

double DAG::variance(Plan plan) {
    double ans = 0;
    for (const auto &semester : plan) {
        int credit = 0;
        for (const auto &lesson : semester) {
            credit += credits[lesson];
        }
        ans += (credit - mean) * (credit - mean);
    }
    return ans / semesterCount;
}