#pragma once

#include <iostream>
#include <iomanip>

#define MODE_INTERACTIVE 0
#define MODE_CALC 1

#define MODE MODE_CALC

class Matrix 
{
    int **mat;
public:
    int width, height;

    Matrix(int w, int h);
    Matrix();
    Matrix(int w, int h, int val);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix();
    int *operator[](const int row) const;
    int *operator[](const int row);
    Matrix operator+(Matrix& matrix1);
    Matrix operator-(Matrix& matrix1);

    Matrix operator=(const Matrix& other);
    Matrix operator=(Matrix&& other) noexcept;

    Matrix slice(int begRow, int endRow, int begCol, int endCol);
    Matrix slice(int begRow, int endRow, int begCol, int endCol) const;


};

void print_matrix(Matrix matrix);
Matrix matrix_merge(const Matrix &a11, const Matrix &a12, const Matrix &a21, const Matrix &a22);
