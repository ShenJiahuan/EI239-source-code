//
//  main.cpp
//  ParkingLot
//
//  Created by 沈嘉欢 on 2018/9/28.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include "../ParkingLot/NewStack.hpp"

int main(int argc, const char * argv[]) {
    NewStack<long long> s;
    for (long long i = 1; i <= 100; i++) {
        s.push(i);
    }
    while (s.size() >= 50) {
        std::cout << s.top() << std::endl;
        s.pop();
    }
    for (long long i = 101; i <= 200; i++) {
        s.push(i);
    }
    while (s.size() != 0) {
        std::cout << s.top() << std::endl;
        s.pop();
    }
    return 0;
}
