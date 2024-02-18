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

    for(int c_count = 1; c_count <= 128; c_count *= 2)
    {
        long double total_t[4] = {0, 0, 0, 0};     

        Matrix (*funcs[4]) (const Matrix&, const Matrix&) = {mult_vinograd, mult_vinograd_opt, mult_classic, mult_strassen}; //{matrix_dam_lev<string>, matrix_lev<string>}; //

        for(int j = 0; j < 4; j ++)
        {
            for(int i = 0; i < REP_COUNT; i ++)
            {
                Matrix str1 = gen_random(c_count);
                Matrix str2 = gen_random(c_count);

                total_t[j] += calc_time(funcs[j], str1, str2);
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

int get_dims(const char* filename, int &h, int &w)
{ 
	string line;
	
	ifstream mFile (filename);   
	w = -1;
	if(mFile.is_open()) 
	{
		while(mFile.peek()!=EOF)
		{
			getline(mFile, line);
            int ww = count(line.begin(), line.end(), ' ') + 1;
            if(w != -1 && w != ww)
            {
                mFile.close();
                h = -1;
                w = -1;
                return -1;
            }
            if(w == -1)
                w = ww;
			h++;
		}
		mFile.close();
	}
	else
    {
		h = -1;
        w = -1;
        return -1;
    }
 
	return 0;
}

int file_to_mat(const char* filename, Matrix& mat)
{
    int width = 0;
    int height = 0;
    int rc = get_dims(filename, height, width);

    if(rc != 0)
        return 1;

    ifstream file(filename);
    string line;


    int cur_w = 0;
    int cur_h = 0;
    int curElem;
    mat = Matrix(width, height, 0);
    file.clear();
    file.seekg(0);
    if (file.is_open() && file.good()) {
        while (getline(file, line)) {
            stringstream str_strm;
            str_strm << line;
            string temp_str;
            int temp_int;            
            while(!str_strm.eof()) {
                str_strm >> temp_str;
                if(stringstream(temp_str) >> temp_int) {
                    mat[cur_h][cur_w] = temp_int;
                    cur_w ++;
                }
                temp_str = "";
            }
            cur_h ++;
            cur_w = 0;
        }
    }

    return 0;

}

int read_two_matrices(Matrix& mat1, Matrix& mat2)
{
    int rc = file_to_mat("./mat1.txt", mat1);  
    if(rc == 0)
        rc = file_to_mat("./mat2.txt", mat2);

    return rc;
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
        Matrix mat1, mat2;
        while(option != 0)
        {
            std::cout << "1 - Классический алгоритм умножения\n";  
            std::cout << "2 - Алгоритм Винограда\n";   
            std::cout << "3 - Оптимизированный алгоритм Винограда\n";    
            std::cout << "4 - Алгоритм Штрассена\n";                

            std::cout << "0 - Выход\n";

            std::cin >> option;

            if(std::cin)
            {
                if(option == 1)
                {

                    int rc = read_two_matrices(mat1, mat2);
                    if(rc == 0)
                    {
                        Matrix mat3 = mult_classic(mat1, mat2);
                        std::cout << "Результат: " << "\n";
                        print_matrix(mat3);
                    }
                    else
                    {
                        cout << "Ошибка ввода\n";
                    }
                }
                else if(option == 2)
                {
                    int rc = read_two_matrices(mat1, mat2);
                    if(rc == 0)
                    {
                        Matrix mat3 = mult_vinograd(mat1, mat2);
                        std::cout << "Результат: " << "\n";
                        print_matrix(mat3);
                    }
                    else
                    {
                        cout << "Ошибка ввода\n";
                    }
                }
                else if(option == 3)
                {
                    int rc = read_two_matrices(mat1, mat2);
                    if(rc == 0)
                    {
                        Matrix mat3 = mult_vinograd_opt(mat1, mat2);
                        std::cout << "Результат: " << "\n";
                        print_matrix(mat3);
                    }
                    else
                    {
                        cout << "Ошибка ввода\n";
                    }
                }  
                else if(option == 4)
                {
                    int rc = read_two_matrices(mat1, mat2);
                    if(rc == 0)
                    {
                        Matrix mat3 = mult_strassen(mat1, mat2);
                        std::cout << "Результат: " << "\n";
                        print_matrix(mat3);
                    }
                    else
                    {
                        cout << "Ошибка ввода\n";
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