#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

bool print_boost_version();

// Report a failure
void fail(beast::error_code ec, char const* what);


/**
 * @brief session allows to performs HTTP GET request and prints the response
 * 
 *  usage: The io_context is required for all I/O
 *  boost::asio::io_context ioc;
 *
 *  std::make_shared<session>(ioc)->run(host, port, target, version);
 *  //Run the I/O service. The call will return when the get operation is complete.
 *  ioc.run();
 * 
 */
class session : public std::enable_shared_from_this<session>
{
    tcp::resolver resolver_;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_; // (Must persist between reads)
    http::request<http::empty_body> req_;
    http::response<http::string_body> res_;

public:
 
    /**
     * @brief Construct a new session object with a strand to ensure that handlers do not execute concurrently. boost::asio::make_strand creates a strand object (=serialized function invocation) for an executor
     * 
     * @param ioc 
     */
    explicit session(net::io_context& ioc);

    /**
     * @brief To Launch the asynchronous operation. 
     * 
     * @param host 
     * @param port 
     * @param target 
     * @param version 
     */
    void run(char const* host,char const* port,char const* target,int version);

    void on_resolve(beast::error_code ec, tcp::resolver::results_type results);

    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type);

    void on_write(beast::error_code ec, std::size_t bytes_transferred);
    
    void on_read(beast::error_code ec, std::size_t bytes_transferred);

};



