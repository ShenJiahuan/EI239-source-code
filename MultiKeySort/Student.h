//
// Created by 沈嘉欢 on 2018/12/9.
//

#ifndef MULTIKEYSORT_STUDENT_H
#define MULTIKEYSORT_STUDENT_H

#include <random>
#include <map>
#include <string>

std::random_device rd;
std::mt19937 gen = std::mt19937(rd());
auto dis = std::uniform_int_distribution<>(0, 100);

struct Student {
    static int tot_num;
    int number;
    std::map<std::string, int> score;
    Student() {
        number = tot_num;
        score["Chinese"] = dis(gen);
        score["Math"] = dis(gen);
        score["English"] = dis(gen);
        score["Physics"] = dis(gen);
        score["Chemistry"] = dis(gen);
        score["Biology"] = dis(gen);
        tot_num++;
    }
    int sum() const {
        int ans = 0;
        for (auto item : score) {
            ans += item.second;
        }
        return ans;
    }
};

int Student::tot_num = 0;

#endif //MULTIKEYSORT_STUDENT_H
