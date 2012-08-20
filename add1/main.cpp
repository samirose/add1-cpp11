//
//  main.cpp
//  add1 tests
//
//  Created by Sami Rosendahl on 2.8.2012.
//  Copyright (c) 2012 Sami Rosendahl. All rights reserved.
//

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <algorithm>

int* add1(int* arr, std::size_t sz, int val, int n);

void print_array(const int* arr, std::size_t sz)
{
    const int* last = arr + sz - 1;
    std::cout << "{";
    std::copy(arr, last, std::ostream_iterator<int>(std::cout, ","));
    std::cout << *last;
    std::cout << "}";
}

bool equal(const int* res, const int* expected, std::size_t sz) {
    if (std::equal(res, res+sz, expected))
        return true;
    std::cout << "Expected: ";
    print_array(expected, sz);
    std::cout << ", but got ";
    print_array(res, sz);
    std::cout << std::endl;
    return false;
}

template<std::size_t N>
void assert_equal(const int* res, const int (&expected)[N])
{
    assert(equal(res, expected, N));
}

void test_general_properties_of_add1(int* arr, int* res, std::size_t sz, int val, int n)
{
    // The algorithm modifies the array in-place
    assert(res == arr);
    int* const begin = res;
    int* const end = res+sz;
    if (n == 0 || std::abs(n) >= sz) {
        // There should be no values equal to val left in the array
        assert(std::count(begin, end, val) == 0);
    }
    else {
        // There should at most sz-abs(n) values equal to val left in the result array
        assert(std::count(begin, end, val) <= sz - std::abs(n));
    }
}

template<std::size_t N>
void test_add1(int* arr, std::size_t sz, int val, int n, const int (&expected)[N])
{
    int* res = add1(arr, sz, val, n);
    test_general_properties_of_add1(arr, res, sz, val, n);
    assert(equal(res, expected, N));
}

void test_arr_not_modified_when_sz_is_zero()
{
    int arr[] = {1, 2, 3};
    const std::size_t sz = 0;
    test_add1(arr, sz, 1,  0, (int[]){1, 2, 3});
    test_add1(arr, sz, 1,  1, (int[]){1, 2, 3});
    test_add1(arr, sz, 1, -1, (int[]){1, 2, 3});
}

void test_arr_of_size_1()
{
    int arr[] = {0};
    const std::size_t sz = 1;
    test_add1(arr, sz, 1,  0, (int[]){0});
    test_add1(arr, sz, 0,  0, (int[]){1});
    test_add1(arr, sz, 0,  1, (int[]){1});
    test_add1(arr, sz, 0, -1, (int[]){1});
    test_add1(arr, sz, 1,  1, (int[]){2});
    test_add1(arr, sz, 2, -1, (int[]){3});
    test_add1(arr, sz, 2,  2, (int[]){3});
    test_add1(arr, sz, 2, -2, (int[]){3});
    test_add1(arr, sz, 3,  2, (int[]){4});
    test_add1(arr, sz, 4, -2, (int[]){5});
}

void test_replace_all()
{
    int arr[] = {1, 2, 3};
    const std::size_t sz = 3;

    for (int n = -(sz+1); n <= sz+1; ++n) {
        test_add1(arr, sz, 0,  n, (int[]){1, 2, 3});
    }

    test_add1(arr, sz, 1,   0, (int[]){2, 2, 3});
    test_add1(arr, sz, 2,  sz, (int[]){3, 3, 3});
    test_add1(arr, sz, 3, -sz, (int[]){4, 4, 4});

    test_add1(arr, sz, 4,   sz+1 , (int[]){5, 5, 5});
    test_add1(arr, sz, 5, -(sz+1), (int[]){6, 6, 6});
}

void test_replace_n()
{
    int arr[] = {1, 1, 1};
    const std::size_t sz = 3;

    for (int n = -sz+1; n < sz; ++n) {
        test_add1(arr, sz, 0,  n, (int[]){1, 1, 1});
    }

    test_add1(arr, sz, 1,  1, (int[]){2, 1, 1});
    test_add1(arr, sz, 1, -1, (int[]){2, 1, 2});
    test_add1(arr, sz, 1,  1, (int[]){2, 2, 2});
    test_add1(arr, sz, 2,  2, (int[]){3, 3, 2});
    test_add1(arr, sz, 2,  2, (int[]){3, 3, 3});
    test_add1(arr, sz, 3, -2, (int[]){3, 4, 4});
    test_add1(arr, sz, 3, -2, (int[]){4, 4, 4});
}

void test_algorithm_does_not_over_or_undeflow_arr()
{
    int fullarr[] = {1, 1, 1, 1};
    int* arr = &(fullarr[1]);
    const std::size_t sz = 2;

    add1(arr, sz, 1, 0);
    assert_equal(fullarr, (int[]){1, 2, 2, 1});

    fullarr[0] = fullarr[3] = 2;
    add1(arr, sz, 2, 1);
    assert_equal(fullarr, (int[]){2, 3, 2, 2});

    add1(arr, sz, 2, -1);
    assert_equal(fullarr, (int[]){2, 3, 3, 2});

    fullarr[0] = fullarr[3] = 3;
    add1(arr, sz, 3, 2);
    assert_equal(fullarr, (int[]){3, 4, 4, 3});

    fullarr[0] = fullarr[3] = 4;
    add1(arr, sz, 4, -2);
    assert_equal(fullarr, (int[]){4, 5, 5, 4});

    fullarr[0] = fullarr[3] = 5;
    add1(arr, sz, 5, 3);
    assert_equal(fullarr, (int[]){5, 6, 6, 5});

    fullarr[0] = fullarr[3] = 6;
    add1(arr, sz, 6, -3);
    assert_equal(fullarr, (int[]){6, 7, 7, 6});
}

int main(int argc, const char * argv[])
{
    test_arr_not_modified_when_sz_is_zero();
    test_arr_of_size_1();
    test_replace_all();
    test_replace_n();
    test_algorithm_does_not_over_or_undeflow_arr();
    std::cout << "All tests passed" << std::endl;
    return 0;
}
