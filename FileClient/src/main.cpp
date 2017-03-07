#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using boost::asio::ip::tcp;
using namespace boost::asio;
namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "FileName not set! "<<std::endl;
        return;
    }

    const std::string fileName(argv[1]);

    try
    {
        io_service io;
        tcp::socket socket(io);
        tcp::resolver resolver(io);

        tcp::resolver::query query("127.0.0.1", "9989");
        tcp::resolver::iterator iterator = resolver.resolve(query);

        boost::asio::connect(socket, iterator);

        std::cout << "connect to server " << std::endl;

        
        std::string data(fileName);
        data.append("\r\n");

        std::cout << "send " << data << std::endl;

        boost::asio::streambuf to;
        std::ostream os(&to);

        os << data;

        boost::asio::write(socket, to);

        boost::asio::streambuf fromServer;


         const fs::path file{fileName};

         fs::ofstream ofs{file, std::ios_base::binary};

         boost::system::error_code error;
         while( boost::asio::read(socket, fromServer,
                                boost::asio::transfer_at_least(1), error ))
         {
             ofs << &fromServer;
         }

         ofs.close();

         std::cout << "file saved" << std::endl;

         if(error != boost::asio::error::eof)
         {
             throw boost::system::system_error(error);
         }

    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

