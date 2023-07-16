#include <stdio.h>
#include <iostream>
#include <map>
#include "arithmetic.cpp"

std::string replace_all(std::string subject, const std::string &search,
                        const std::string &replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

int main()
{
    std::string input;
    std::map<std::string, double> vars;
    bool set = false;
    std::string var;
    while (true)
    {
        std::cout << ">>> ";
        std::getline(std::cin, input);
        if (input.rfind("set", 0) != std::string::npos)
        {
            try
            {
                var = input.substr(4, input.size());
                std::cout << "Set: " << var << std::endl;
                set = true;
            }
            catch (const std::out_of_range &e)
            {
                std::cout << "Error: No Variable Name. `set <varname>`" << std::endl;
            }
            continue;
        }
        try
        {
            for (const auto &[key, value] : vars) // c++17 iterator
            {
                input = replace_all(input, key, std::to_string(value));
            }
            std::string pf = infix_to_postfix(input);
            std::cout << "PF: " << pf << std::endl;
            float res = evaluate_infix(input);
            std::cout << "R: " << res << std::endl;
            if (set)
            {
                vars[var] = res;
                set = false;
            }
        }
        catch (const std::invalid_argument &e)
        {
            if (input.rfind("q", 0) != std::string::npos)
            {
                std::cout << "Quitting..." << std::endl;
                break;
            }
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}