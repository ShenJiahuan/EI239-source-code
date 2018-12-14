//
//  main.cpp
//  TestQueue
//
//  Created by 沈嘉欢 on 2018/9/28.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include "../ParkingLot/NewQueue.hpp"

int main(int argc, const char * argv[]) {
    NewQueue<long long> s;
    for (long long i = 1; i <= 1000; i++) {
        s.push(i);
    }
    while (s.size() >= 500) {
        std::cout << s.front() << std::endl;
        s.pop();
    }
    for (long long i = 1001; i <= 2000; i++) {
        s.push(i);
    }
    while (s.size() != 0) {
        std::cout << s.front() << std::endl;
        s.pop();
    }
    return 0;
}
