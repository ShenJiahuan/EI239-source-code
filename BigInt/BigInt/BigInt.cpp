//
//  BigInt.cpp
//  BigInt
//
//  Created by 沈嘉欢 on 2018/9/21.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include <string>
#include <climits>
#include "BigInt.h"

BigInt::BigInt() {
    header = new LinkedList();
    rear = header;
    length = 0;
}

BigInt::BigInt(const std::string &num) {
    assert(num.length() != 0);
    copy(*this, num);
}

BigInt::BigInt(const BigInt &num) {
    copy(*this, num);
}

BigInt::BigInt(long long num) {
    assert(num != LLONG_MIN);
    copy(*this, num);
}

BigInt &BigInt::operator=(const std::string &num) {
    assert(num.length() != 0);
    delete this->header;
    copy(*this, num);
    return *this;
}

BigInt &BigInt::operator=(const BigInt &num) {
    if (this == &num) {
        return *this;
    }
    delete this->header;
    copy(*this, num);
    return *this;
}

BigInt &BigInt::operator=(long long num) {
    assert(num != LLONG_MIN);
    delete this->header;
    copy(*this, num);
    return *this;
}

bool operator>(const BigInt &first, const BigInt &second) {
    if (first.header->data == 0 && second.header->data == 1) {
        return true;
    } else if (first.header->data == 1 && second.header->data == 0) {
        return false;
    }
    if (first.length != second.length) {
        if (first.header->data == 0) {
            return first.length > second.length;
        } else {
            return first.length < second.length;
        }
    }
    BigInt::LinkedList *p1 = first.rear, *p2 = second.rear;
    while (p1 != first.header && p2 != second.header) {
        if (p1->data != p2->data) {
            if (first.header->data == 0) {
                return p1->data > p2->data;
            } else {
                return p1->data < p2->data;
            }
        }
        p1 = p1->front;
        p2 = p2->front;
    }
    return false;
}

bool operator<(const BigInt &first, const BigInt &second){
    return !(first >= second);
}


bool operator==(const BigInt &first, const BigInt &second) {
    if (first.length != second.length) {
        return false;
    }
    if (first.header->data != second.header->data) {
        return false;
    }
    BigInt::LinkedList *p1 = first.rear, *p2 = second.rear;
    while (p1 != first.header && p2 != second.header) {
        if (p1->data != p2->data) {
            return false;
        }
        p1 = p1->front;
        p2 = p2->front;
    }
    return true;
}

bool operator!=(const BigInt &first, const BigInt &second) {
    return !(first == second);
}

bool operator>=(const BigInt &first, const BigInt &second) {
    return first > second || first == second;
}

bool operator<=(const BigInt &first, const BigInt &second) {
    return first < second || first == second;
}

BigInt BigInt::abs(const BigInt &num) {
    BigInt ans = num;
    ans.header->data = 0;
    return ans;
}

BigInt operator+(const BigInt &first, const BigInt &second) {
    BigInt ans;
    if (first.header->data == second.header->data) {
        ans.header->data = first.header->data;
    } else {
        if (first.header->data == 1) {
            return second - -first;
        } else {
            return first - -second;
        }
    }
    BigInt::LinkedList *p = first.header, *q = second.header, *r = ans.header;
    while (p->next && q->next) {
        r->next = new BigInt::LinkedList(p->next->data + q->next->data, r);
        ans.rear = r->next;
        p = p->next;
        q = q->next;
        r = r->next;
        ++ans.length;
    }
    while (p->next) {
        r->next = new BigInt::LinkedList(p->next->data, r);
        ans.rear = r->next;
        p = p->next;
        r = r->next;
        ++ans.length;
    }
    while (q->next) {
        r->next = new BigInt::LinkedList(q->next->data, r);
        ans.rear = r->next;
        q = q->next;
        r = r->next;
        ++ans.length;
    }
    ans.simplify();
    return ans;
}

BigInt operator-(const BigInt &num) {
    BigInt ans = num;
    if (!(ans.length == 1 && ans.header->next->data == 0)) {
        ans.header->data = 1 - ans.header->data;
    }
    return ans;
}

BigInt operator-(const BigInt &first, const BigInt &second) {
    if (first.header->data == 1) {
        return -(-first + second);
    }
    if (second.header->data == 1) {
        return first + (-second);
    }
    if (first < second) {
        return -(second - first);
    }
    BigInt ans;
    ans.header->data = 0;
    BigInt::LinkedList *p = first.header, *q = second.header, *r = ans.header;
    while (p->next && q->next) {
        r->next = new BigInt::LinkedList(p->next->data - q->next->data, r);
        ans.rear = r->next;
        p = p->next;
        q = q->next;
        r = r->next;
        ++ans.length;
    }
    while (p->next) {
        r->next = new BigInt::LinkedList(p->next->data, r);
        ans.rear = r->next;
        p = p->next;
        r = r->next;
        ++ans.length;
    }
    ans.simplify();
    return ans;
}

BigInt operator*(const BigInt &first, const BigInt &second) {
    BigInt ans;
    ans.header->data = (first.header->data == second.header->data) ? 0 : 1;
    ans.length = first.length + second.length;
    BigInt::LinkedList *p = first.header->next, *q = second.header->next, *r = ans.header, *s = ans.header;
    for (int i = 1; i <= ans.length; ++i) {
        r->next = new BigInt::LinkedList(0, r);
        r = r->next;
    }
    ans.rear = r;
    r = ans.header->next;
    while (p) {
        s = r;
        q = second.header->next;
        while (q) {
            s->data += p->data * q->data;
            s = s->next;
            q = q->next;
        }
        r = r->next;
        p = p->next;
    }
    ans.simplify();
    return ans;
}

BigInt operator/(const BigInt &first, const BigInt &second) {
    assert(second != 0);
    BigInt ans;
    ans.length = first.length;
    BigInt::LinkedList *p = ans.header;
    for (int i = 1; i <= ans.length; ++i) {
        p->next = new BigInt::LinkedList(0, p);
        p = p->next;
    }
    ans.rear = p;
    BigInt remain = BigInt::abs(first);
    BigInt subtrahend = BigInt::abs(second);
    while (true) {
        BigInt stdSubtrahend = 1;
        while (remain >= stdSubtrahend * 10 * subtrahend) {
            stdSubtrahend *= 10;
        }
        while (remain >= stdSubtrahend * subtrahend) {
            ans = ans + stdSubtrahend;
            remain = remain - stdSubtrahend * subtrahend;
        }
        if (stdSubtrahend == 1) {
            break;
        }
    }
    ans.header->data = (first.header->data == second.header->data) ? 0 : 1;
    ans.simplify();
    if (ans.length == 1 && ans.header->next->data == 0) {
        ans.header->data = 0;
    }
    return ans;
}

BigInt &BigInt::operator+=(const BigInt &second) {
    BigInt tmp = *this + second;
    *this = tmp;
    return *this;
}

BigInt &BigInt::operator-=(const BigInt &second) {
    BigInt tmp = *this - second;
    *this = tmp;
    return *this;
}

BigInt &BigInt::operator*=(const BigInt &second) {
    BigInt tmp = *this * second;
    *this = tmp;
    return *this;
}

BigInt &BigInt::operator/=(const BigInt &second) {
    BigInt tmp = *this / second;
    *this = tmp;
    return *this;
}

BigInt &BigInt::operator++() {
    *this += 1;
    return *this;
}

BigInt BigInt::operator++(int x) {
    BigInt tmp = *this;
    ++(*this);
    return tmp;
}

BigInt &BigInt::operator--() {
    *this -= 1;
    return *this;
}

BigInt BigInt::operator--(int x) {
    BigInt tmp = *this;
    --(*this);
    return tmp;
}

void copy(BigInt &first, const std::string &second) {
    first.header = new BigInt::LinkedList();
    first.rear = first.header;
    first.length = 0;
    auto begin = second.rbegin();
    auto end = second.rend();
    if (*second.begin() == '-') {
        first.header->data = 1;
        assert(second.length() >= 1);
        end--;
    }
    BigInt::LinkedList *p = first.header;
    for (auto it = begin; it != end; ++it) {
        if (*it == ',') {
            continue;
        }
        p->next = new BigInt::LinkedList(*it - '0', p);
        first.rear = p->next;
        ++first.length;
        p = p->next;
    }
}

void copy(BigInt &first, const BigInt &second) {
    first.header = new BigInt::LinkedList();
    first.rear = first.header;
    first.length = second.length;
    first.header->data = second.header->data;
    BigInt::LinkedList *p = first.header, *q = second.header;
    while (q->next) {
        p->next = new BigInt::LinkedList(q->next->data, p);
        p = first.rear = p->next;
        q = q->next;
    }
}

void copy(BigInt &first, long long second) {
    first.header = new BigInt::LinkedList();
    first.rear = first.header;
    first.length = 0;
    if (second == 0) {
        first.rear = first.header->next = new BigInt::LinkedList(0);
        first.length = 1;
    } else {
        if (second < 0) {
            first.header->data = 1;
            second = -second;
        }
        BigInt::LinkedList *p = first.header;
        while (second) {
            p->next = new BigInt::LinkedList(second % 10, p);
            second /= 10;
            first.length++;
            p = first.rear = p->next;
        }
    }
}

BigInt power(const BigInt &first, const BigInt &second) {
    assert(second >= 0);
    BigInt ans = 1;
    for (BigInt i = 1; i <= second; ++i) {
        ans *= first;
    }
    return ans;
}

BigInt factorial(const BigInt &num) {
    assert(num >= 0);
    BigInt ans = 1;
    for (BigInt i = 1; i <= num; ++i) {
        ans *= i;
    }
    return ans;
}

void BigInt::simplify() {
    LinkedList *p = header->next;
    while (p->next) {
        p->data += 10;
        --p->next->data;
        p->next->data += p->data / 10;
        p->data %= 10;
        p = p->next;
    }
    if (p->data >= 10) {
        p->next = new LinkedList(p->data / 10, p);
        rear = p->next;
        ++length;
        p->data %= 10;
    }
    while (rear->data == 0 && length != 1) {
        LinkedList *tmp = rear->front;
        --length;
        tmp->next = nullptr;
        rear->front = nullptr;
        delete rear;
        rear = tmp;
    }
    if (length == 1 && header->next->data == 0) {
        header->data = 0;
    }
}

std::istream &operator>>(std::istream &in, BigInt &num) {
    std::string tmp;
    in >> tmp;
    for (auto it : tmp) {
        assert((it >= '0' && it <= '9') || it == ',' || it == '-');
    }
    num = tmp;
    return in;
}

std::ostream &operator<<(std::ostream &out, const BigInt &num) {
    if (num.header->data == 1) {
        out << '-';
    }
    BigInt::LinkedList *p = num.rear;
    int cnt = 0;
    while (p != num.header) {
        out << p->data;
        ++cnt;
        p = p->front;
        if ((num.length - cnt) % 4 == 0 && p != num.header) {
            out << ",";
        }
    }
    return out;
}
