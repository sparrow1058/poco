#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include <vector>
#include <iostream>
using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
struct Person
{
    std::string name;
    std::string address;
    int age;
};

int main(int argc,char **argv)
{
	Poco::Data::SQLite::Connector::registerConnector();
	Session session("SQLite","test.db");
	session<<"DROP TABLE IF EXISTS Person",now;
	session<<"CREATE TABLE Person (Name VARCHAR(30),Address VARCHAR,Age INTEGER(3))",now;
	std::cout<<"open test db "<<std::endl;
	//Create a person struct
	Person person=
	{
		"leaf",
			"shenzhen",
			12
	};
	//Create sql query
	Statement insert(session);
	insert<<"INSERT INTO Person VALUES(?,?,?)",
		use(person.name),
		use(person.address),
		use(person.age);
	insert.execute();	//Insert one data

	person.name="lisa";
	person.address="spring";
	person.age=20;
	insert.execute();
	
	//Create  query
	Statement select(session);
	//Save one date
	select <<"SELECT NAME,Address,Age FROM Person",
		into(person.name),
		into(person.address),
		into(person.age),
		range(0,1);
	while(!select.done())
	{
		select.execute();
		std::cout<<person.name<<"  "<<person.address<<" "<<person.age<<std::endl;
	}
/*
	//Another type
	std::cout<<"an other type"<<std::endl;
	std::vector<std::string> names;
	session<<"SELECT Name FROM person",into(names),now;
	for(std::vector<std::string>::const_iterator it=names.begin();it!=names.end();++it)
		std::cout<<*it<<std::endl;
	Poco::Data::SQLite::Connector::unregisterConnector();
*/

// 另一种，把查询结果放入到容器中
    std::vector<std::string> names;
    session << "SELECT Name FROM Person",
        into(names),
        now;
 
    for (std::vector<std::string>::const_iterator it = names.begin(); it != names.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    //退出会话注册器
    Poco::Data::SQLite::Connector::unregisterConnector();
    return 0;

	return 0;
}


