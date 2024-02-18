#pragma once

#include <string>
#include <iostream>
#include <fcntl.h>
#include <ctime>
#include "../inc/general.h"
#include "../inc/algo.h"

Matrix gen_random(const int len);


double calc_time(Matrix (*func) (const Matrix&, const Matrix&), Matrix& str1, Matrix& str2);