#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>
#include <memory>
#include <array>
#include "connectionmanager.h"
#include "ihandler.h"
#include <iostream>

using namespace boost::asio;

class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    Connection(const Connection &) = delete;
    Connection& operator=(const Connection &) = delete;

    explicit Connection(ip::tcp::socket socket, ConnectionManager &manager, IHandler &handler);
    ~Connection();

    void start();
    void stop();

private:
   void doRead();
   void doWrite();


   ip::tcp::socket socket;
   ConnectionManager &manager;
   IHandler &handler;

   std::array<char ,8192> socket_buffer;


};


#endif // CONNECTION_H
