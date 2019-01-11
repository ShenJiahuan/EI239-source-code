//
//  main.cpp
//  MultiKeySort
//
//  Created by 沈嘉欢 on 2018/12/8.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "Sort.h"
#include "Student.h"

inline bool compare(const Student &a, const Student &b, std::vector<std::pair<std::string, int>> power) {
    int diff = a.sum() - b.sum();
    if (diff < 0) {
        return false;
    } else if (diff > 0) {
        return true;
    }
    for (auto it = power.cbegin() + 1; it != power.cend(); ++it) {
        diff = a.score.at(it->first) - b.score.at(it->first);
        if (diff < 0) {
            return false;
        } else if (diff > 0) {
            return true;
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    std::vector<Student> stu(10000);
    std::vector<std::pair<std::string, int>> power = {{"Sum", INT_MAX}, {"Chinese", 0}, {"Math", 0}, {"English", 0},
                                                      {"Physics", 0}, {"Chemistry", 0}, {"Biology", 0}};
    std::cout << "Input 6 integers to give power of each lesson.\n";
    for (auto it = power.begin() + 1; it != power.end(); ++it) {
        std::cout << it->first << ": ";
        std::cin >> it->second;
    }
    sort::quickSort(power.begin(), power.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {return a.second > b.second;});
    sort::quickSort(stu.begin(), stu.end(), [power](const Student &a, const Student &b) {return compare(a, b, power);});
    int i = 1;
    for (auto item : stu) {
        std::cout << "Rank: " << std::setw(5) << i++ <<" ID: " << std::setw(4) << item.number << " Sum: "<< std::setw(3)  << item.sum() << " ";
        for (auto course = power.cbegin() + 1; course != power.cend(); ++course) {
            std::cout << course->first << ": "<< std::setw(3) << item.score[course->first] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
