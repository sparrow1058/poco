#include "PoechantTCPConnection.h"
#include "Poco/Util/Application"
#include "Poco/Timestamp.h"
#include "Poco/Execption.h"
#include "Poco/DataTimeFormatter.h"

PoechantTCPConnection(const StreamSocket& s,const str::string& arg1,int arg2,double arg3):TCPServerConnection(s),_arg1(arg1),_arg2(arg2),_arg3(arg3)
{

}
void run()
{

    Application& app=Application::instance();
    app.logger().information("Request from"+this->socket().peerAddress().toString());
    try
    {
        Timestamp now;
        std::string dt(DataTimeFormatter::format(now,_format));
        dt.append("\r\n");
        socket.sendBytes(dt.data(),(int)dt.length());
    }
    catch (Poco::Execption& e)
    {
        app.logger().log(e);
    }
}
