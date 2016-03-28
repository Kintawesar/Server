#include "echohandler.h"
#include <iostream>

EchoHandler::EchoHandler() :
    IHandler()
{
}

EchoHandler::~EchoHandler()
{

}

bool EchoHandler::recvCallback(const std::string &buffer)
{
    echoQueue.push(buffer);
    std::cout <<"recv message "<<buffer<<std::endl;

    return true;
}

std::string EchoHandler::nextMessage()
{
    if(hasNext())
    {
        std::string s = echoQueue.front();
        echoQueue.pop();
        return s;
        std::cout<<"pop next"<<std::endl;
    }
    else
        return std::string();

}

bool EchoHandler::hasNext()
{
    if(echoQueue.empty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

