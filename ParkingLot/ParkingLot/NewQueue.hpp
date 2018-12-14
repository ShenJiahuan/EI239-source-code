//
//  NewQueue.hpp
//  ParkingLot
//
//  Created by 沈嘉欢 on 2018/9/28.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#ifndef NewQueue_h
#define NewQueue_h

#include <memory>

template <typename T>
class NewQueue {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        Node(): next(nullptr) {};
        Node(T data): data(data), next(nullptr) {};
    };
    std::shared_ptr<Node> rearPtr, frontPtr;
    uint32_t queueSize;
public:
    NewQueue(): rearPtr(nullptr), frontPtr(nullptr), queueSize(0) {};
    void push(const T &data) {
        auto current = std::make_shared<Node>(data);
        if (queueSize != 0) {
            rearPtr->next = current;
            rearPtr = current;
        } else {
            rearPtr = frontPtr = current;
        }
        ++queueSize;
    }
    T front() const {
        assert(queueSize != 0);
        return frontPtr->data;
    }
    void pop() {
        assert(queueSize != 0);
        frontPtr = frontPtr->next;
        --queueSize;
    }
    uint32_t size() const {
        return queueSize;
    }
};
#endif /* NewQueue_h */
