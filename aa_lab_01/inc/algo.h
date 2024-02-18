#pragma once

#include "../inc/general.h"
#include <string>
#include <cstring>

using namespace std;

template <typename T>
concept IsStr = 
  requires(T m) {
    m.c_str();
	m.length();
};

int recurs_dam_lev_temp(const char*str1, const char*str2, int length1, int length2);
int matrix_lev_temp(const char* str1,const char* str2, int width, int height);
int matrix_dam_lev_temp(const char* str1,const char* str2, int width, int height);
int hash_dam_lev_temp(const char*str1, const char*str2, int ind1, int ind2, int **memo);

template <IsStr T>
int matrix_lev(const T& str1,const T& str2)
{
    return matrix_lev_temp(str1.c_str(), str2.c_str(), str1.length(), str2.length());
}

template <IsStr T>
int recurs_dam_lev(const T& str1,const T& str2)
{
    return recurs_dam_lev_temp(str1.c_str(), str2.c_str(), str1.length(), str2.length());
}

template <IsStr T>
int matrix_dam_lev(const T& str1,const T& str2)
{
    return matrix_dam_lev_temp(str1.c_str(), str2.c_str(), str1.length(), str2.length());
}

template <IsStr T>
int hash_dam_lev(const T& str1,const T& str2)
{

    int len1 = str1.length();
    int len2 = str2.length();

    int** memo = new int*[len2 + 1];
    for (int i = 0; i < len2 + 1; i++)
        memo[i] = new int[len1 + 1];

    if (!memo)
        return -1;

    for (int i = 0; i < len2 + 1; i++)
    {
        for (int j = 0; j < len1 + 1; j++)
        {
                memo[i][j] = -1;
        }
    }

    
    int res = hash_dam_lev_temp(str1.c_str(), str2.c_str(), len1, len2, memo);
    
    for (int i = 0; i < len2 + 1; ++i)
        delete[] memo[i];    
    delete[] memo;
    return res;


}