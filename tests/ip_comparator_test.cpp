#define BOOST_TEST_MODULE ip_comparator_test

#include "helper_library.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_comparator_test)

BOOST_AUTO_TEST_CASE(ip_comparator_test) 
{
    using namespace helper;

    auto ip1 = split("1.1.1.1", '.');
    auto ip2 = split("1.2.1.1", '.');
    auto ip3 = split("1.10.1.1", '.');

    auto part_comparator = [](const auto& pt1, const auto& pt2)
    {
        return lex_compare_strings(pt2, pt1);
    };

    BOOST_CHECK_EQUAL(lex_compare_ip(ip1, ip2, part_comparator), false);
    BOOST_CHECK_EQUAL(lex_compare_ip(ip2, ip3, part_comparator), false);
    BOOST_CHECK_EQUAL(lex_compare_ip(ip3, ip1, part_comparator), true);
}

BOOST_AUTO_TEST_SUITE_END()