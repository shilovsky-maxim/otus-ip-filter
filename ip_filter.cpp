#include <cassert>
#include <cstdlib>
#include <algorithm>

#include "helper_library.h"

/* [[maybe_unused]] attribute is used to make the code more C++14. 
   Alternatively, parameter names could be omitted. */
int main([[maybe_unused]]int argc, [[maybe_unused]]char const *argv[])
{
    using namespace helper;
    try
    {
        IPAddresses ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.front(), '.'));
        }

        ip_pool = reverse_sort(ip_pool);

        print_ip_pool(std::cout, ip_pool);
        print_ip_pool(std::cout, filter(ip_pool, 1));
        print_ip_pool(std::cout, filter(ip_pool, 46, 70));
        print_ip_pool(std::cout, filter_any(ip_pool, 46));
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}