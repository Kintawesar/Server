#ifndef IHANDLER
#define IHANDLER

#include <string>

class IHandler
{
public:
    IHandler() = default;
    virtual ~IHandler() = default;
    virtual bool recvCallback(const std::string &buffer) = 0;
    virtual std::string nextMessage() = 0;
    virtual bool hasNext() = 0;
};

#endif // IHANDLER

