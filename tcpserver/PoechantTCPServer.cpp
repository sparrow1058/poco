#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServer.h"
#include "PoechantTCPServer.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/DateTimeFormat.h"
#include "PoechantTCPConnectionFactory.h"

using Poco::Net::ServerSocket;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Net::TCPServer;
using Poco::DateTimeFormat;

void PoechantTCPServer::initialize(Application& self)
{
    ServerApplication::loadConfiguration();
    ServerApplication::initialize(self);
}
void PoechantTCPServer::uninitialize()
{
    ServerApplication::uninitialize();
}
int PoechantTCPServer::main(const std::vector<std::string>& args)
{
   unsigned short port=(unsigned short) config().getInt("PoechantTCPServer.port",123456);
   std::string format(config().getString("PoechantTCPServer.format",DateTimeFormat::ISO8601_FORMAT));
 //1 Bind server socket
 ServerSocket serverSocket(port);
 //2 Pass the serversocket to a tcpserver
 TCPServer server(new PoechantTCPConnectionFactory(format),serverSocket);
 //3 Start the TCPServer
 server.start();
 //4 Wait for termination
 waitForTerminationRequest();
 //5. Stop the TCPServer
 server.stop();

    return Application::EXIT_OK;
}
