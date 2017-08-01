#include "ReactorTest.h"
#include "Poco/String.h"
#include "Poco/Format.h"
#include "Poco/Exception.h"
//#include "Poco/Data/Common.h"
//#include "Poco/Data/BLOB.h"
#include "Poco/Data/StatementImpl.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/LOB.h"
#include <iostream>
#include <limits>
#include "Poco/Data/MySQL/MySQL.h"
#include "Poco/Data/Session.h"



#include "Poco/Exception.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include <Poco/Tuple.h>
#include <stdint.h>
#include <vector>


using namespace Poco::Data::Keywords;
using namespace Poco;
using namespace Poco::Data;
using Poco::format;
using Poco::NotFoundException;


using Poco::Net::ReadableNotification;
using Poco::Net::StreamSocket;
using Poco::Net::SocketReactor;
using Poco::Observer;
using Poco::Net::ServerSocket;
using Poco::Net::SocketAcceptor;

//using namespace Poco::Data;
using Poco::Data::MySQL::ConnectionException;
using Poco::Data::MySQL::StatementException;
using Poco::Data::StatementImpl;
using Poco::Data::Session;
using Poco::Data::SessionFactory;



class MyHandler{
public:
    MyHandler(StreamSocket& socket,SocketReactor& reactor):_socket(socket),_reactor(reactor)
    {
        _peerAddress=socket.peerAddress().toString();
        std::cout<<"Connection from "<<_peerAddress<<"..."<<std::endl;
        _reactor.addEventHandler(_socket,Observer<MyHandler,ReadableNotification>(*this,&MyHandler::onReadable));
    }
    ~MyHandler()
    {
        std::cout<<_peerAddress<<"disConnected ...."<<std::endl;
        _reactor.removeEventHandler(_socket,Observer<MyHandler,ReadableNotification>(*this,&MyHandler::onReadable));
    }
    void onReadable(ReadableNotification *pNf)
    {

        pNf->release();
        char buffer[8];
        int n=_socket.receiveBytes(buffer,sizeof(buffer));
        if(n>0)
        {
            _socket.sendBytes(buffer,n);
            _socket.sendBytes("\n",1);
            std::cout<<"receive buffer from "<<_peerAddress<<":"<<std::string(buffer,n)<<std::endl;
        }else{
            _socket.shutdownSend();
            delete this;
        }
    }
private:
    StreamSocket _socket;
    std::string _peerAddress;
    SocketReactor& _reactor;
};
Poco::SharedPtr<Poco::Data::Session> _pSession=0;
//Poco::SharedPtr<SQLExecutor> _pExecutor=0;
std::string _dbConnString="user=root;password=;db=mysql;compress=true;auto-reconnect=true";
int t_main()
{
    MySQL::Connector::registerConnector();
    try
    {
        _pSession=new Session(SessionFactory::instance().create(MySQL::Connector::KEY,_dbConnString));

    }catch(ConnectionException& ex)
    {
        std::cout<<"!!! Warning: Connection failed. MySQL Test will fail!!!!"<<std::endl;
        std::cout<<ex.displayText()<<std::endl;
    }
    if(_pSession &&_pSession->isConnected())
        std::cout<<"*** Connected to "<<'('<<_dbConnString<<')'<<std::endl;
    int i;
    Poco::Data::Session ses(MySQL::Connector::KEY,_dbConnString);
    int count=0;
    ses<<"SELECT COUNT(*) FROM SMART",into(count),now;
    std::cout<<"Stress has "<<count<<std::endl;
    MySQL::Connector::unregisterConnector();

    std::cin>>i;
    return 0;

}
int main(int argc,char **argv)
{
   // cout << "Hello world!" << endl;
    t_main();

/*
    unsigned short port=7070;
    ServerSocket serverSocket(port);
    SocketReactor reactor;
    SocketAcceptor<MyHandler> acceptor(serverSocket,reactor);
    std::cout<<"\nReactor:\""<<argv[0]<<"\"starting..."<<std::endl;
    reactor.run();
     std::cout<<"\nReactor:\""<<argv[0]<<"\"stop..."<<std::endl;
    return EXIT_SUCCESS;
*/
}


