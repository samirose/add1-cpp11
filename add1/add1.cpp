//
//  add1.cpp
//  add1
//
//  Created by Sami Rosendahl on 2.8.2012.
//  Copyright (c) 2012 Sami Rosendahl. All rights reserved.
//
// Array Iteration Interview Problem solution in C++11
// See http://blog.jazzychad.net/2012/08/01/array-iteration-problem.html
//

#include "add1.h"
#include <cstddef>
#include <algorithm>
#include <iterator>

namespace {

    template<class RandomAccessIterator, class Size, class T>
    void replace_n(RandomAccessIterator first, RandomAccessIterator last,
                   Size n, const T& value, const T& new_value)
    {
        while ((first = std::find(first, last, value)) != last && n > 0) {
            if (n < last-first) {
                *first = new_value;
                --n;
            }
            else {
                std::replace(first, last, value, new_value);
                return;
            }
        }
    }

}

int* add1(int* arr, std::size_t sz, int val, int n)
{
    if (n == 0) {
        std::replace(arr, arr+sz, val, val+1);
    }
    else if (n > 0) {
        replace_n(arr, arr+sz, n, val, val+1);
    }
    else if (n < 0) {
        replace_n(std::reverse_iterator<int*>(arr+sz), std::reverse_iterator<int*>(arr), -n, val, val+1);
    }
    return arr;
}
