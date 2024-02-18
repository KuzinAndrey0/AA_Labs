#pragma once

#include "../inc/general.h"
#include <vector>
#include <string>
#include <cstring>

using namespace std;

Matrix mult_classic(const Matrix& matrix1, const Matrix& matrix2);
Matrix mult_vinograd(const Matrix& matrix1, const Matrix& matrix2);
Matrix mult_vinograd_opt(const Matrix& matrix1, const Matrix& matrix2);
Matrix mult_strassen(const Matrix& matrix1, const Matrix& matrix2);