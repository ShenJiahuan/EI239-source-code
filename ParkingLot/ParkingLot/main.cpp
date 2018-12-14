//
//  main.cpp
//  ParkingLot
//
//  Created by 沈嘉欢 on 2018/9/28.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "ParkingLot.hpp"

int main(int argc, const char * argv[]) {
    int n, unit_price;
    std::cin >> n >> unit_price;
    ParkingLot p(n, unit_price);
    bool alive = true;
    while (alive) {
        char choice;
        std::string id;
        uint32_t time;
        std::cin >> choice >> id >> time;
        switch (choice) {
            case 'A': {
                p.arrival(id, time);
                break;
            }
            case 'D': {
                auto property = p.departure(id, time);
                std::cout << property.first << " " << property.second << "\n";
                break;
            }
            case 'E': {
                alive = false;
                break;
            }
            case 'L': {
                p.departureFromLane(id);
                break;
            }
            default:
                std::cout << "Error!\n";
                break;
        }
    }
    return 0;
}
