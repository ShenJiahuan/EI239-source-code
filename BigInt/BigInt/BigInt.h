//
//  BigInt.h
//  BigInt
//
//  Created by 沈嘉欢 on 2018/9/21.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#ifndef BigInt_h
#define BigInt_h

#include <iostream>

class BigInt {
private:
    struct LinkedList {
        int data;
        LinkedList *front;
        LinkedList *next;
        LinkedList(int num=0, LinkedList *front=nullptr): data(num), front(front), next(nullptr) {};
        ~LinkedList() {
            delete next;
        }
    };
    LinkedList *header, *rear;
    int length;
    static BigInt abs(const BigInt &);
    void simplify();
    friend void copy(BigInt &, const std::string &);
    friend void copy(BigInt &, const BigInt &);
    friend void copy(BigInt &, long long);
public:
    BigInt();
    BigInt(const std::string &);
    BigInt(const BigInt &);
    BigInt(long long);
    ~BigInt() {
        delete header;
    }
    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend BigInt operator/(const BigInt &, const BigInt &);
    BigInt &operator=(const std::string &);
    BigInt &operator=(const BigInt &);
    BigInt &operator=(long long);
    BigInt &operator+=(const BigInt &);
    BigInt &operator-=(const BigInt &);
    BigInt &operator*=(const BigInt &);
    BigInt &operator/=(const BigInt &);
    BigInt &operator++();
    BigInt operator++(int);
    BigInt &operator--();
    BigInt operator--(int);
    friend BigInt power(const BigInt &, const BigInt &);
    friend BigInt factorial(const BigInt &);
    friend std::istream &operator>>(std::istream &, BigInt &);
    friend std::ostream &operator<<(std::ostream &, const BigInt &);
};

#endif /* BigInt_h */
