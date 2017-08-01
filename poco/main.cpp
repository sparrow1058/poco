#include <Poco/Net/DNS.h>
#include <iostream>
using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;
int main(int argc,char **argv)
{
    if(argc!=2)
    {
        std::cout<<"Invalid argument number."<<std::endl;
    }
    const HostEntry& entry=DNS::hostByName(argv[1]);
    std::cout<<"Canonical Name: "<<entry.name()<<std::endl;

    const HostEntry::AliasList& aliases=entry.aliases();
    for(HostEntry::AliasList::const_iterator it=aliases.begin();it!=aliases.end(); ++it)
        std::cout<<"Alias: " << *it << std::endl;
    const HostEntry::AddressList & addrs=entry.addresses();
    for(HostEntry::AddressList::const_iterator it=addrs.begin();it!=addrs.end();++it)
        std::cout<<"Address: "<<it->toString() <<std::endl;
    return 0;

}
