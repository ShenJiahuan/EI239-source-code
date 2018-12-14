
//
//  ParkingLot.cpp
//  ParkingLot
//
//  Created by 沈嘉欢 on 2018/9/28.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include "ParkingLot.hpp"

ParkingLot::ParkingLot(uint32_t size, double unitPrice) {
    this->size = size;
    this->unitPrice = unitPrice;
};

std::pair<uint32_t, double> ParkingLot::calc(const ParkingLot::Car &c) {
    assert(c.departureTime >= c.arrivalTime);
    uint32_t duration = c.departureTime - c.arrivalTime;
    double price = duration * unitPrice;
    return std::make_pair(duration, price);
}

void ParkingLot::arrival(const std::string &id, uint32_t arrivalTime) {
    Car c(id, arrivalTime);
    if (lot.size() < size) {
        lot.push(c);
    } else {
        lane.push(c);
    }
}

std::pair<uint32_t, double> ParkingLot::departure(const std::string &id, uint32_t departureTime) {
    Car c;
    if (lot.top().id == id) {
        c = lot.top();
        lot.pop();
        c.departureTime = departureTime;
    } else {
        stack<Car> tmp;
        while (lot.top().id != id) {
            tmp.push(lot.top());
            lot.pop();
            assert(lot.size() > 0);
        }
        c = lot.top();
        lot.pop();
        c.departureTime = departureTime;
        while (tmp.size() != 0) {
            lot.push(tmp.top());
            tmp.pop();
        }
    }
    if (lane.size() != 0) {
        Car tmp = lane.front();
        tmp.arrivalTime = departureTime;
        lot.push(tmp);
        lane.pop();
    }
    return calc(c);
}

void ParkingLot::departureFromLane(const std::string &id) {
    uint32_t cnt = 0;
    while (lane.front().id != id && cnt != lane.size()) {
        lane.push(lane.front());
        lane.pop();
        cnt++;
    }
    assert(lane.front().id == id);
    lane.pop();
}
