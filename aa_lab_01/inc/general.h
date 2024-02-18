#pragma once

#include <iostream>

#define MODE_INTERACTIVE 0
#define MODE_CALC 1

#define MODE MODE_CALC

template <typename T>
void print_matrix(T** matrix, int w, int h)
{
    for(int i = 0; i < h; i ++)
    {
        for(int j = 0; j < w; j ++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}