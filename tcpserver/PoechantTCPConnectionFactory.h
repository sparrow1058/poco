#ifndef POECHANT_TCP_CONNECTION_FACTORY_H
#define POECHANT_TCP_CONNECTION_FACTORY_H
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"

using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;

class PoechantTCPConnectionFactory:public TCPServerConectionFactory
{
public:
    PoechantTCPConnectionFactory(const std::string arg1,int arg2,double arg3): _arg1(arg1),_arg2(arg2),_arg3(arg3){}
    TCPServerConnection * createConnection(const StreamSocket&socket)
    {
        return new PoechantTCPConnection(socket,arg1,arg2,arg3);
    }
private:
    std::string arg1;
    int arg2;
    double arg3;
};

#endif // POECHANT_TCP_CONNECTION_FACTORY_H
