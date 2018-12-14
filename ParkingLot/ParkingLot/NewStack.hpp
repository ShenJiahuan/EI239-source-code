//
//  NewStack.hpp
//  ParkingLot
//
//  Created by 沈嘉欢 on 2018/9/28.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#ifndef NewStack_hpp
#define NewStack_hpp

#include <memory>

template <typename T>
class NewStack {
private:
    uint32_t stackSize;
    uint32_t stackMaxSize;
    std::unique_ptr<T[]> list;
    void expand() {
        stackMaxSize *= 2;
        std::unique_ptr<T[]> newList(new T[stackMaxSize]);
        for (uint32_t i = 0; i < stackSize; ++i) {
            newList[i] = list[i];
        }
        list.reset(newList.release());
    }
public:
    NewStack(): stackSize(0), stackMaxSize(8), list(new T[stackMaxSize]) {};
    void push(const T &data) {
        if (stackSize == stackMaxSize) {
            expand();
        }
        list[stackSize] = data;
        ++stackSize;
    }
    T top() const {
        assert(stackSize != 0);
        return list[stackSize - 1];
    }
    void pop() {
        assert(stackSize != 0);
        --stackSize;
    }
    uint32_t size() const {
        return stackSize;
    }
};

#endif /* NewStack_hpp */
