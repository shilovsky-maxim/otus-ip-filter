#include "helper_library.h"

#include <algorithm>

namespace helper
{
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

    bool lex_compare_strings(const std::string& first, const std::string& second)
    {
        // If both strings can be converted to numbers, compare them as numbers.
        // Otherwise, compare them as strings
        auto num1 = convert_to_int(first);
        auto num2 = convert_to_int(second);
        if (num1.second && num2.second)
            return num1.first < num2.first;
        else
            return first < second;
    }

    bool lex_compare_ip(const IPAddress& first, const IPAddress& second, IPPartComparator comparator)
    {
        return std::lexicographical_compare(first.begin(), first.end(), second.begin(), second.end(), 
                                            comparator);
    }

    void output_ip_address(std::ostream& out, const IPAddress& ip)
    {
        bool is_first =  true;
        for(const auto& ip_part : ip)
        {
            if (!is_first)
            {
                out << ".";
            }
            is_first = false;
            out << ip_part;
        }
        out << std::endl;
    }

    void print_ip_pool(std::ostream& out, const IPAddresses& ip_pool)
    {
        for(const auto& ip : ip_pool)
        {
            output_ip_address(out, ip);
        }
    }

    IPAddresses filter(IPAddresses ip_pool, int first_byte, int second_byte)
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
    }

    IPAddresses filter_any(IPAddresses ip_pool, int value)
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
    }
}
