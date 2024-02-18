#include "../inc/algo.h"

template <typename T>
static T min(T x, T y, T z)
{
    return std::min(x, std::min(y, z));
}

int matrix_lev_temp(const char* str1,const char* str2, int width, int height)
{

    int** mat = new int*[height + 1];
    for (int i = 0; i < height + 1; ++i)
        mat[i] = new int[width + 1];


    for(int i = 0; i <= width; i ++)
    {
        mat[0][i] = i;
    }
    for(int i = 1; i <= height; i ++)
    {
        mat[i][0] = i;
    }


    for (int i = 1; i <= height; ++i)
    {
        for (int j = 1; j <= width; ++j)
        {        
            int cost = (str1[j - 1] == str2[i - 1]) ? 0 : 1;

            mat[i][j] = min(
                mat[i - 1][j] + 1,
                mat[i][j - 1] + 1,
                mat[i - 1][j - 1] + cost);
        }
    }

    if(MODE == MODE_INTERACTIVE)
        print_matrix(mat, width + 1, height + 1);

    int res = mat[height][width];

    for (int i = 0; i < height + 1; ++i)
        delete[] mat[i];    
    delete[] mat;

    return res;
}

int recurs_dam_lev_temp(const char*str1, const char*str2, int length1, int length2)
{
    if (length1 == 0)
        return length2;
    if (length2 == 0)
        return length1;

    int change = 0;
    int res = 0;
    if (str1[length1 - 1] != str2[length2 - 1])
        change = 1;

    res = min(recurs_dam_lev_temp(str1, str2, length1, length2 - 1) + 1,
              min(recurs_dam_lev_temp(str1, str2, length1 - 1, length2) + 1,
                  recurs_dam_lev_temp(str1, str2, length1 - 1, length2 - 1) + change));

    if (length1 > 1 && length2 > 1 &&
        str1[length1 - 1] == str2[length2 - 2] &&
        str1[length1 - 2] == str2[length2 - 1])
        res = min(res, recurs_dam_lev_temp(str1, str2, length1 - 2, length2 - 2) + 1);
    return res;    
}

int matrix_dam_lev_temp(const char* str1,const char* str2, int width, int height)
{
    int diff;

    int** matrix = new int*[height];
    for (int i = 0; i < height; ++i)
        matrix[i] = new int[width];


    for(int i = 0; i < height; i ++)
    {
        for(int j = 0; j < width; j ++)
        {
            matrix[i][j] = 0;  
        }
    }  

    for(int i = 0; i < width; i ++)
    {
        matrix[0][i] = i;
    }
    for(int i = 1; i < height; i ++)
    {
        matrix[i][0] = i;
    }

    for(int i = 1; i < height; i ++)
    {
            int minval = min(matrix[i][0], matrix[i - 1][1]);
            minval ++;
            minval = min(minval, matrix[i - 1][0] + int(str1[1] != str2[i]));
            matrix[i][1] = minval;
    }

    for(int j = 1; j < width; j ++)
    {
            int minval = min(matrix[1][j - 1], matrix[0][j]);
            minval ++;
            minval = min(minval, matrix[0][j - 1] + int(str1[j] != str2[1]));
            matrix[1][j] = minval;
    }

    for(int i = 2; i < height; i ++)
    {
        for(int j = 2; j < width; j ++)
        {
            int minval = min(matrix[i][j - 1], matrix[i - 1][j]);
            minval ++;
            minval = min(minval, matrix[i - 1][j - 1] + int(str1[j] != str2[i]));
            if(str1[j] == str2[i - 1] && str1[j - 1] == str2[i])
            {
                minval = min(minval, matrix[i - 2][j - 2] + 1);
            }
            matrix[i][j] = minval;  
        }
    }  

    if(MODE == MODE_INTERACTIVE)
        print_matrix(matrix, width, height);  

    diff = matrix[height - 1][width - 1];

    for (int i = 0; i < height; ++i)
        delete[] matrix[i];    
    delete[] matrix;

    return diff;
}

int hash_dam_lev_temp(const char*str1, const char*str2, int ind1, int ind2, int **memo)
{

    if (ind1 == 0)
        return ind2;

    if (ind2 == 0)
        return ind1;

    if (memo[ind2][ind1] != -1)
        return memo[ind2][ind1];
    
    int cost = (str1[ind1 - 1] == str2[ind2 - 1]) ? 0 : 1;

    int res = min(
        hash_dam_lev_temp(str1, str2, ind1, ind2 - 1, memo) + 1,
        hash_dam_lev_temp(str1, str2, ind1 - 1, ind2, memo) + 1,
        hash_dam_lev_temp(str1, str2, ind1 - 1, ind2 - 1, memo) + cost
    );

    if (ind1 > 1 && ind2 > 1 && str1[ind1 - 1] == str2[ind2 - 2] && str1[ind1 - 2] == str2[ind2 - 1])
        res = std::min(res, hash_dam_lev_temp(str1, str2, ind1 - 2, ind2 - 2, memo) + 1);

    memo[ind2][ind1] = res;
    return res;

}