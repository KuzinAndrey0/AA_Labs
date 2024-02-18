#include "../inc/csr_matrix.h"

matrixT CSRMatrix::convertToNormalMatrix() {
    matrixT normalMatrix(num_rows, std::vector<int>(num_cols, 0));
    int k = 0;
    for (int i = 0; i < num_rows; ++i) {
        for (int j = row_pointers[i]; j < row_pointers[i + 1]; ++j) {
            int col = column_indices[j];
            normalMatrix[i][col] = values[j];
            k++;
        }
    }
    return normalMatrix;
}

CSRMatrix::CSRMatrix(int rows, int cols) : num_rows(rows), num_cols(cols) {
    for (int i = 0; i <= num_rows; ++i) {
        row_pointers.push_back(0);
    }
}

CSRMatrix::CSRMatrix() {
    num_cols = 0;
    num_rows = 0;
}

void CSRMatrix::printMatrix() {
    int k = 0;
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            if (j == column_indices[k] && k < column_indices.size()) {
                std::cout << values[k] << " ";
                k++;
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
}

void CSRMatrix::printMatrix2() {
    cout << "Values: ";
    for(int i = 0; i < values.size(); i ++)
    {
        cout << values[i] << " ";
    }
    cout << "\nColumn indexes: ";
    for(int i = 0; i < column_indices.size(); i ++)
    {
        cout << column_indices[i] << " ";
    }
    cout << "\nRow pointers: ";
    for(int i = 0; i < row_pointers.size(); i ++)
    {
        cout << row_pointers[i] << " ";
    }
    cout << "\n";

}

void CSRMatrix::addValue(int row, int col, int value) {
    values.push_back(value);
    column_indices.push_back(col);
    for (int i = row + 1; i <= num_rows; ++i) {
        row_pointers[i]++;
    }
}


void printMatrix(const matrixT& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

matrixT readNormalMatrixFromStdin() {
    int size_rows, size_cols;
    cout << "Введите размер матрицы: \n";
    cin >> size_rows;
    size_cols = size_rows;

    cout << "Введите элементы матрицы: \n";

    matrixT normalMatrix(size_rows, vector<int>(size_cols));

    for (int i = 0; i < size_rows; i++) {
        for (int j = 0; j < size_cols; j++) {
            cin >> normalMatrix[i][j];
        }
    }

    return normalMatrix;
}


//void (*func)(matrix_t &)

void convertToCSRNew(matrix_t &matrix)
{
    int rows = matrix.data.size();
    int cols = matrix.data[0].size();
    matrix.num_rows = rows;
    matrix.num_cols = cols;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix.data[i][j] != 0) {
                matrix.values.push_back(matrix.data[i][j]);
                matrix.column_indices.push_back(j);
                for (int i = i + 1; i <= matrix.num_rows; ++i) {
                    matrix.row_pointers[i]++;
                }
            }
        }
    }


}
CSRMatrix convertToCSR(const matrixT& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    CSRMatrix csrMatrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] != 0) {
                csrMatrix.addValue(i, j, matrix[i][j]);
            }
        }
    }
    return csrMatrix;
}

CSRMatrix removeFirstRowAndColumn(const CSRMatrix& matrix, int i) {

    CSRMatrix sparseMatrix = matrix;
    int idx = i;

    int cnt = sparseMatrix.row_pointers[idx + 1] - sparseMatrix.row_pointers[idx];

    for(int j = sparseMatrix.row_pointers[idx]; j < sparseMatrix.row_pointers[idx + 1]; j ++)
    {
        sparseMatrix.values.erase(sparseMatrix.values.begin() + sparseMatrix.row_pointers[idx]);
        sparseMatrix.column_indices.erase(sparseMatrix.column_indices.begin() + sparseMatrix.row_pointers[idx]);
    }

    sparseMatrix.row_pointers.erase(sparseMatrix.row_pointers.begin() + idx);

    for(int j = idx; j < sparseMatrix.row_pointers.size(); j ++)
    {
        sparseMatrix.row_pointers[j] -= cnt;
    }

    for(int i = 1; i < sparseMatrix.row_pointers.size(); i ++)
    {
        for(int j = sparseMatrix.row_pointers[i - 1]; j < sparseMatrix.row_pointers[i]; j ++)
        {
            if(sparseMatrix.column_indices[j] == (sparseMatrix.num_cols - 1))
            {
                sparseMatrix.values.erase(sparseMatrix.values.begin() + j);
                sparseMatrix.column_indices.erase(sparseMatrix.column_indices.begin() + j);
                for(int k = i; k < sparseMatrix.row_pointers.size(); k ++)
                {
                    sparseMatrix.row_pointers[k] --;
                }
            }
        }
    }

    sparseMatrix.num_rows --;
    sparseMatrix.num_cols --;

    return sparseMatrix;

}

int CSRElem(const CSRMatrix& matrix, int row, int col) {
    int rowStart = matrix.row_pointers[row];
    int rowEnd = matrix.row_pointers[row + 1];

    for (int i = rowStart; i < rowEnd; i++) {
        if (matrix.column_indices[i] == col) {
            return matrix.values[i];
        }
    }
    return 0; 
}

// void generateMatrix(size_t size, matrixT &matrix)
// {
//     for(int i = 0; i < size; i ++)
//     {
//         matrix.push_back(vector({rand() % 10}));
//         for(int j = 1; j < size; j ++)
//         {
//             matrix[i].push_back(rand() % 10);
//         }
//     }
// }

matrix_t generateMatrix(size_t size)
{
    std::vector<std::vector<int> > tmpData;
    tmpData.resize(size);

    for (size_t i = 0; i < size; i++) {
        tmpData[i].resize(size);
    }

    matrix_t matrix;
    matrix.size = size;
    matrix.data = tmpData;

    for (size_t i = 0; i < matrix.size; i++) {
        for (size_t j = 0; j < matrix.size; j++) {
            matrix.data[i][j] = rand() % 10 + 1;
        }
    }
    return matrix;
}


int calcDeterm(CSRMatrix &mat, int size)
{
    if(size == 1)                                  
        return CSRElem(mat, 0, 0);                 
    if(size == 2)                              
        return CSRElem(mat, 0, 0) * CSRElem(mat, 1, 1) - CSRElem(mat, 0, 1) * CSRElem(mat, 1, 0);
    int sign = 1, det_sum = 0;                    
    for(int i = 0; i < size; i ++)                 
    {
        CSRMatrix minMat = removeFirstRowAndColumn(mat, i);
        det_sum += sign * CSRElem(mat, i, size - 1) * calcDeterm(minMat, size - 1);                               
        sign *= -1;                                 

    }
    return det_sum;                        
}

int calc_determ(matrixT &mat, int size)
{
    if(size == 1)                                 
        return mat[0][0];                         
    if(size == 2)                                 
        return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];             
    int sign = 1, det_sum = 0;                 
    for(int i = 0; i < size; i ++)                 
    {
        matrixT minMat(size - 1);                 
        for(int j = 0; j < i; j ++)            
            for(int k = 1; k < size; k ++)        
                minMat[j].push_back(mat[j][k]); 
        for(int j = i + 1; j < size; j ++)         
            for(int k = 1; k < size; k ++) 
                minMat[j - 1].push_back(mat[j][k]); 
        det_sum += sign * mat[i][0] * calc_determ(minMat, size - 1);                                
        sign *= -1;       

    }
    return det_sum;

}

void calcDetermNew(matrix_t &matrix)
{
    int d = calc_determ(matrix.data, matrix.size);

    matrix.determ = d;
}


string makeDump(CSRMatrix &mat, int &det)
{
    string str;

    str += "Values: ";
    for(int i = 0; i < mat.values.size(); i ++)
    {
        str += to_string(mat.values[i]);
        str += " ";
    }
    str += "\nColumn indexes: ";
    for(int i = 0; i < mat.column_indices.size(); i ++)
    {
        str += to_string(mat.column_indices[i]);
        str += " ";
    }
    str += "\nRow pointers: ";
    for(int i = 0; i < mat.row_pointers.size(); i ++)
    {
        str += to_string(mat.row_pointers[i]);
        str += " ";
    }
    str += "\nDeterminant: ";
    str += to_string(det);
    str += "\n";

    return str;
}

void makeDumpNew(matrix_t &matrix)
{
    string str;

    str += "Values: ";
    for(int i = 0; i < matrix.values.size(); i ++)
    {
        str += to_string(matrix.values[i]);
        str += " ";
    }
    str += "\nColumn indexes: ";
    for(int i = 0; i < matrix.column_indices.size(); i ++)
    {
        str += to_string(matrix.column_indices[i]);
        str += " ";
    }
    str += "\nRow pointers: ";
    for(int i = 0; i < matrix.row_pointers.size(); i ++)
    {
        str += to_string(matrix.row_pointers[i]);
        str += " ";
    }
    str += "\nDeterminant: ";
    str += to_string(matrix.determ);
    str += "\n";

    matrix.dump = str;
}