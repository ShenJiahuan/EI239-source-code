//
//  Sort.h
//  Sort
//
//  Created by 沈嘉欢 on 2018/12/2.
//  Copyright © 2018 沈嘉欢. All rights reserved.
//

#ifndef Sort_h
#define Sort_h
#include <iostream>
#include <map>

// 检查排序的稳定性

namespace sort {
    template <class Iterator>
    void swap(Iterator x, Iterator y) {
        auto tmp = *x;
        *x = *y;
        *y = tmp;
    }
    
    template <class Iterator, class Compare>
    std::tuple<int, int> bubbleSort(Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        bool sorted = false;
        for (Iterator i = begin; i != end - 1 && !sorted; ++i) {
            sorted = true;
            for (Iterator j = end - 1; j != i; --j) {
                ++comparison;
                if (cmp(*j, *(j - 1))) {
                    move += 3;
                    sort::swap(j - 1, j);
                    sorted = false;
                }
            }
        }
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator>
    std::tuple<int, int> bubbleSort(Iterator begin, Iterator end) {
        return bubbleSort(begin, end, std::less<decltype(*begin)>());
    }
    
    template <class Iterator, class Compare>
    std::tuple<int, int> directInsertionSort(Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        for (Iterator i = begin + 1; i != end; ++i) {
            ++move;
            auto tmp = *i;
            Iterator j = i;
            while (j != begin && (1 | ++comparison) && cmp(tmp, *(j - 1))) {
                ++move;
                *j = *(j - 1);
                --j;
            }
            ++move;
            *j = tmp;
        }
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator>
    std::tuple<int, int> directInsertionSort(Iterator begin, Iterator end) {
        return directInsertionSort(begin, end, std::less<decltype(*begin)>());
    }
    
    template <class Iterator, class Compare>
    std::tuple<int, int> selectionSort(Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        if (end - begin == 1) {
            return std::make_tuple(0, 0);
        }
        for (Iterator i = begin; i != end; ++i) {
            Iterator minPos = i;
            for (Iterator j = i + 1; j != end; ++j) {
                ++comparison;
                if (cmp(*j, *minPos)) {
                    minPos = j;
                }
            }
            move += 3;
            sort::swap(i, minPos);
        }
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator>
    std::tuple<int, int> selectionSort(Iterator begin, Iterator end) {
        return selectionSort(begin, end, std::less<decltype(*begin)>());
    }
    
    template <class Iterator, class Compare>
    std::tuple<int, int> quickSort(Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        if (end - begin <= 1) {
            return std::make_tuple(0, 0);
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, static_cast<int>(end - begin - 1));
        move += 3;
        sort::swap(begin, begin + dis(gen));
        ++move;
        auto pivot = *begin;
        Iterator i = begin, j = end - 1;
        while (i != j) {
            while ((1 | ++comparison) && cmp(pivot, *j) && i < j) {
                --j;
            }
            if (i < j) {
                ++move;
                *i = *j;
                ++i;
            }
            while ((1 | ++comparison) && cmp(*i, pivot) && i < j) {
                ++i;
            }
            if (i < j) {
                ++move;
                *j = *i;
                --j;
            }
        }
        ++move;
        *i = pivot;
        int tmp_comparison, tmp_move;
        std::tie(tmp_comparison, tmp_move) = quickSort(begin, i, cmp);
        comparison += tmp_comparison;
        move += tmp_move;
        std::tie(tmp_comparison, tmp_move) = quickSort(i + 1, end, cmp);
        comparison += tmp_comparison;
        move += tmp_move;
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator>
    std::tuple<int, int> quickSort(Iterator begin, Iterator end) {
        return quickSort(begin, end, std::less<decltype(*begin)>());
    }

    template <class Iterator, class Compare>
    std::tuple<int, int> shellSort(Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        for (int d = static_cast<int>((end - begin)) >> 1; d >= 1; d >>= 1) {
            for (Iterator i = begin; i != begin + d; ++i) {
                for (Iterator j = i + d; j < end; j += d) {
                    ++move;
                    auto tmp = *j;
                    Iterator k = j;
                    while (k != i && (1 | ++comparison) && cmp(tmp, *(k - d))) {
                        ++move;
                        *k = *(k - d);
                        k -= d;
                    }
                    ++move;
                    *k = tmp;
                }
            }
        }
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator>
    std::tuple<int, int> shellSort(Iterator begin, Iterator end) {
        return shellSort(begin, end, std::less<decltype(*begin)>());
    }
    
    template <class Iterator, class Compare>
    std::tuple<int, int> merge(Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        Iterator lpos = begin, lend = begin + ((end - begin) >> 1);
        Iterator rpos = begin + ((end - begin) >> 1), rend = end;
        std::vector<std::decay_t<decltype(*begin)>> result(end - begin);
        Iterator pos = result.begin();
        while (lpos != lend && rpos != rend) {
            if ((1 | ++comparison) && !cmp(*rpos, *lpos)) {
                ++move;
                *pos = *lpos;
                lpos++;
            } else {
                ++move;
                *pos = *rpos;
                rpos++;
            }
            pos++;
        }
        while (lpos != lend) {
            ++move;
            *pos = *lpos;
            lpos++;
            pos++;
        }
        while (rpos != rend) {
            ++move;
            *pos = *rpos;
            rpos++;
            pos++;
        }
        pos = result.begin();
        for (Iterator it = begin, pos = result.begin(); it != end; ++it, ++pos) {
            *it = *pos;
        }
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator, class Compare>
    std::tuple<int, int> mergeSort(Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        if (end - begin <= 1) {
            return std::make_tuple(0, 0);
        }
        int tmp_comparison, tmp_move;
        std::tie(tmp_comparison, tmp_move) = mergeSort(begin, begin + ((end - begin) >> 1), cmp);
        comparison += tmp_comparison;
        move += tmp_move;
        std::tie(tmp_comparison, tmp_move) = mergeSort(begin + ((end - begin) >> 1), end, cmp);
        comparison += tmp_comparison;
        move += tmp_move;
        std::tie(tmp_comparison, tmp_move) = merge(begin, end, cmp);
        comparison += tmp_comparison;
        move += tmp_move;
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator>
    std::tuple<int, int> mergeSort(Iterator begin, Iterator end) {
        return mergeSort(begin, end, std::less<decltype(*begin)>());
    }
    
    template <class Iterator, class Compare>
    std::tuple<int, int> binaryInsertionSort(Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        for (Iterator i = begin + 1; i != end; ++i) {
            ++move;
            auto tmp = *i;
            Iterator l = begin, r = i - 1;
            while (l <= r) {
                Iterator mid = l + (r - l) / 2;
                if ((1 | ++comparison) && !cmp(tmp, *mid)) {
                    l = mid + 1;
                } else {
                    if (r != begin) {
                        r = mid - 1;
                    }
                    else {
                        break;
                    }
                }
            }
            Iterator j;
            for (j = i; j > l; --j) {
                *j = *(j - 1);
                ++move;
            }
            *j = tmp;
            ++move;
        }
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator>
    std::tuple<int, int> binaryInsertionSort(Iterator begin, Iterator end) {
        return binaryInsertionSort(begin, end, std::less<decltype(*begin)>());
    }
    
    template <class Iterator, class Compare>
    std::tuple<int, int> heapify(Iterator cur, Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        while (cur < end) {
            Iterator left = (cur - begin + 1) + cur;
            Iterator right = (cur - begin + 1) + cur + 1;
            if (left < end && right < end && (((1 | ++comparison) && cmp(*left, *cur)) || ((1 | ++comparison) && cmp(*right, *cur)))) {
                if ((1 | ++comparison) && cmp(*left, *right)) {
                    sort::swap(cur, left);
                    move += 3;
                    cur = left;
                } else {
                    sort::swap(cur, right);
                    move += 3;
                    cur = right;
                }
            } else if (left < end && (1 | ++comparison) && cmp(*left, *cur)) {
                sort::swap(cur, left);
                move += 3;
                cur = left;
            } else {
                break;
            }
        }
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator, class Compare>
    std::tuple<int, int> heapSort(Iterator begin, Iterator end, const Compare &cmp) {
        int comparison = 0, move = 0;
        for (Iterator it = begin + (end - begin + 1) / 2 - 1; it >= begin; --it) {
            int tmp_comparison, tmp_move;
            std::tie(tmp_comparison, tmp_move) = heapify(it, begin, end, cmp);
            comparison += tmp_comparison;
            move += tmp_move;
        }
        std::vector<std::decay_t<decltype(*begin)>> result;
        int cnt = 0;
        while (cnt < end - begin) {
            result.push_back(*begin);
            swap(begin, end - 1 - cnt);
            move += 3;
            int tmp_comparison, tmp_move;
            std::tie(tmp_comparison, tmp_move) = heapify(begin, begin, end - 1 - cnt, cmp);
            comparison += tmp_comparison;
            move += tmp_move;
            ++cnt;
        }
        for (Iterator it = begin, pos = result.begin(); it != end; ++it, ++pos) {
            *it = *pos;
        }
        return std::make_tuple(comparison, move);
    }
    
    template <class Iterator>
    std::tuple<int, int> heapSort(Iterator begin, Iterator end) {
        return heapSort(begin, end, std::less<decltype(*begin)>());
    }
}

#endif /* Sort_h */
