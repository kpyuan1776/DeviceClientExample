#include "messagehandling.h"


MessagePacket::MessagePacket()
{
    BOOST_LOG_TRIVIAL(trace) << "MessagePacket::constructor";
}

void MessagePacket::setMessage(std::string const& msg)
{
    BOOST_LOG_TRIVIAL(trace) << "MessagePacket::setMessage";
    message = msg;
}

std::string MessagePacket::getMessage()
{
    BOOST_LOG_TRIVIAL(trace) << "MessagePacket::getMessage";
    return message;
}





std::queue<MessagePacket> ProducerConsumerObjects::dataqueue;