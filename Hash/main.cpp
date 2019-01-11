//
// Created by 沈嘉欢 on 2018/12/11.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include "HashTable.h"

int main() {
    auto func0 = [](const std::string& str, size_t size) {
        size_t result = 0;
        for (int i = 0; i < str.length(); i += 3) {
            result += str[i];
        }
        return result * 1007 % size;
    };

    auto func1 = [](const std::string& str, size_t size) {
        size_t result = 0;
        for (int i = 0; i < str.length(); ++i) {
            result += str[i] * (i + 1);
        }
        return result % size;
    };
    auto func2 = [](const std::string& str, size_t size) {
        size_t result = 0;
        for (const auto ch : str) {
            result += ch;
        }
        return result * str.length() % size;
    };
    auto func3 = [](const std::string& str, size_t size) {
        size_t result = 0;
        for (const auto ch : str) {
            result += ch;
        }
        return result % size;
    };

    std::vector<std::pair<std::string, int>> data = {
        {"Ma Yun", 2700}, {"Xu Jiayin", 2500}, {"Ma Huateng", 2400},
        {"Yang Huiyan", 1500}, {"Wang Jianlin", 1400}, {"He Xiangjian", 1300},
        {"Wang Wei", 1200}, {"Yan Hao", 1200}, {"Li Yanhong", 1150},
        {"Lei Jun", 1100}, {"Wang Wenyin", 1100}, {"Yao Zhenhua", 1100},
        {"Huang Zheng", 950}, {"Zhang Jindong", 950}, {"Zhang Zhidong", 950},
        {"Ding Lei", 900}, {"Li Shufu", 900}, {"Zong Qinghou", 900},
        {"Xu Rongmao", 850}, {"Sun Piaoyang", 825}, {"Lu Zhiqiong", 800},
        {"Chen Jianhua", 790}, {"Yan Bin", 780}, {"Liu Qiangdong", 750},
        {"Lin Li", 670}, {"Xu Shihui", 650}, {"Zhang Shiping", 650},
        {"Zhang Yiming", 650}, {"Liu Yongxing", 630}, {"Wang Yusuo", 620}
    };
    std::map<std::string, std::function<int(const std::string &, size_t)>> funcList = {{"Func0", func0}, {"Func1", func1}, {"Func2", func2}, {"Func3", func3}};
    for (auto func : funcList) {
        std::cout << func.first  << " LinearProbingHashTable: "<< std::endl;
        LinearProbingHashTable<std::string, int> table1(func.second);
        for (const auto person : data) {
            table1[person.first] = person.second;
        }
        for (const auto person : data) {
            assert(person.second == table1[person.first]);
        }
        std::cout << table1.collideRate() << " " << table1.averageSearchLength() << std::endl;
        std::cout << func.first  << " QuadraticProbingHashTable: "<< std::endl;
        QuadraticProbingHashTable<std::string, int> table2(func.second);
        for (const auto person : data) {
            table2[person.first] = person.second;
        }
        for (const auto person : data) {
            assert(person.second == table2[person.first]);
        }
        std::cout << table2.collideRate() << " " << table2.averageSearchLength() << std::endl;
    }

    return 0;
}