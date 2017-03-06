#include "echohandler.h"
#include <iostream>

EchoHandler::EchoHandler() :
    IHandler(),
    messageSize(0)
{
}

EchoHandler::~EchoHandler()
{

}

bool EchoHandler::recvCallback(const std::string &buffer)
{

    msg.append(buffer);

    std::cout <<"recv message "<<msg<<std::endl;

    if(msg.size() < messageSize)
        return false;

    return true;
}

std::string EchoHandler::nextMessage()
{
//    if(hasNext())
//    {
//        std::string s = echoQueue.front();
//        echoQueue.pop();
//        return s;
//        std::cout<<"pop next"<<std::endl;
//    }

    return std::string();
}

bool EchoHandler::hasNext()
{
   // if(echoQueue.empty())
   // {
        return false;
 //   }
 //   else
 //   {
   //     return true;
 //   }
}

void EchoHandler::setMessageSize(const size_t s)
{
    messageSize = s;
}

