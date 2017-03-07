#ifndef ECHOHANDLER_H
#define ECHOHANDLER_H
#include "ihandler.h"

#include <queue>

class EchoHandler : public IHandler
{
public:
    EchoHandler();
    ~EchoHandler();

    void Handle(const std::string &buffer, std::string &out) override;

private:

};

#endif // ECHOHANDLER_H
