#ifndef HTTP_REST_CLIENT_ENCODER_H
#define HTTP_REST_CLIENT_ENCODER_H

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

#include "json.hpp"


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
    HttpsRestClient()
    {
        ssl_ctx.set_verify_mode(ssl::context::verify_peer |
                            ssl::context::verify_fail_if_no_peer_cert);
        ssl_ctx.set_default_verify_paths();
        boost::certify::enable_native_https_server_verification(ssl_ctx);
    }

    std::unique_ptr<ssl::stream<tcp::socket>>
    connect(std::string const& hostname) override
    {
        auto stream = boost::make_unique<ssl::stream<tcp::socket>>(
        sslConnection(hostname), ssl_ctx);
        // tag::stream_setup_source[]
        boost::certify::set_server_hostname(*stream, hostname);
        boost::certify::sni_hostname(*stream, hostname);
        // end::stream_setup_source[]

        stream->handshake(ssl::stream_base::handshake_type::client);
        return stream;
    }

    http::response<http::string_body>
    get(ssl::stream<tcp::socket>& stream,
        boost::string_view hostname,
        boost::string_view uri)
    {
        http::request<http::empty_body> request;
        request.method(http::verb::get);
        request.target(uri);
        request.keep_alive(false);
        request.set(http::field::host, hostname);
        http::write(stream, request);

        http::response<http::string_body> response;
        beast::flat_buffer buffer;
        http::read(stream, buffer, response);

        return response;
    }

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
    get(ssl::stream<tcp::socket>& stream,
        boost::string_view hostname,
        boost::string_view uri,
        const std::string& username,
        const std::string& password)
    {
        http::request<http::empty_body> request;
        request.method(http::verb::get);
        request.target(uri);
        request.keep_alive(false);
        request.set(http::field::host, hostname);
        request.set(boost::beast::http::field::authorization,
            "Basic " + Base64Encoder::encode(username+":"+password));

        http::write(stream, request);

        http::response<http::string_body> response;
        beast::flat_buffer buffer;
        http::read(stream, buffer, response);

        return response;
    }

  private:
    asio::io_context ctx;
    ssl::context ssl_ctx{ssl::context::tls_client};
    std::unique_ptr<ssl::stream<tcp::socket>> stream_ptr;


    tcp::resolver::results_type
    resolve(std::string const& hostname)
    {
        tcp::resolver resolver{ctx};
        return resolver.resolve(hostname, "https");
    }

    tcp::socket
    sslConnection(std::string const& hostname)
    {
        tcp::socket socket{ctx};
        asio::connect(socket, resolve(hostname));
        return socket;
    }

};





class HttpClient : RestClientProtocoll<tcp::socket>
{
  public:
    HttpClient()
    {}

    std::unique_ptr<tcp::socket>
    connect(std::string const& hostname) override
    {

        auto stream = boost::make_unique<tcp::socket>(connection(hostname));
        return stream;
    }


    http::response<http::string_body>
    get(tcp::socket& stream,
        boost::string_view hostname,
        boost::string_view uri)
    {
        http::request<http::empty_body> request;
        request.method(http::verb::get);
        request.target(uri);
        request.keep_alive(false);
        request.set(http::field::host, hostname);
        http::write(stream, request);

        http::response<http::string_body> response;
        beast::flat_buffer buffer;
        http::read(stream, buffer, response);

        return response;
    }


  private:
    std::unique_ptr<tcp::socket> stream_ptr;
    asio::io_context ctx;

    tcp::resolver::results_type
    resolve(std::string const& hostname)
    {
        tcp::resolver resolver{ctx};
        return resolver.resolve(hostname, "http");
    }

    tcp::socket
    connection(std::string const& hostname)
    {
        tcp::socket socket{ctx};
        asio::connect(socket, resolve(hostname));
        return socket;
    }

};




template <typename RCP>
class ResponseProcessor
{
  public:
    ResponseProcessor(const std::string& hostname, const std::string& user,
                const std::string& pswd): host(hostname), username(user), password(pswd)
    {}

    ResponseProcessor(const std::string& hostname): host(hostname)
    {}

    json::JSON getVersion(const std::string& uri)
    {
        stream_ptr = restClientProtocol.connect(host);
        auto response = restClientProtocol.get(*stream_ptr, host, uri, username, password);
        stream_ptr->shutdown(ec);
        stream_ptr->next_layer().close(ec);
        return json::JSON::Load( response.body() );
    }

  private:
    std::string host;
    std::string username;
    std::string password;
    boost::system::error_code ec;
    std::unique_ptr<ssl::stream<tcp::socket>> stream_ptr;
    RCP restClientProtocol{};    
};









#endif //end HTTP_REST_CLIENT_ENCODER_H