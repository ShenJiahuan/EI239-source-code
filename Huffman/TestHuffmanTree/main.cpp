//
//  main.cpp
//  TestHuffmanTree
//
//  Created by 沈嘉欢 on 2018/10/12.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include <vector>
#include "../Huffman/HuffmanTree.hpp"
#include "../Huffman/Huffman.hpp"


int main(int argc, const char * argv[]) {
    std::vector<HuffmanTree<int>> forest;
    for (int i = 0; i < 4; ++i) {
        HuffmanTree<int> tmp = HuffmanTree<int>(i, i);
        forest.push_back(tmp);
    }
    while (forest.size() != 1) {
        std::vector<HuffmanTree<int>> tmp;
        while (!forest.empty()) {
            HuffmanTree<int> left = forest.back();
            forest.pop_back();
            HuffmanTree<int> right = forest.back();
            forest.pop_back();
            tmp.push_back(HuffmanTree<int>(left, right));
        }
        forest = tmp;
    }
    return 0;
}
