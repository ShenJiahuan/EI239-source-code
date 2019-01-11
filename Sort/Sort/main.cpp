//
//  main.cpp
//  Sort
//
//  Created by 沈嘉欢 on 2018/12/2.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <map>
#include "Sort.h"

inline void display(std::string type, int comparison, int move) {
    std::cout << type << ": " << "cmp " << comparison << ", " << "move " << move << ".\n";
}

template <class Iterator, class Compare>
void judge(std::tuple<int, int> (*sort)(Iterator begin, Iterator end, const Compare &cmp),
           std::string type, Iterator begin, Iterator end, const Compare &cmp) {
    std::vector<std::decay_t<decltype(*begin)>> data(begin, end);
    int comparison, move;
    std::tie(comparison, move) = sort(data.begin(), data.end(), cmp);
    display(type, comparison, move);
}

template <class Iterator>
void judge(std::tuple<int, int> (*sort)(Iterator begin, Iterator end),
           std::string type, Iterator begin, Iterator end) {
    std::vector<std::decay_t<decltype(*begin)>> data(begin, end);
    int comparison, move;
    std::tie(comparison, move) = sort(data.begin(), data.end());
    display(type, comparison, move);
}

int main(int argc, const char * argv[]) {
    struct test {
        int first;
        int second;
    };
    int n = 1000;
    std::map<std::string, std::vector<int>> data_group;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, n * 10);
    for (int i = 1; i <= 5; ++i) {
        std::vector<int> data(n);
        std::for_each(data.begin(), data.end(), [&dis, &gen](int &num) {return num = dis(gen);});
        data_group["Random " + std::to_string(i)] = data;
    }
    int i = 0;
    std::vector<int> sorted(n), reversed(n);
    std::for_each(sorted.begin(), sorted.end(), [&i](int &num) {return num = ++i;});
    std::for_each(reversed.begin(), reversed.end(), [&i](int &num) {return num = i--;});
    data_group["Sorted"] = sorted;
    data_group["Reversed"] = reversed;
    auto cmp = [](int a, int b) {return a < b;};
    for (auto item : data_group) {
        std::string type = item.first;
        auto data = item.second;
        std::cout << type << ":" << std::endl;
        judge(sort::bubbleSort, "Bubble sort", data.begin(), data.end(), cmp);
        judge(sort::directInsertionSort, "Direct insertion sort", data.begin(), data.end(), cmp);
        judge(sort::selectionSort, "Selection sort", data.begin(), data.end(), cmp);
        judge(sort::quickSort, "Quick sort", data.begin(), data.end(), cmp);
        judge(sort::shellSort, "Shell sort", data.begin(), data.end(), cmp);
        judge(sort::heapSort, "Heap sort", data.begin(), data.end(), cmp);
        judge(sort::binaryInsertionSort, "Binary insertion sort", data.begin(), data.end(), cmp);
        judge(sort::mergeSort, "Merge sort", data.begin(), data.end(), cmp);
    }
    return 0;
}
