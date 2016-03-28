#ifndef CONNECTIONCONTAINER_H
#define CONNECTIONCONTAINER_H

#include <set>
#include "connection.h"

class Connection;

typedef std::shared_ptr<Connection> connection_ptr;

class ConnectionManager
{
public:
    ConnectionManager();
    void start(connection_ptr c);
    void stop(connection_ptr c);
    void stopAll();


    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager &) = delete;

private:
    std::set<connection_ptr> connections;

};

#endif // CONNECTIONCONTAINER_H
