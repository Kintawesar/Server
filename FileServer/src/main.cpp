#include <iostream>
#include <memory>
#include "server.h"
#include "echohandler.h"

int main(int argc, char* argv[] )
{
    std::string iface("127.0.0.1");
    std::string port("9989");

    if(argc == 2)
    {
        iface = std::string(argv[1]);
    }
    else if(argc ==3)
    {
        iface = std::string(argv[1]);
        port = std::string(argv[2]);
    }


    try
    {
        EchoHandler handler;
        Server server(iface,port,handler);
        server.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

