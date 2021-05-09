#define BOOST_TEST_MODULE mylib_test

#include <boost/test/included/unit_test.hpp>
#include "my_lib.h"


BOOST_AUTO_TEST_SUITE( test_suite_project )

//initialize some variables or declare some functions


BOOST_AUTO_TEST_CASE(test_returning_boostversion)
{
    bool testversion = print_boost_version();
    BOOST_REQUIRE(testversion);	
}




BOOST_AUTO_TEST_SUITE_END()
