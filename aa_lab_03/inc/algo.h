#pragma once

#include "../inc/general.h"
#include <vector>
#include <string>
#include <cstring>

using namespace std;

void sort_smooth(vector<int> &arr);
void sort_shaker(vector<int> &arr);
void sort_shell(vector<int> &arr);

typedef long long INT;

int NextState(INT &curState);
void PrevState(INT &curState);