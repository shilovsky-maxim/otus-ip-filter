#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

namespace helper
{
    using VectorOfStrings =std::vector<std::string>;
    using IPAddress = VectorOfStrings;
    using IPAddresses = std::vector<IPAddress>;
    using IPPartComparator = std::function<bool(const std::string&, const std::string&)>;

    VectorOfStrings split(const std::string &str, char delim);
    std::pair<int, bool> convert_to_int(const std::string& str);
    bool lex_compare_strings(const std::string& first, const std::string& second);
    bool lex_compare_ip(const IPAddress& first, const IPAddress& second, IPPartComparator comparator);
    void output_ip_address(std::ostream& out, const IPAddress& ip, bool addNewLine = true);
    void print_ip_pool(std::ostream& out, const IPAddresses& ip_pool);

    IPAddresses reverse_sort(IPAddresses ip_pool);
    IPAddresses filter(IPAddresses ip_pool, int first_byte, int second_byte = -1);
    IPAddresses filter_any(IPAddresses ip_pool, int value);

}
