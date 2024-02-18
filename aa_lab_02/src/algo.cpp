#include "../inc/algo.h"
#include "../inc/general.h"

Matrix mult_classic(const Matrix& matrix1, const Matrix& matrix2)
{
     int rows = matrix1.height, 
        columns = matrix2.width,
        tmp = matrix1.width;

    Matrix res{rows, columns, 0};

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < columns; ++j) {
            
            for (int k = 0; k < columns; ++k) {
                res[i][j] = res[i][j] + matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return res;   
}

Matrix mult_vinograd(const Matrix& matrix1, const Matrix& matrix2)
{
    int rows = matrix1.height;

    Matrix res{rows, rows};

    vector<int> mulH(rows, 0);
    vector<int> mulV(rows, 0);

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < rows / 2; ++j) 
            mulH[i] = mulH[i] + matrix1[i][j * 2] * matrix1[i][j * 2 + 1]; 
    }

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < rows / 2; ++j) 
            mulV[i] = mulV[i] +  matrix2[j * 2][i] * matrix2[j * 2 + 1][i];
    }

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < rows; ++j) {
            
            res[i][j] = -mulH[i] - mulV[j];

            for (int k = 0; k < rows / 2; ++k) 
                res[i][j] = res[i][j] + (matrix1[i][k* 2] + matrix2[k* 2 + 1][j]) * (matrix1[i][k* 2 + 1] + matrix2[k* 2][j]);
        }
    }

    if (rows % 2) {

        for (int i = 0; i < rows; ++i) {

            for (int j = 0; j < rows; ++j) 
                res[i][j] = res[i][j] + matrix1[i][rows - 1] * matrix2[rows - 1][j];
        }
    }

    return res;   
}
Matrix mult_vinograd_opt(const Matrix& matrix1, const Matrix& matrix2)
{
    int rows = matrix1.height;

    Matrix res{rows, rows, 0};

    vector<int> mulH(rows, 0);
    vector<int> mulV(rows, 0);

    int stepHalf = rows / 2;

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < stepHalf; ++j) 
            mulH[i] = mulH[i] + matrix1[i][(j << 1)] * matrix1[i][(j << 1) + 1]; 
    }

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < stepHalf; ++j) 
            mulV[i] = mulV[i] +  matrix2[(j << 1)][i] * matrix2[(j << 1) + 1][i];
    }

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < rows; ++j) {
            
            res[i][j] = -mulH[i] - mulV[j];

            for (int k = 0; k < stepHalf; ++k) 
                res[i][j] = res[i][j] + (matrix1[i][(k << 1)] + matrix2[(k << 1) + 1][j]) * (matrix1[i][(k << 1) + 1] + matrix2[(k << 1)][j]);
        }
    }

    if (rows % 2) {

        for (int i = 0; i < rows; ++i) {

            for (int j = 0; j < rows; ++j) 
                res[i][j] = res[i][j] + matrix1[i][rows - 1] * matrix2[rows - 1][j];
        }
    }

    return res;   
}

Matrix mult_strassen(const Matrix& matrix1, const Matrix& matrix2)
{
    int rows = matrix1.height;
    int n = rows / 2;

    if (rows <= 2)
        return mult_classic(matrix1, matrix2);

    auto a11 = matrix1.slice(0, n, 0, n);
    auto a12 = matrix1.slice(0, n, n, rows);
    auto a21 = matrix1.slice(n, rows, 0, n);
    auto a22 = matrix1.slice(n, rows, n, rows);

    auto b11 = matrix2.slice(0, n, 0, n);
    auto b21 = matrix2.slice(n, rows, 0, n);

    auto b12 = matrix2.slice(0, n, n, rows);
    auto b22 = matrix2.slice(n, rows, n, rows);

    auto p1 = mult_strassen(a11 + a22, b11 + b22);
    auto p2 = mult_strassen(a22, b21 - b11);
    auto p3 = mult_strassen(a11 + a12, b22);
    auto p4 = mult_strassen(a12 - a22, b21 + b22);
    auto p5 = mult_strassen(a11, b12 - b22);
    auto p6 = mult_strassen(a21 + a22, b11);
    auto p7 = mult_strassen(a11 - a21, b11 + b12);

    auto c11 = p1 + p2 - p3 + p4;
    auto c12 = p5 + p3;
    auto c21 = p6 + p2;
    auto c22 = p5 + p1 - p6 - p7;


    return matrix_merge(c11, c12, c21, c22);;
}
