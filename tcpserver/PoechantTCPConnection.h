//PoechantTCPConnection.h
#ifndef POECHANT_TCP_CONNECTION_H
#define POECHANT_TCP_CONNECTION_H
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string>
class PoechantTCPConnection:public TCPServerConnection
{

public :
    PoechantTCPConnection(const StreamSocket& s,const std::string& arg1,int arg2,double arg3);
    void run();
private:
    std::string _arg1;
    int _arg2;
    double _arg3;
};


#endif // POECHANT_TCP_CONNECTION_H
