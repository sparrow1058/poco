//Poechant TCp server
#ifndef POECHANT_TCP_SERVER
#define POECHANT_TCP_SERVER
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Application.h"

using Poco::Util::ServerApplication;
using Poco::Util::Application;
class PoechantTCPServer:public ServerApplication
{
public:
    PoechantTCPServer(){}
    ~PoechantTCPServer(){}
protected:
    void initialize(Application& self);
    void uninitialize();
    int main(const std::vector<std::string>&args);

};


#endif
