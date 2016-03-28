#include <iostream>
#include <memory>
#include "server.h"
#include "echohandler.h"

int main()
{
    try
    {
        EchoHandler handler;
        Server server("127.0.0.1","9989",handler);
        server.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

