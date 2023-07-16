#include <cstdlib>
#include <ctime>
#include <string>

std::string random_string(int length, int seed = -1)
{

    static const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_- !?";
    std::string result;
    result.reserve(length);

    (seed < 0) ? srand(time(0)) : srand(seed);

    for (int i = 0; i < length; ++i)
    {
        result.push_back(charset[rand() % charset.length()]);
    }

    return result;
}