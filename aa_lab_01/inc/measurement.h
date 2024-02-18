#pragma once

#include <string>
#include <iostream>
#include <fcntl.h>
#include <ctime>
#include "../inc/general.h"
#include "../inc/algo.h"

std::string gen_random(const int len);

template <IsStr T>
double calc_time(int (*func)(const T& str1,const T& str2), T& str1, T& str2)
{
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    func(str1, str2);
    end_t = clock();
    total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    return total_t;
}