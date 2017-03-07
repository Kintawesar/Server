#include "connection.h"

Connection::Connection(io_service &service, ip::tcp::socket socket, ConnectionManager &manager, IHandler &handler) :
    strand(service),
    socket(std::move(socket)),
    manager(manager),
    handler(handler)
{
}

Connection::~Connection()
{
    std::cout<<"connection remove"<<std::endl;
}

std::string Connection::makeString(boost::asio::streambuf &buf)
   {
       return{ boost::asio::buffers_begin(buf.data()),
           boost::asio::buffers_end(buf.data()) };
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


    boost::asio::async_read_until(socket, from, "\r\n",
                            strand.wrap([ this, self](boost::system::error_code ec, size_t)
    {
        if(!ec)
        {
            std::string s(makeString(from));
            handler.Handle(s.substr(0, s.size()-2), buf);

            doWrite();
        }
        else if( ec != error::operation_aborted)
            manager.stop(self);

    }));
}

void Connection::doWrite()
{
    auto self = shared_from_this();

    socket.async_write_some(buffer(buf.data(), buf.length()),
                            strand.wrap([this, self](boost::system::error_code ec, size_t )
    {
       if(!ec)
       {
           doRead();
       }

       if(ec != error::operation_aborted)
           manager.stop(self);
    }));
}


