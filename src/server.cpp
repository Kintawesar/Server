#include "server.h"

Server::Server(const std::string &address, const std::string &port, IHandler &handler) :
    service(),
    signal(service),
    socket(service),
    acceptor(service),
    handler(handler)
{
    signal.add(SIGINT);
    signal.add(SIGTERM);
    signal.add(SIGQUIT);

    doAwaitStop();

    ip::tcp::resolver resolver(service);
    ip::tcp::endpoint endpoint = *resolver.resolve({address, port});

    acceptor.open(endpoint.protocol());
    acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();

    doAccept();

}

void Server::run()
{
    std::cout<<"server started "<<std::endl;
    service.run();

}

void Server::doAwaitStop()
{
    signal.async_wait( [this](boost::system::error_code, int)
    {
        acceptor.close();
        manager.stopAll();
        std::cout<<"server stoped"<<std::endl;
    });

}

void Server::doAccept()
{
    acceptor.async_accept(socket, [this](boost::system::error_code ec)
    {
        if(!acceptor.is_open())
            return;

        if(!ec)
        {
            std::cout<<"new client accepted"<<std::endl;
            manager.start( std::make_shared<Connection>( std::move(socket), manager, handler) );

        }

        doAccept();

    });

}

