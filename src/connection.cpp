#include "connection.h"

Connection::Connection(ip::tcp::socket socket, ConnectionManager &manager, IHandler &handler) :
    socket(std::move(socket)),
    manager(manager),
    handler(handler)
{
}

Connection::~Connection()
{
    std::cout<<"connection remove"<<std::endl;
}

void Connection::start()
{
    doRead();
}

void Connection::stop()
{
    socket.close();

}

void Connection::doRead()
{
    auto self = shared_from_this();

    socket.async_read_some(buffer(socket_buffer),
                           [this, self](boost::system::error_code ec, size_t)
    {
        if(!ec)
        {
            if(handler.recvCallback(std::string(socket_buffer.data())) == true)
                doWrite();
            else
                doRead();
        }
        else if( ec != error::operation_aborted)
            manager.stop(self);

    });

}

void Connection::doWrite()
{
    if(!handler.hasNext())
    {
        doRead();
        return;
    }

    auto self = shared_from_this();
    std::string s = handler.nextMessage();
    if(s.empty())
    {
        doRead();
        return;
    }
    std::cout<<"next messge is "<<s<<std::endl;

    socket.async_write_some(buffer(s.data(), s.length()),
                            [this, self](boost::system::error_code ec, size_t )
    {
       if(!ec)
       {
           doRead();
       }

       if(ec != error::operation_aborted)
           manager.stop(self);
    });



}


