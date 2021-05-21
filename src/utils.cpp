#include "utils.h"

/**
 * @brief transforms a text string to a base64 encoded string. Took the example from https://www.boost.org/doc/libs/1_75_0/libs/serialization/doc/dataflow.html and one of the stackoverflow answers to question 7053538. The operation in the end computes the number of '=' that have to be appended.
 * 
 * @param string 
 * @return std::string 
 */
std::string Base64Encoder::encode(const std::string& string)
{
    std::stringstream os;

    typedef base64_from_binary<transform_width<std::string::const_iterator, 6, 8>> base64_text;

    auto tmpString = std::string(base64_text(std::begin(string)), base64_text(std::end(string)));
    
    return tmpString.append((3 - string.size() % 3) % 3, '=');
}