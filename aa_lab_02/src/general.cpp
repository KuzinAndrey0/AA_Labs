#include "../inc/general.h"



Matrix::Matrix(int w, int h)
{
    height = h;
    width = w;
    mat = new int*[height];
    for (int i = 0; i < height; ++i)
    {
        mat[i] = new int[width];
    }
}

Matrix::Matrix(int w, int h, int val)
{
    height = h;
    width = w;
    mat = new int*[height];
    for (int i = 0; i < height; ++i)
    {
        mat[i] = new int[width];
        for(int j = 0; j < width; j ++)
        {
            mat[i][j] = val;
        }
    }
}

Matrix::Matrix()
{
    height = 0;
    width = 0;
    mat = NULL;
}

Matrix::Matrix(const Matrix& other)
{
    height = other.height;
    width = other.width;
    mat = new int*[height];
    for (int i = 0; i < height; ++i)
    {
        mat[i] = new int[width];
        for(int j = 0; j < width; j ++)
        {
            mat[i][j] = other[i][j];
        }
    }    
}

Matrix::Matrix(Matrix&& other) noexcept 
{

    height = other.height;
    width = other.width;
    mat = other.mat;
    for (int i = 0; i < height; ++i)
    {
        mat[i] = other[i];
        for(int j = 0; j < width; j ++)
        {
            mat[i][j] = other[i][j];
        }
    }      
}

Matrix::~Matrix()
{
    for (int i = 0; i < height; ++i)
        delete[] mat[i];    
    delete[] mat;
}

int* Matrix::operator[](const int row) const
{
    return mat[row];
}

int* Matrix::operator[](const int row)
{
    return mat[row];
}

Matrix Matrix::operator+(Matrix& matrix1)
{

    Matrix res(width, height);

    for (int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; j ++)
        {
            res[i][j] = matrix1[i][j] + (*this)[i][j];
        }
    }  
    return res;
}

Matrix Matrix::operator-(Matrix& matrix1)
{
    Matrix res(width, height);
    for (int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; j ++)
        {
            res[i][j] = (*this)[i][j] - matrix1[i][j];
        }
    }  
    return res;
}

Matrix Matrix::operator=(const Matrix& other)
{
    if (this == &other)
        return *this;
    for (int i = 0; i < height; ++i)
        delete[] mat[i];    
    delete[] mat;
    height = other.height;
    width = other.width;
    mat = new int*[height];
    for (int i = 0; i < height; ++i)
    {
        mat[i] = new int[width];
        for(int j = 0; j < width; j ++)
        {
            mat[i][j] = other[i][j];
        }
    } 
    return (*this);
}
Matrix Matrix::operator=(Matrix&& other) noexcept
{
    if (this == &other)
        return *this;
    for (int i = 0; i < height; ++i)
        delete[] mat[i];    
    delete[] mat;
    height = other.height;
    width = other.width;
    mat = other.mat;
    other.mat = NULL;
    other.height = -1;
    other.width = -1;
    return (*this);
}

void print_matrix(Matrix matrix)
{
    for(int i = 0; i < matrix.height; i ++)
    {
        for(int j = 0; j < matrix.width; j ++)
        {
            std::cout << std::setw(4) << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

Matrix Matrix::slice(int begRow, int endRow, int begCol, int endCol) {
    
    Matrix res(endCol - begCol, endRow - begRow);

    for (int i = begRow; i < endRow; ++i) {

        for (int j = begCol; j < endCol; ++j)
            res[i - begRow][j - begCol] = (*this)[i][j];
    }

    return res;
}

Matrix Matrix::slice(int begRow, int endRow, int begCol, int endCol) const {
    Matrix res(endCol - begCol, endRow - begRow);

    for (int i = begRow; i < endRow; ++i) {

        for (int j = begCol; j < endCol; ++j)
            res[i - begRow][j - begCol] = (*this)[i][j];
    }

    return res;
}

Matrix matrix_merge(const Matrix &a11, const Matrix &a12, const Matrix &a21, const Matrix &a22)
{
    size_t n = a11.height;
    size_t rows = n * 2;

    Matrix res(rows, rows);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            res[i][j] = a11[i][j];
            res[i][j + n] = a12[i][j];
            res[i + n][j] = a21[i][j];
            res[i + n][j + n] = a22[i][j];
        }
    }
    return res;
}