//
// Created by 沈嘉欢 on 2018/12/11.
//

#ifndef HASH_HASHTABLE_H
#define HASH_HASHTABLE_H
#include <vector>
#include <functional>

template <typename Key, typename Value>
class HashTable {
protected:
    struct Item {
        Key index;
        Value value;
    };
    size_t size;
    size_t remain;
    size_t totalCollide;
    std::vector<Item> data;
    enum Stat {Available, Exist, Removed};
    std::vector<Stat> stat;
    std::function<int(Key, size_t)> hashFunc;
    virtual size_t nextHash(int i, size_t size, int collideTimes) = 0;
    inline bool prime(int x);
    size_t nextSize(size_t size);
    Value get(const Key &index, bool &status);
    virtual void rehash() = 0;
    virtual void rehash(HashTable *expanded);
    Value& set(const Key &index, const Value &value);
    struct Deref {
        HashTable &table;
        const Key &index;
        Deref(HashTable &table, const Key &index): table(table), index(index) {};
        operator Value() {
            // get
            bool status;
            Value result = table.get(index, status);
            if (!status) {
                table.set(index, result);
            }
            return result;
        }
        Value& operator=(const Value& value) {
            // set
            return table.set(index, value);
        }
    };
public:
    explicit HashTable(std::function<int(Key, size_t)> hashFunc, size_t size=11):
    size(size), remain(size), totalCollide(0), data(size), stat(size, Available), hashFunc(hashFunc) {};
    Deref operator[](const Key &index) {
        return Deref(*this, index);
    }
    void erase(Key index);
    double collideRate() const {
        return static_cast<double>(totalCollide) / (totalCollide + (size - remain));
    }

    double averageSearchLength() const {
        return static_cast<double>(totalCollide) / (size - remain) + 1;
    }
    virtual ~HashTable() = default;
};

template<typename Key, typename Value>
size_t HashTable<Key, Value>::nextSize(size_t size) {
    size_t next = size * 2 + 1;
    while (!prime(next)) {
        ++next;
    }
    return next;
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::prime(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

template<typename Key, typename Value>
Value HashTable<Key, Value>::get(const Key &index, bool &status) {
    int id = hashFunc(index, size);
    int collide = 0;
    while (stat[id] != Available) {
        if (data[id].index == index) {
            status = true;
            return data[id].value;
        } else {
            ++collide;
            id = nextHash(id, size, collide);
        }
    }
    status = false;
    return Value();
}

template<typename Key, typename Value>
void HashTable<Key, Value>::rehash(HashTable *expanded) {
    for (int i = 0; i < this->size; ++i) {
        if (this->data[i].index != Key()) {
            (*expanded)[this->data[i].index] = this->data[i].value;
        }
    }
    this->size = expanded->size;
    this->remain = expanded->remain;
    this->totalCollide = expanded->totalCollide;
    this->data = expanded->data;
    this->stat = expanded->stat;
}

template<typename Key, typename Value>
Value &HashTable<Key, Value>::set(const Key &index, const Value &value) {
    int id = hashFunc(index, size);
    int collide = 0;
    while (stat[id] == Exist && data[id].index != index) {
        ++collide;
        id = nextHash(id, size, collide);
    }
    totalCollide += collide;
    if (stat[id] != Exist) {
        --remain;
    }
    if (remain <= size / 2) {
        rehash();
        return set(index, value);
    } else {
        data[id] = {index, value};
        stat[id] = Exist;
        return data[id].value;
    }
}

template<typename Key, typename Value>
void HashTable<Key, Value>::erase(Key index) {
    int id = hashFunc(index);
    int collide = 0;
    while (stat[id] == Exist && data[id].index != index) {
        ++collide;
        id = nextHash(id, size, collide);
    }
    if (data[id].index == index) {
        stat[id] = Removed;
        totalCollide -= collide;
        ++remain;
    }
}

template <typename Key, typename Value>
class LinearProbingHashTable : public HashTable<Key, Value> {
private:
    void rehash() override {
        LinearProbingHashTable<Key, Value> expanded(this->hashFunc, this->nextSize(this->size));
        HashTable<Key, Value>::rehash(&expanded);
    }
public:
    explicit LinearProbingHashTable(std::function<int(Key, size_t)> hashFunc, size_t size=11): HashTable<Key, Value>(hashFunc, size) {};
    size_t nextHash(int i, size_t size, int collideTimes) override {
        return (i + 1) % size;
    }
    ~LinearProbingHashTable() override = default;
};

template <typename Key, typename Value>
class QuadraticProbingHashTable : public HashTable<Key, Value> {
private:
    void rehash() override {
        QuadraticProbingHashTable<Key, Value> expanded(this->hashFunc, this->nextSize(this->size));
        HashTable<Key, Value>::rehash(&expanded);
    }
public:
    explicit QuadraticProbingHashTable(std::function<int(Key, size_t)> hashFunc, size_t size=11): HashTable<Key, Value>(hashFunc, size) {};
    size_t nextHash(int i, size_t size, int collideTimes) override {
        return (i + 2 * collideTimes - 1) % size;
    }
    ~QuadraticProbingHashTable() override = default;
};

#endif //HASH_HASHTABLE_H
