//
//  main.cpp
//  BigInt
//
//  Created by 沈嘉欢 on 2018/9/21.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include "BigInt.h"

int main() {
    using std::cin;
    using std::cout;
    using std::endl;
    BigInt a, b;
    cin >> a >> b;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << a / b << endl;
    cout << power(a, b) << endl;
    cout << factorial(b) << endl;
    return 0;
}

// cannot input

// you see, not focused on this window before

// still cannot input
// but will work with a enter key
