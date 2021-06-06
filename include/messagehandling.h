#ifndef MESSAGE_HANDLING_H
#define MESSAGE_HANDLING_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>

#include <boost/log/trivial.hpp>


class MessagePacket
{
  public:
    MessagePacket();

    void setMessage(std::string const& msg);

    std::string getMessage();

  private:
    std::string message;
};




class ProducerConsumerObjects
{
  public:
    static std::queue<MessagePacket> dataqueue;
};





#endif //end MESSAGE_HANDLING_H