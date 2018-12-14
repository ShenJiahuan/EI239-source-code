//
//  main.cpp
//  Polynomial
//
//  Created by 沈嘉欢 on 2018/10/10.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include "Polynomial.hpp"

int main(int argc, const char * argv[]) {
    using std::cin;
    using std::cout;
    using std::endl;
    Polynomial poly1, poly2;
    cin >> poly1 >> poly2;
    cout << poly1 + poly2 << endl;
    cout << poly1 - poly2 << endl;
    cout << poly1 * poly2 << endl;
    cout << poly1.derivative() << endl;
    cout << poly2.derivative() << endl;
    return 0;
}
