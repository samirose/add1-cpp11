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

// add1 - increments items in an array matching specified value
//
// param: arr - array of integers to manipulate
// param: sz  - number of elements in arr
// param: val - integer, value to increment
// param: n   - integer, control value specifying behavior of manipulation
//   n == 0 means increment all occurrences of val
//
//   n > 0  means increment up to n occurrences of val
//          from left-to-right (forward)
//
//   n < 0  means increment up to n occurrences of val
//          from right-to-left (backward)
//
// return: arr with proper values incremented

#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <iterator>

template<class ForwardIterator, class Size, class T>
void replace_n(ForwardIterator first, ForwardIterator last,
               Size n, const T& value, const T& new_value)
{
    for (; first != last; ++first) {
        if (*first == value) {
            *first = new_value;
            if (--n == 0)
                break;
        }
    }
}

int* add1(int* arr, std::size_t sz, int val, int n)
{
    int* const begin = arr;
    int* const end = arr+sz;
    if (n == 0 || std::abs(n) >= sz) {
        std::replace(begin, end, val, val+1);
    }
    else if (n > 0) {
        replace_n(begin, end, n, val, val+1);
    }
    else if (n < 0) {
        replace_n(std::reverse_iterator<int*>(end), std::reverse_iterator<int*>(begin), -n, val, val+1);
    }
    return arr;
}
