//
//  main.cpp
//  Huffman
//
//  Created by 沈嘉欢 on 2018/10/12.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include "Huffman.hpp"

void hint();

int main(int argc, const char * argv[]) {
    char option;
    Huffman hfmTree;
    while (true) {
        hint();
        std::cin >> option;
        switch (option) {
            case 'I':
                {
                    size_t n;
                    std::cin >> n;
                    std::vector<char> dict(n);
                    std::vector<double> weight(n);
                    for (size_t i = 0; i < n; ++i) {
                        std::cin >> dict[i];
                        std::cin >> weight[i];
                    }
                    hfmTree = Huffman(dict, weight);
                    break;
                }
            case 'E':
                {
                    hfmTree.encode("/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/plainFile", "/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/codeFile");
                    break;
                }
            case 'D':
                {
                    hfmTree.decode("/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/codeFile", "/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/textFile");
                    break;
                }
            case 'P':
                {
                    std::string encoded = hfmTree.encode("/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/plainFile", "/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/codeFile");
                    std::ofstream out("/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/codePrint", std::ios::out);
                    int cnt = 0;
                    for (auto ch : encoded) {
                        std::cout << ch;
                        out << ch;
                        cnt++;
                        if (cnt % 50 == 0) {
                            std::cout << '\n';
                            out << '\n';
                        }
                    }
                    std::cout << '\n';
                    out << '\n';
                    out.close();
                    break;
                }
            case 'T':
                {
                    std::string result = hfmTree.display();
                    std::cout << result;
                    std::ofstream out("/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/treePrint", std::ios::out);
                    out << result;
                    out.close();
                    break;
                }
            case 'R':
                {
                    std::string line;
                    std::cin.get();
                    std::getline(std::cin, line);
                    std::map<char, int> count;
                    for (auto ch : line) {
                        count[ch]++;
                    }
                    std::vector<char> value;
                    std::vector<double> weight;
                    std::for_each(count.begin(), count.end(), [&](std::pair<char, int> item) {
                        value.push_back(item.first);
                        weight.push_back(item.second);
                    });
                    hfmTree = Huffman(value, weight);
                    std::ofstream out("/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/plainFile", std::ios::out);
                    out << line;
                    out.close();
                    hfmTree.encode("/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/plainFile", "/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/codeFile");
                    hfmTree.decode("/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/codeFile", "/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/textFile");
                    break;
                }
            case 'Q':
                {
                    return 0;
                }
            default:
                break;
        }
    }
    return 0;
}

void hint() {
    std::cout << "Choose from I, E, D, P, T, Q:\n";
    std::cout << "I: Initialize;\n";
    std::cout << "E: Encode;\n";
    std::cout << "D: Decode;\n";
    std::cout << "P: Print code;\n";
    std::cout << "T: Print tree;\n";
    std::cout << "R: Create tree from random string;\n";
    std::cout << "Q: Quit.\n";
}
