//
//  main.cpp
//  TestTree
//
//  Created by 沈嘉欢 on 2018/10/12.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include <vector>
#include "../Huffman/Tree.hpp"
#include "../Huffman/Huffman.hpp"


int main(int argc, const char * argv[]) {
    std::vector<Tree<int>> forest;
    for (int i = 0; i < 4; ++i) {
        Tree<int> tmp = Tree<int>(i, i);
        forest.push_back(tmp);
    }
    while (forest.size() != 1) {
        std::vector<Tree<int>> tmp;
        while (!forest.empty()) {
            Tree<int> left = forest.back();
            forest.pop_back();
            Tree<int> right = forest.back();
            forest.pop_back();
            tmp.push_back(Tree<int>(left, right));
        }
        forest = tmp;
    }
    return 0;
}
