#include "httprestclient.h"


void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}



HttpsRestClient::HttpsRestClient()
{
    ssl_ctx.set_verify_mode(ssl::context::verify_peer |
                        ssl::context::verify_fail_if_no_peer_cert);
    ssl_ctx.set_default_verify_paths();
    boost::certify::enable_native_https_server_verification(ssl_ctx);
}


std::unique_ptr<ssl::stream<tcp::socket>> HttpsRestClient::connect(std::string const& hostname)
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


http::response<http::string_body> HttpsRestClient::get(ssl::stream<tcp::socket>& stream,
        boost::string_view hostname,boost::string_view uri)
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

http::response<http::string_body> HttpsRestClient::get(ssl::stream<tcp::socket>& stream,
        boost::string_view hostname, boost::string_view uri, const std::string& username, const std::string& password)
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

tcp::resolver::results_type HttpsRestClient::resolve(std::string const& hostname)
{
    tcp::resolver resolver{ctx};
    return resolver.resolve(hostname, "https");
}

tcp::socket HttpsRestClient::sslConnection(std::string const& hostname)
{
    tcp::socket socket{ctx};
    asio::connect(socket, resolve(hostname));
    return socket;
}



HttpClient::HttpClient()
{}

std::unique_ptr<tcp::socket> HttpClient::connect(std::string const& hostname)
{

    auto stream = boost::make_unique<tcp::socket>(connection(hostname));
    return stream;
}

http::response<http::string_body> HttpClient::get(tcp::socket& stream,
        boost::string_view hostname,boost::string_view uri)
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

tcp::resolver::results_type HttpClient::resolve(std::string const& hostname)
{
    tcp::resolver resolver{ctx};
    return resolver.resolve(hostname, "http");
}

tcp::socket HttpClient::connection(std::string const& hostname)
{
    tcp::socket socket{ctx};
    asio::connect(socket, resolve(hostname));
    return socket;
}