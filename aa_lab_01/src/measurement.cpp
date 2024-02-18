#include <string>

using namespace std;

string gen_random(const int len) {
    string al = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string tmp_s = "";
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += al[rand() % (al.length() - 1)];
    }

    return tmp_s;
}