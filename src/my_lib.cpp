#include <iostream>
#include <stdio.h>


#include "boost/version.hpp"

#include "my_lib.h"



/**
 * @brief Couts the version of the installed boost library.
 * 
 * @return bool
 */
bool print_boost_version()
{
    std::cout << "Boost version: " << BOOST_VERSION << std::endl;

    return true;
}


void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}