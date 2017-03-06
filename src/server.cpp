#include "server.h"
#include <thread>

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
    try
    {
        acceptor.bind(endpoint);
    }
    catch( std::exception &e)
    {
        std::cerr << "Can't bind "<<e.what() << std::endl;
        return;
    }

    acceptor.listen();

    std::cout<<"server bind on " <<address <<" port "<<port <<std::endl;

    doAccept();

}

void Server::run()
{
    unsigned int thread_count = 4; //std::thread::hardware_concurrency();

    std::vector<std::shared_ptr<std::thread>> threads;
    for(unsigned i = 0; i< thread_count; ++i)
    {
        std::shared_ptr<std::thread> thr(new std::thread([this]()
        {
         service.run();

        }));

        threads.push_back(thr);
    }

    std::cout<<"server started on " << thread_count <<" threads "<<std::endl;



    //service.run();

    for (unsigned i = 0; i < threads.size(); ++i)
       threads[i]->join();

}

void Server::stop()
{
    service.stop();
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
            manager.start( std::make_shared<Connection>(service, std::move(socket), manager, handler) );

        }

        doAccept();

    });

}

