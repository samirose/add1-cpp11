//
//  add1.h
//  add1
//
//  Created by Sami Rosendahl on 22.8.2012.
//  Copyright (c) 2012 Sami Rosendahl. All rights reserved.
//
// Array Iteration Interview Problem solution in C++11
// See http://blog.jazzychad.net/2012/08/01/array-iteration-problem.html
//

#ifndef ADD1_H
#define ADD1_H

#include <cstddef>

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

int* add1(int* arr, std::size_t sz, int val, int n);

#endif
