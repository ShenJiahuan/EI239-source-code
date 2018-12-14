//
//  Polynomial.hpp
//  Polynomial
//
//  Created by 沈嘉欢 on 2018/10/10.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include <iostream>

class Polynomial {
private:
    struct Node;
    void simplify();
    static const constexpr double epsilon = 1e-6;
    static bool equal(double a, double b);
    static void copy(Polynomial& lhs, const Polynomial& rhs);
    Node* head;
public:
    Polynomial();
    Polynomial(const Polynomial& poly);
    Polynomial& operator=(const Polynomial& rhs);
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial operator-(const Polynomial& poly);
    friend Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs);
    Polynomial &operator+=(const Polynomial& rhs);
    Polynomial &operator-=(const Polynomial& rhs);
    Polynomial &operator*=(const Polynomial& rhs);
    Polynomial derivative();
    friend std::istream& operator>>(std::istream& in, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& out, const Polynomial& poly);
};

#endif /* Polynomial_hpp */
