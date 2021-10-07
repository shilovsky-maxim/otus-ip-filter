#define BOOST_TEST_MODULE split_test

#include "helper_library.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(split_test)

BOOST_AUTO_TEST_CASE(split_test) 
{
    using namespace helper;

    auto result = split("113.162.145.156\t111\t0",'\t');
    BOOST_CHECK_EQUAL(result.size(), 3);
    BOOST_CHECK_EQUAL(result.at(0), "113.162.145.156");
    auto ip = split(result.at(0),'.');
    BOOST_CHECK_EQUAL(ip.size(), 4);
    BOOST_CHECK_EQUAL(ip.at(0), "113");
    BOOST_CHECK_EQUAL(ip.at(1), "162");
    BOOST_CHECK_EQUAL(ip.at(2), "145");
    BOOST_CHECK_EQUAL(ip.at(3), "156");
}

BOOST_AUTO_TEST_SUITE_END()