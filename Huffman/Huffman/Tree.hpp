//
//  Tree.hpp
//  Huffman
//
//  Created by 沈嘉欢 on 2018/10/12.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp

#include <memory>
#include <vector>

class Tree {
private:
    char data;
    double weight;
    Tree *lchild, *rchild, *parent;
public:
    Tree(): lchild(nullptr), rchild(nullptr), parent(nullptr) {};
    Tree(char data, double weight): data(data), weight(weight), lchild(nullptr), rchild(nullptr), parent(nullptr) {};
    ~Tree() {
        if (lchild) {
            delete lchild;
        }
        if (rchild) {
            delete rchild;
        }
    }
    Tree(const Tree& rhs);
    Tree &operator=(const Tree& rhs);
    friend void copy(Tree &lhs, const Tree &rhs) {
        lhs.data = rhs.data;
        lhs.weight = rhs.weight;
        if (rhs.lchild) {
            lhs.lchild = new Tree(*rhs.lchild);
            lhs.lchild->parent = &lhs;
        }
        if (rhs.rchild) {
            lhs.rchild = new Tree(*rhs.rchild);
            lhs.rchild->parent = &lhs;
        }
    }
    Tree(Tree& lchild, Tree& rchild, char data = '\0'):
    data(data), parent(nullptr) {
        this->lchild = new Tree(lchild);
        this->rchild = new Tree(rchild);
        this->weight = lchild.weight + rchild.weight;
    };
    void set_parent(Tree& parent) {
        this->parent = &parent;
    }
    double get_weight() const {
        return weight;
    }
    friend class Huffman;
};

Tree::Tree(const Tree& rhs) {
    this->lchild = this->rchild = this->parent = nullptr;
    copy(*this, rhs);
}

Tree &Tree::operator=(const Tree& rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete this->lchild;
    delete this->rchild;
    this->lchild = this->rchild = this->parent = nullptr;
    copy(*this, rhs);
    return *this;
}


#endif /* Tree_hpp */
