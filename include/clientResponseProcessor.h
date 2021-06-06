#include <string>
#include "httprestclient.h"
#include "json.hpp"


using tcp = boost::asio::ip::tcp;


/**
 * @brief template class which provides highlevel access/API communication with server backends via protocols such as https,...
 * 
 *  usage:  ResponseProcessor<HttpsRestClient> client{"www.SOMEHOSTADDRESS.com","username","pswd"};
 *          auto someObjFromJSON = client.getVersion("/SOMEAPI/v1.0/test?param1=1");
 * 
 * @details type of stream_ptr still depends on specific protocoll <ssl::stream<tcp::socket>> is coupled to https. Should be changed.
 * 
 * @tparam RCP communication protocol (HttpsRestClient,... ).
 */
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