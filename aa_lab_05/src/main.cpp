#include <iostream>
#include <string>
#include <chrono>
#include "../inc/algo.h"
#include "../inc/measurement.h"
#define REP_COUNT 50
#include <fstream>
#include <time.h>
#include "../inc/general.h"
#include <iterator>
#include <cstdlib>
#include <istream>
#include "../inc/csr_matrix.h"

using namespace std;

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
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
        //calc_prog();
        return 0;
    }

    if(MODE == MODE_INTERACTIVE)
    {
        int option = -2;
        while(option != 0)
        {
            std::cout << "1 - Линейная очередь\n";  
            std::cout << "2 - Конвеерная очередь\n";  
            std::cout << "3 - Выполнить замеры\n";  
                
            std::cout << "0 - Выход\n";

            std::cin >> option;

            if(std::cin)
            {
                if(option == 1)
                {
                    int size = 0, count = 0;
                    std::cout << "\nРазмер: ";
                    std::cin >> size;
                    std::cout << "Количество: ";
                    std::cin >> count;
                    parseLinear(count, size, true);

                }
                else if(option == 2)
                {
                    int size = 0, count = 0;
                    std::cout << "\nРазмер: ";
                    std::cin >> size;
                    std::cout << "Количество: ";
                    std::cin >> count;
                    parseParallel(count, size, true);
                }
                else if(option == 3)
                {
                    timeMessage();
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