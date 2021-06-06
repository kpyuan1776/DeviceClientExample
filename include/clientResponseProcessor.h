#include <string>
#include "httprestclient.h"
#include "json.hpp"


using tcp = boost::asio::ip::tcp;



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