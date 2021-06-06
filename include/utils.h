#ifndef BASE_64_ENCODER_H
#define BASE_64_ENCODER_H

#include <boost/archive/iterators/base64_from_binary.hpp>
// #include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <sstream>
#include <string>
#include <iostream>



using namespace boost::archive::iterators;

/**
 * @brief handles base64 encoding (necessary for basic authentication transmission of username and passwords)
 * 
 */
class Base64Encoder
{
  public:
    static std::string encode(const std::string& string);

};

#endif //end BASE_64_ENCODER_H