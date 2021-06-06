#ifndef HTTP_REST_CLIENT_H
#define HTTP_REST_CLIENT_H


#include "utils.h"

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>

#include <boost/certify/extensions.hpp>
#include <boost/certify/https_verification.hpp>


#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

//#include "json.hpp"


namespace beast = boost::beast;
namespace asio = boost::asio;
namespace ssl = asio::ssl;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

using namespace std;


bool print_boost_version();

void fail(beast::error_code ec, char const* what);

/**
 * @brief interface for different client communication protocols (e.g. https, http, ...)
 * 
 *
 * 
 */
template <typename SOCTYPE>
class RestClientProtocoll
{
  public:
    virtual ~RestClientProtocoll() = default;
    virtual std::unique_ptr<SOCTYPE> connect(std::string const& hostname) = 0; 
    virtual http::response<http::string_body> get(SOCTYPE& stream,boost::string_view hostname,boost::string_view uri) = 0;
    virtual http::response<http::string_body> get(SOCTYPE& stream,boost::string_view hostname,
                                                    boost::string_view uri, const std::string& username, const std::string& password) = 0;
};


/**
 * @brief client communication for https connection
 * 
 *  usage:  ResponseProcessor<HttpsRestClient> client{"www.SOMEHOSTADDRESS.com","username","pswd"};
 *          auto someObjFromJSON = client.getVersion("/SOMEAPI/v1.0/test?param1=1");
 *
 */
class HttpsRestClient : RestClientProtocoll<ssl::stream<tcp::socket>>
{
  public:
    /**
     * @brief Construct a new Https Rest Client object
     * 
     */
    HttpsRestClient();

    /**
     * @brief 
     * 
     * @param hostname 
     * @return std::unique_ptr<ssl::stream<tcp::socket>> 
     */
    std::unique_ptr<ssl::stream<tcp::socket>> connect(std::string const& hostname) override;

    /**
     * @brief 
     * 
     * @param stream 
     * @param hostname 
     * @param uri 
     * @return http::response<http::string_body> 
     */
    http::response<http::string_body> get(ssl::stream<tcp::socket>& stream,
                                boost::string_view hostname,boost::string_view uri) override;

    /**
     * @brief 
     * 
     * @param stream 
     * @param hostname 
     * @param uri 
     * @param username 
     * @param password 
     * @return http::response<http::string_body> 
     */
    http::response<http::string_body>
    get(ssl::stream<tcp::socket>& stream, boost::string_view hostname, boost::string_view uri,
        const std::string& username, const std::string& password) override;

  private:
    asio::io_context ctx;
    ssl::context ssl_ctx{ssl::context::tls_client};
    std::unique_ptr<ssl::stream<tcp::socket>> stream_ptr;


    tcp::resolver::results_type resolve(std::string const& hostname);

    tcp::socket sslConnection(std::string const& hostname);

};





class HttpClient : RestClientProtocoll<tcp::socket>
{
  public:
    HttpClient();

    std::unique_ptr<tcp::socket> connect(std::string const& hostname) override;


    http::response<http::string_body> get(tcp::socket& stream,
                                    boost::string_view hostname,
                                    boost::string_view uri) override;



  private:
    std::unique_ptr<tcp::socket> stream_ptr;
    asio::io_context ctx;

    tcp::resolver::results_type resolve(std::string const& hostname);

    tcp::socket connection(std::string const& hostname);

};




#endif //end HTTP_REST_CLIENT_H