#include <string>
#include "../inc/general.h"
#include "../inc/measurement.h"
using namespace std;

void gen_random(vector<int> &arr, const int len) {
    arr.clear();
    for(int i = 0; i < len; i ++)
        arr.push_back(len - i);
}

double calc_time(void (*func) (vector<int>&), vector<int>& arr1)
{
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    func(arr1);
    end_t = clock();
    total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    return total_t;
}