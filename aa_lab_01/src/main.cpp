#include <iostream>
#include <string>
#include <chrono>
#include "../inc/algo.h"
#include "../inc/measurement.h"
#define REP_COUNT 100
#include <fstream>
#include <time.h>
#include "../inc/general.h"


using namespace std;

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void calc_prog()
{
    ofstream f;
    f.open ("the_data.csv");

    for(int c_count = 1; c_count <= 10; c_count ++)
    {
        long double total_t[4] = {0, 0, 0, 0};     

        int (*funcs[2]) (const string&, const string&) = {hash_dam_lev<string>, recurs_dam_lev<string>}; //{matrix_dam_lev<string>, matrix_lev<string>}; //

        for(int j = 0; j < 2; j ++)
        {
            for(int i = 0; i < REP_COUNT; i ++)
            {
                string str1 = gen_random(c_count);
                string str2 = gen_random(c_count);

                total_t[j] += calc_time(funcs[j], str1, str2);
            }


            total_t[j] *= 1000;
            total_t[j] /= REP_COUNT;


        }
        std::cout << "Char: " << c_count << "\n";
        f << c_count << " " << total_t[0] << " " << total_t[1] << "\n";
    }
    f.close();
    
    std::cout << "Done\n";
}

int get_two_strings(string& str1, string& str2)
{
    std::cout << "Введите первую строку:\n";
    std::cin >> str1;

    std::cout << "Введите вторую строку:\n";
    std::cin >> str2;

    if(str1.size() > 0 && str2.size() > 0)
        return 0;
    return 1;
}

int main(void)
{
    srand(timeSinceEpochMillisec());

    if(MODE == MODE_CALC)
    {
        calc_prog();
        return 0;
    }

    if(MODE == MODE_INTERACTIVE)
    {
        int option = -2;
        string str1, str2;
        while(option != 0)
        {
            std::cout << "1 - Левенштейн с использованием матрицы\n";  
            std::cout << "2 - Дамерау - Левенштейн с использованием матрицы\n";   
            std::cout << "3 - Рекурсивный алгоритм расстояния Дамерау - Левенштейн\n";    
            std::cout << "4 - Дамерау - Левенштейн с использованием хэш таблицы\n";                

            std::cout << "0 - Выход\n";

            std::cin >> option;

            if(std::cin)
            {
                if(option == 1)
                {
                    int rc = get_two_strings(str1, str2);
                    if(rc == 0)
                    {
                        std::cout << "Матрица: \n";
                        int diff = matrix_lev(str1, str2);
                        std::cout << "Расстояние Левенштейна: " << diff << "\n";
                    }
                }
                else if(option == 2)
                {
                    int rc = get_two_strings(str1, str2);
                    if(rc == 0)
                    {
                        std::cout << "Матрица: \n";
                        int diff = matrix_dam_lev(str1, str2);
                        std::cout << "Расстояние Дамерау - Левенштейна: " << diff << "\n";
                    }
                }
                else if(option == 3)
                {
                    int rc = get_two_strings(str1, str2);
                    if(rc == 0)
                    {

                        int diff = recurs_dam_lev(str1, str2);
                        std::cout << "Расстояние Дамерау - Левенштейна: " << diff << "\n";
                    }
                }  
                else if(option == 4)
                {
                    int rc = get_two_strings(str1, str2);
                    if(rc == 0)
                    {

                        int diff = hash_dam_lev(str1, str2);
                        std::cout << "Расстояние Дамерау - Левенштейна: " << diff << "\n";
                    }
                }                              
            }
            else
            {
                option = -1;
                std::cout << "Ошибка ввода\n";
                std::cin.clear();
                std::cin.ignore(32767,'\n');
            }
        }
    }
    return 0;
}