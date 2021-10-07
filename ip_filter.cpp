#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using VectorOfStrings = std::vector<std::string>;
using VectorOfVectorOfStrings = std::vector<VectorOfStrings>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
VectorOfStrings split(const std::string &str, char d)
{
    VectorOfStrings r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::pair<int, bool> convert_to_int(const std::string& str)
{
    try
    {
       return std::make_pair(std::stoi(str), true);
    }
    catch(const std::invalid_argument&)
    {
    }
    catch (const std::out_of_range&)
    {
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return std::make_pair(-1, false);   
}

auto compare_strings(const std::string& first, const std::string& second)
{
    // If both strings can be converted to numbers, compare them as numbers.
    // Otherwise, compare them as strings
    auto num1 = convert_to_int(first);
    auto num2 = convert_to_int(second);
    if (num1.second && num2.second)
        return num1.first > num2.first;
    else
        return first > second;
}

void output_ip_address(const VectorOfStrings& ip)
{
    bool is_first =  true;
    for(const auto& ip_part : ip)
    {
        if (!is_first)
        {
            std::cout << ".";
        }
        is_first = false;
        std::cout << ip_part;
    }
    std::cout << std::endl;
}

void print_ip_pool(const VectorOfVectorOfStrings& ip_pool)
{
    for(const auto& ip : ip_pool)
    {
        output_ip_address(ip);
    }
}

/* [[maybe_unused]] attribute is used to make the code more C++14. 
   Alternatively, parameter names could be omitted. */
int main([[maybe_unused]]int argc, [[maybe_unused]]char const *argv[])
{
    try
    {
        std::vector<VectorOfStrings> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.front(), '.'));
        }

        auto comparator = [](const auto& first, const auto& second)
        {
            return std::lexicographical_compare(first.begin(), first.end(), second.begin(), second.end(), 
                                                [](const auto& f, const auto& s)
                                                {
                                                    return compare_strings(f, s);
                                                });
        };
        std::sort(ip_pool.begin(), ip_pool.end(), comparator);

        // It captures ip_pool by copy to be able to perform destructive operations on it
        auto filter = [](VectorOfVectorOfStrings ip_pool, int first_byte, int second_byte = -1)
        {
            // We need to remove unsuitable ip addresses, so the condition is negated
            auto filter_condition = [first_byte, second_byte](const auto& ip)
            {
                return (convert_to_int(ip.at(0)).first != first_byte) || 
                       (second_byte >= 0 && convert_to_int(ip.at(1)).first != second_byte);
            };
            // Not really effective but uses std algorithms by max
            ip_pool.erase(std::remove_if(ip_pool.begin(), ip_pool.end(), filter_condition), ip_pool.end());
            return ip_pool;
        };

        auto filter_any = [](VectorOfVectorOfStrings ip_pool, int value) mutable
        {
             // We need to remove unsuitable ip addresses, so the condition is negated
            auto filter_condition = [value](const auto& ip)
            {
                return std::all_of(ip.begin(), ip.end(), [value](const auto& ip_part)
                {
                    return convert_to_int(ip_part).first != value;
                });
            };
            // Not really effective but uses std algorithms by max
            ip_pool.erase(std::remove_if(ip_pool.begin(), ip_pool.end(), filter_condition), ip_pool.end());
            return ip_pool;   
        };

        print_ip_pool(ip_pool);
        print_ip_pool(filter(ip_pool, 1));
        print_ip_pool(filter(ip_pool, 46, 70));
        print_ip_pool(filter_any(ip_pool, 46));
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}