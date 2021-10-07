#define BOOST_TEST_MODULE reverse_sort_test

#include "helper_library.h"

#include <boost/test/unit_test.hpp>

#include <sstream>
#include <iostream>

BOOST_AUTO_TEST_SUITE(reverse_sort_test)

BOOST_AUTO_TEST_CASE(reverse_sort_test) 
{
    using namespace helper;

    IPAddresses ip_pool;
    ip_pool.push_back(split("1.1.1.1", '.'));
    ip_pool.push_back(split("1.2.1.1", '.'));
    ip_pool.push_back(split("1.10.1.1", '.'));

    ip_pool = reverse_sort(ip_pool);

    auto ip_to_str = [](const auto& ip)
    {
        std::stringstream out;
        output_ip_address(out, ip, false);
        return out.str();
    };

    BOOST_CHECK_EQUAL(ip_to_str(ip_pool.at(0)), "1.10.1.1");
    BOOST_CHECK_EQUAL(ip_to_str(ip_pool.at(1)), "1.2.1.1");
    BOOST_CHECK_EQUAL(ip_to_str(ip_pool.at(2)), "1.1.1.1");
}

BOOST_AUTO_TEST_SUITE_END()