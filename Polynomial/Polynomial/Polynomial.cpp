//
//  Polynomial.cpp
//  Polynomial
//
//  Created by 沈嘉欢 on 2018/10/10.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include "Polynomial.hpp"

struct Polynomial::Node {
    Node(): next(nullptr) {};
    Node(double value, int index, Node* next = nullptr): value(value), index(index), next(next) {};
    ~Node() {
        if (next) {
            delete next;
        }
    }
    double value;
    int index;
    Node* next;
};

void Polynomial::simplify() {
    Node* p = head;
    while (p->next) {
        if (equal(p->next->value, 0)) {
            Node* tmp = p->next;
            p->next = p->next->next;
            tmp->next = nullptr;
            delete tmp;
        } else {
            p = p->next;
        }
    }
    if (!head->next) {
        head->next = new Node(0, 0);
    }
}

bool Polynomial::equal(double a, double b) {
    return (a - b) < epsilon && (b - a) < epsilon;
}

void Polynomial::copy(Polynomial& lhs, const Polynomial& rhs) {
    lhs.head = new Node();
    Node *p = lhs.head, *q = rhs.head->next;
    while (q) {
        p->next = new Node(q->value, q->index);
        p = p->next;
        q = q->next;
    }
}

Polynomial::Polynomial() {
    head = new Node();
    head->next = new Node(0, 0);
}

Polynomial::Polynomial(const Polynomial& poly) {
    copy(*this, poly);
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    if (this == &rhs) {
        return *this;
    }
    if (head) {
        delete head;
    }
    copy(*this, rhs);
    return *this;
}

Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial ans;
    Polynomial::Node *p = ans.head, *q1 = lhs.head->next, *q2 = rhs.head->next;
    while (q1 && q2) {
        if (q1->index == q2->index) {
            p->next = new Polynomial::Node(q1->value + q2->value, q1->index);
            q1 = q1->next;
            q2 = q2->next;
        } else if (q1->index > q2->index) {
            p->next = new Polynomial::Node(q1->value, q1->index);
            q1 = q1->next;
        } else {
            p->next = new Polynomial::Node(q2->value, q2->index);
            q2 = q2->next;
        }
        p = p->next;
    }
    while (q1) {
        p->next = new Polynomial::Node(q1->value, q1->index);
        q1 = q1->next;
        p = p->next;
    }
    while (q2) {
        p->next = new Polynomial::Node(q2->value, q2->index);
        q2 = q2->next;
        p = p->next;
    }
    ans.simplify();
    return ans;
}

Polynomial operator-(const Polynomial& poly) {
    Polynomial ans;
    Polynomial::Node *p = ans.head, *q = poly.head->next;
    while (q) {
        p->next = new Polynomial::Node(-q->value, q->index);
        p = p->next;
        q = q->next;
    }
    return ans;
}

Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) {
    return lhs + (-rhs);
}

Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial ans;
    Polynomial::Node *q1 = lhs.head->next;
    while (q1) {
        Polynomial tmp;
        tmp.head = new Polynomial::Node();
        Polynomial::Node *p = tmp.head, *q2 = rhs.head->next;
        while (q2) {
            p->next = new Polynomial::Node(q1->value * q2->value, q1->index + q2->index);
            p = p->next;
            q2 = q2->next;
        }
        ans += tmp;
        q1 = q1->next;
    }
    ans.simplify();
    return ans;
}

Polynomial &Polynomial::operator+=(const Polynomial& rhs) {
    Polynomial tmp = *this + rhs;
    *this = tmp;
    return *this;
}

Polynomial &Polynomial::operator-=(const Polynomial& rhs) {
    Polynomial tmp = *this - rhs;
    *this = tmp;
    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial& rhs) {
    Polynomial tmp = *this * rhs;
    *this = tmp;
    return *this;
}

Polynomial Polynomial::derivative() {
    Polynomial ans;
    Node *p = ans.head, *q = head->next;
    while (q) {
        p->next = new Node(q->index * q->value, q->index - 1);
        p = p->next;
        q = q->next;
    }
    ans.simplify();
    return ans;
}

std::istream& operator>>(std::istream& in, Polynomial& poly) {
    if (poly.head) {
        delete poly.head;
    }
    size_t n;
    in >> n;
    poly.head = new Polynomial::Node();
    for (auto i = 0; i < n; ++i) {
        Polynomial::Node* p = poly.head;
        double value;
        int index;
        in >> value >> index;
        while (p->next && p->next->index > index) {
            p = p->next;
        }
        if (p->next && p->next->index == index) {
            p->next->value += value;
        } else {
            Polynomial::Node* tmp = new Polynomial::Node(value, index);
            tmp->next = p->next;
            p->next = tmp;
        }
    }
    poly.simplify();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& poly) {
    Polynomial::Node* p = poly.head->next;
    bool first = true;
    assert(p);
    while (p) {
        if (!first && p->value > 0) {
            out << "+";
        }
        if (Polynomial::equal(p->value, -1) && p->index != 0) {
            out << "-";
        } else if (!Polynomial::equal(p->value, 1) || p->index == 0) {
            out << p->value;
        }
        if (p->index != 0) {
            out << "x";
            if (p->index != 1) {
                out << "^";
                if (p->index < 0) {
                    out << "(" << p->index << ")";
                } else {
                    out << p->index;
                }
            }
        }
        first = false;
        p = p->next;
    }
    return out;
}
