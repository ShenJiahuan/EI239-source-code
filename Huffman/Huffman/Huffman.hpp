//
//  Huffman.hpp
//  Huffman
//
//  Created by 沈嘉欢 on 2018/10/12.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#ifndef Huffman_hpp
#define Huffman_hpp

#include <queue>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "Tree.hpp"

class Huffman {
private:
    Tree huffmanTree;
    bool initialized = false;
    std::map<char, Tree*> T_ptr;
    void traverse(Tree* root);
    static std::function<bool(Tree, Tree)> compare;
public:
    Huffman() = default;
    Huffman(std::vector<char> value, std::vector<double> weight);
    Huffman& operator=(const Huffman& other);
    std::string encode(std::string inputFile, std::string outputFile);
    std::string decode(std::string code, std::string filename);
    std::string display();
};

std::function<bool(Tree, Tree)> Huffman::compare = [](Tree a, Tree b) {return a.get_weight() > b.get_weight();};

Huffman::Huffman(std::vector<char> value, std::vector<double> weight) {
    assert(value.size() == weight.size());
    std::priority_queue<Tree, std::vector<Tree>, decltype(compare)> forest(compare);
    for (size_t i = 0; i < value.size(); ++i) {
        forest.push(Tree(value[i], weight[i]));
    }
    while (forest.size() > 1) {
        Tree a = forest.top();
        forest.pop();
        Tree b = forest.top();
        forest.pop();
        Tree parent(a, b);
        a.set_parent(parent);
        b.set_parent(parent);
        forest.push(parent);
    }
    huffmanTree = forest.top();
    traverse(&huffmanTree);
    initialized = true;
}

Huffman& Huffman::operator=(const Huffman& other) {
    huffmanTree = other.huffmanTree;
    traverse(&huffmanTree);
    initialized = true;
    return *this;
}

void Huffman::traverse(Tree* root) {
    if (!root) {
        return;
    }
    if (!root->lchild && !root->rchild) {
        T_ptr[root->data] = root;
    }
    if (root->lchild) {
        traverse(root->lchild);
    }
    if (root->rchild) {
        traverse(root->rchild);
    }
}

std::string Huffman::encode(std::string inputFile, std::string outputFile) {
    assert(initialized);
    std::ifstream in(inputFile, std::ios::in);
    std::string encoded = "";
    char ch;
    while (in >> ch) {
        assert(T_ptr.find(ch) != T_ptr.end());
        std::string tmp;
        Tree *last = T_ptr[ch];
        while (last->parent) {
            Tree *parent = last->parent;
            if (parent->lchild == last) {
                tmp = "0" + tmp;
            } else {
                tmp = "1" + tmp;
            }
            last = parent;
        }
        encoded += tmp;
    }
    in.close();
    std::ofstream out(outputFile, std::ios::out);
    out << encoded;
    out.close();
    return encoded;
}

std::string Huffman::decode(std::string inputFile, std::string outputFile) {
    assert(initialized);
    std::ifstream in(inputFile, std::ios::in);
    std::string code;
    in >> code;
    in.close();
    size_t pos = 0;
    std::string decoded;
    while (pos < code.length()) {
        Tree *p = &huffmanTree;
        while (p->lchild && p->rchild) {
            bool right = code[pos] == '0'? false: true;
            if (right) {
                p = p->rchild;
            } else {
                p = p->lchild;
            }
            pos++;
        }
        decoded += p->data;
    }
    std::ofstream out(outputFile, std::ios::out);
    for (auto ch: decoded) {
        out << ch;
    }
    out.close();
    return decoded;
}

std::string Huffman::display() {
    assert(initialized);
    std::string disp;
    std::vector<std::vector<char>> text;
    std::queue<std::pair<Tree*, std::vector<bool>>> q;
    q.push(std::make_pair(&huffmanTree, std::vector<bool>()));
    while (!q.empty()) {
        Tree *tree = q.front().first;
        std::vector<bool> path = q.front().second;
        q.pop();
        char ch = tree->data != '\0' ? tree->data : '*';
        int cnt = 0;
        int i = 0;
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cnt += *it * (1 << i);
            ++i;
        }
        if (path.size() >= text.size()) {
            text.push_back(std::vector<char>((1 << path.size()), '^'));
        }
        text[path.size()][cnt] = ch;
        if (tree->lchild) {
            std::vector<bool> tmp = path;
            tmp.push_back(false);
            q.push(std::make_pair(tree->lchild, tmp));
        }
        if (tree->rchild) {
            std::vector<bool> tmp = path;
            tmp.push_back(true);
            q.push(std::make_pair(tree->rchild, tmp));
        }
    }
    for (auto line : text) {
        for (auto ch : line) {
            disp += ch;
        }
        disp += '\n';
    }
    return disp;
}

#endif /* Huffman_hpp */
