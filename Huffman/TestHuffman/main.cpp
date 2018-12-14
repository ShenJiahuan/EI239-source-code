//
//  main.cpp
//  TestHuffman
//
//  Created by 沈嘉欢 on 2018/10/12.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include <vector>
#include "../Huffman/Huffman.hpp"

int main(int argc, const char * argv[]) {
    //std::vector<char> dict = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    //std::vector<double> weight = {186, 64, 13, 22, 32, 103, 21, 17, 47, 57, 1, 5, 33, 20, 57, 63, 15, 1, 49, 51, 80, 23, 8, 19, 1, 16, 1};
    std::vector<char> dict = {'A', 'B', 'C'};
    std::vector<double> weight = {10, 5, 100};
    Huffman h(dict, weight);
    std::string raw = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string encoded = h.encode("/Users/shenjiahuan/Desktop/数据结构与算法/Huffman/Huffman/plainFile", "codeFile");
    //for (auto ch : raw) {
    //    encoded += h.encode(ch, "codeFile");
    //}
    std::cout << encoded << std::endl;
    std::vector<char> decoded = h.decode(encoded, "textFile");
    for (auto ch : decoded) {
        std::cout << ch;
    }
    std::cout << std::endl;
    h.display();
    return 0;
}
