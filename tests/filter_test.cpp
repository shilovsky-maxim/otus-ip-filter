#define BOOST_TEST_MODULE filter_test

#include "helper_library.h"

#include <boost/test/unit_test.hpp>

#include <sstream>
#include <iostream>

BOOST_AUTO_TEST_SUITE(filter_test)

BOOST_AUTO_TEST_CASE(filter_test) 
{
    using namespace helper;

    IPAddresses ip_pool;
    ip_pool.push_back(split("46.70.113.73", '.'));
    ip_pool.push_back(split("46.146.29.220", '.'));
    ip_pool.push_back(split("46.70.147.26", '.'));
    ip_pool.push_back(split("1.1.70.46", '.'));

    auto ip_to_str = [](const auto& ip)
    {
        std::stringstream out;
        output_ip_address(out, ip, false);
        return out.str();
    };

    auto starts_with_46 = filter(ip_pool, 46);
    BOOST_CHECK_EQUAL(starts_with_46.size(), 3);
    BOOST_CHECK_EQUAL(ip_to_str(starts_with_46[0]), "46.70.113.73");
    BOOST_CHECK_EQUAL(ip_to_str(starts_with_46[1]), "46.146.29.220");
    BOOST_CHECK_EQUAL(ip_to_str(starts_with_46[2]), "46.70.147.26");

    auto starts_with_46_70 = filter(ip_pool, 46, 70);
    BOOST_CHECK_EQUAL(starts_with_46_70.size(), 2);
    BOOST_CHECK_EQUAL(ip_to_str(starts_with_46_70[0]), "46.70.113.73");
    BOOST_CHECK_EQUAL(ip_to_str(starts_with_46_70[1]), "46.70.147.26");

    auto contains_70 = filter_any(ip_pool, 70);
    BOOST_CHECK_EQUAL(contains_70.size(), 3);
    BOOST_CHECK_EQUAL(ip_to_str(contains_70[0]), "46.70.113.73");
    BOOST_CHECK_EQUAL(ip_to_str(contains_70[1]), "46.70.147.26");
    BOOST_CHECK_EQUAL(ip_to_str(contains_70[2]), "1.1.70.46");
}

BOOST_AUTO_TEST_SUITE_END()