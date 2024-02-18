#pragma once

#include <string>
#include <iostream>
#include <fcntl.h>
#include <ctime>
#include "../inc/general.h"
#include "../inc/algo.h"
#include <vector>

void gen_random(vector<int> &arr, const int len);

double calc_time(void (*func) (vector<int>&), vector<int>& arr1);