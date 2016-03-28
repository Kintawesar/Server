#ifndef SERVER_H
#define SERVER_H


#include <boost/asio.hpp>
#include <string>
#include "connectionmanager.h"
#include "ihandler.h"

using namespace boost::asio;


class Server
{
public:
    explicit Server(const std::string &address, const std::string &port, IHandler &handler);

    void run();

    Server(const Server &) = delete;
    Server& operator=(const Server &) = delete;


private:
    void doAwaitStop();
    void doAccept();

    io_service service;
    signal_set signal;
    ip::tcp::socket socket;
    ip::tcp::acceptor acceptor;
    ConnectionManager manager;
    IHandler &handler;


};

#endif // SERVER_H
