#pragma once

#include <iostream>
#include <vector>
#include "time.h"
#include <iomanip>

using namespace std;

using matrixT = vector<vector<int>>;

struct matrix_s {
    std::vector<std::vector<int>> data;

    vector<int> values;
    vector<int> column_indices;
    vector<int> row_pointers;

    int num_rows;
    int num_cols;

    size_t size;
    int determ;

    string dump;
};
using matrix_t = struct matrix_s;

struct CSRMatrix {
    vector<int> values;
    vector<int> column_indices;
    vector<int> row_pointers;

    int num_rows;
    int num_cols;

    CSRMatrix();

    matrixT convertToNormalMatrix();

    CSRMatrix(int rows, int cols);

    void printMatrix();

    void printMatrix2();

    void addValue(int row, int col, int value);
};



void printMatrix(const matrixT& matrix);

matrixT readNormalMatrixFromStdin();

//void (*func)(matrix_t &)

void convertToCSRNew(matrix_t &matrix);

CSRMatrix convertToCSR(const matrixT& matrix);

CSRMatrix removeFirstRowAndColumn(const CSRMatrix& matrix, int i);

int CSRElem(const CSRMatrix& matrix, int row, int col);


matrix_t generateMatrix(size_t size);


int calcDeterm(CSRMatrix &mat, int size);

int calc_determ(matrixT &mat, int size);

void calcDetermNew(matrix_t &matrix);



string makeDump(CSRMatrix &mat, int &det);

void makeDumpNew(matrix_t &matrix);