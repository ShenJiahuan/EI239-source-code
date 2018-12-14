//
//  ParkingLot.hpp
//  ParkingLot
//
//  Created by 沈嘉欢 on 2018/9/28.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#ifndef ParkingLot_hpp
#define ParkingLot_hpp

#include <string>
#include <cassert>

#ifdef DEBUG
#include <stack>
#include <queue>
template <typename T>
using stack = std::stack<T>;
template <typename T>
using queue = std::queue<T>;
#else
#include "NewStack.hpp"
#include "NewQueue.hpp"
template <typename T>
using stack = NewStack<T>;
template <typename T>
using queue = NewQueue<T>;
#endif /* DEBUG */

class ParkingLot {
private:
    struct Car {
        std::string id;
        uint32_t arrivalTime;
        uint32_t departureTime;
        Car() {};
        Car(const std::string &id, uint32_t arrivalTime): id(id), arrivalTime(arrivalTime), departureTime(0) {};
    };
    uint32_t size;
    double unitPrice;
    stack<Car> lot;
    queue<Car> lane;
    std::pair<uint32_t, double> calc(const Car &c);
public:
    ParkingLot(uint32_t size, double unitPrice);
    void arrival(const std::string &id, uint32_t arrivalTime);
    std::pair<uint32_t, double> departure(const std::string &id, uint32_t departureTime);
    void departureFromLane(const std::string &id);
    
};

#endif /* ParkingLot_hpp */
