#include "echohandler.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace fs = boost::filesystem;

EchoHandler::EchoHandler() :
    IHandler()
{
}

EchoHandler::~EchoHandler()
{

}

void EchoHandler::Handle(const std::string &buffer, std::string &out)
{
    std::cout << "file name is "<<buffer << std::endl;
    try
    {
       const fs::path f = fs::system_complete(fs::path(buffer));
       std::cout << f.string()  << std::endl;

       fs::ifstream file(f, std::ios_base::binary);
       if(file.fail())
       {
           std::cerr << "error open file "<< buffer << std::endl;
           return;
       }

       auto size = fs::file_size(f);
       std::cout << "filesize "<< size << std::endl;

       out.resize(size);
       file.read(&out[0], size);

       file.close();
    }
    catch(const fs::filesystem_error &e)
    {
        std::cerr <<  e.what() << std::endl;;
    }


}
