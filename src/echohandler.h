#ifndef ECHOHANDLER_H
#define ECHOHANDLER_H
#include "ihandler.h"

#include <queue>

class EchoHandler : public IHandler
{
public:
    EchoHandler();
    ~EchoHandler();

    bool recvCallback(const std::string &buffer) override;
    std::string nextMessage() override;
    bool hasNext() override;

private:
    std::queue<std::string> echoQueue;

};

#endif // ECHOHANDLER_H
