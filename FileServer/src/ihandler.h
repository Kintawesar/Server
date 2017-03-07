#ifndef IHANDLER
#define IHANDLER

#include <string>

class IHandler
{
public:
    IHandler() = default;
    virtual ~IHandler() = default;
    virtual void Handle(const std::string &buffer, std::string &out) = 0;
};

#endif // IHANDLER

