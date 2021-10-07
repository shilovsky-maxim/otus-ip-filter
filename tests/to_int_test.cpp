#define BOOST_TEST_MODULE to_int_test

#include "helper_library.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(to_int_test)

BOOST_AUTO_TEST_CASE(to_int_test) 
{
    using namespace helper;

    auto res = convert_to_int("123");
    BOOST_CHECK_EQUAL(res.second, true);
    BOOST_CHECK_EQUAL(res.first, 123);

    auto res2 = convert_to_int("A12");
    BOOST_CHECK_EQUAL(res2.second, false);
    BOOST_CHECK_EQUAL(res2.first, -1);
    
}

BOOST_AUTO_TEST_SUITE_END()