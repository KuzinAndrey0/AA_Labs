#include <iostream>
#include <string>
#include <chrono>
#include "../inc/algo.h"
#include "../inc/measurement.h"
#define REP_COUNT 1000
#include <fstream>
#include <time.h>
#include "../inc/general.h"
#include <iterator>
#include <cstdlib>
#include <istream>

using namespace std;

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void calc_prog()
{
    ofstream f;
    f.open ("the_data.csv");

    for(int c_count = 1; c_count <= 500; c_count += 10)
    {
        long double total_t[4] = {0, 0, 0, 0};     

        void (*funcs[3]) (vector<int>&) = {sort_smooth, sort_shaker, sort_shell};

        for(int j = 0; j < 3; j ++)
        {
            for(int i = 0; i < REP_COUNT; i ++)
            {
                vector<int> arr1;
                gen_random(arr1, c_count);

                total_t[j] += calc_time(funcs[j], arr1);

            }


            total_t[j] *= 1000;
            total_t[j] /= REP_COUNT;


        }
        std::cout << "Char: " << c_count << "\n";
        f << c_count << " " << total_t[0] << " " << total_t[1] << " " <<  total_t[2] << "\n";
    }
    f.close();
    
    std::cout << "Done\n";
}

void readVector(vector<int> &vec)
{
    std::cin.clear();
    std::cin.ignore(32767,'\n');
    std::string line;
    getline(std::cin, line);
    int enterNumber;
    std::istringstream iss(line);
    while (iss >> enterNumber)
    {
        vec.push_back(enterNumber);
    }

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
        while(option != 0)
        {
            std::cout << "1 - Плавная сортировка\n";  
            std::cout << "2 - Сортировка перемешиванием\n";   
            std::cout << "3 - Сортировка Шелла\n";                

            std::cout << "0 - Выход\n";

            std::cin >> option;

            if(std::cin)
            {
                if(option == 1)
                {
                    vector<int> myVector;
                    readVector(myVector);
                    sort_smooth(myVector);
                    cout << "Отсортированный массив:\n";
                    for(int i = 0; i < myVector.size(); i ++)
                        std::cout << myVector[i] << " ";
                    std::cout << "\n";
                }
                else if(option == 2)
                {
                    vector<int> myVector;
                    readVector(myVector);
                    sort_shaker(myVector);
                    cout << "Отсортированный массив:\n";
                    for(int i = 0; i < myVector.size(); i ++)
                        std::cout << myVector[i] << " ";
                    std::cout << "\n";
                }
                else if(option == 3)
                {
                    vector<int> myVector;
                    readVector(myVector);
                    sort_shell(myVector);
                    cout << "Отсортированный массив:\n";
                    for(int i = 0; i < myVector.size(); i ++)
                        std::cout << myVector[i] << " ";
                    std::cout << "\n";
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