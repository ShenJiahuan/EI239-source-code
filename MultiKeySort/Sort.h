//
// Created by 沈嘉欢 on 2018/12/9.
//

#ifndef MULTIKEYSORT_SORT_H
#define MULTIKEYSORT_SORT_H

#include <random>

namespace sort {
    template <class Iterator>
    void swap(Iterator x, Iterator y) {
        auto tmp = *x;
        *x = *y;
        *y = tmp;
    }

    template <class Iterator, class Compare>
    void quickSort(Iterator begin, Iterator end, const Compare &cmp) {
        if (end - begin <= 1) {
            return;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, static_cast<int>(end - begin - 1));
        sort::swap(begin, begin + dis(gen));
        auto pivot = *begin;
        Iterator i = begin, j = end - 1;
        while (i != j) {
            while (cmp(pivot, *j) && i < j) {
                --j;
            }
            if (i < j) {
                *i = *j;
                ++i;
            }
            while (cmp(*i, pivot) && i < j) {
                ++i;
            }
            if (i < j) {
                *j = *i;
                --j;
            }
        }
        *i = pivot;
        quickSort(begin, i, cmp);
        quickSort(i + 1, end, cmp);
    }

    template <class Iterator>
    void quickSort(Iterator begin, Iterator end) {
        return quickSort(begin, end, std::less<decltype(*begin)>());
    }
}

#endif //MULTIKEYSORT_SORT_H
