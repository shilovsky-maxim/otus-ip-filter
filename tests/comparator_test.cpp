#define BOOST_TEST_MODULE comparator_test

#include "helper_library.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(comparator_test)

BOOST_AUTO_TEST_CASE(comparator_test) 
{
    using namespace helper;

    BOOST_CHECK_EQUAL(lex_compare_strings("1", "2"), true);
    BOOST_CHECK_EQUAL(lex_compare_strings("10", "2"), false);
    BOOST_CHECK_EQUAL(lex_compare_strings("A", "B"), true);
    BOOST_CHECK_EQUAL(lex_compare_strings("A", "12"), false);
    
}

BOOST_AUTO_TEST_SUITE_END()