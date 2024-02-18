#include <string>
#include "../inc/general.h"
using namespace std;

Matrix gen_random(const int len) {
    Matrix tmp_s(len, len);

    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j++)
        {
            tmp_s[i][j] = rand() % 100;
        }        
    }
    return tmp_s;
}

double calc_time(Matrix (*func) (const Matrix&, const Matrix&), Matrix& str1, Matrix& str2)
{
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    func(str1, str2);
    end_t = clock();
    total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    return total_t;
}