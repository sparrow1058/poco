#include "Poco/Exception.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include <Poco/Data/RecordSet.h>
#include <Poco/Tuple.h>
#include <stdint.h>
#include <vector>
#include <iostream>



using namespace Poco::Data::Keywords;
using namespace Poco;
using namespace Poco::Data;
using Poco::format;
using Poco::NotFoundException;

//====================一般步骤========================
//-----------------------注册---------------------------
//      MySQL::Connector::registerConnector();
//-------------创建 mysql Session(连接池)会话-------------------------
//Poco::Data::Session sess("MySQL",
//              "host=127.0.0.1;port=3306;user=root;password=123;db=test；auto-reconnect=true");
//每个参数都是在同一个字符串里的，用 ";" 隔开。
//这里面很多参数不是必须的都有默认值，但是生成环境 推荐加上auto-reconnect=true.
//------------------判断是否链接-------------------
//if (sess.isConnected())
//------------------操作数据库----------------------


/*
 * Poco::Data::Statement select(sess); 是可以省略的。因为我们 sess<< 时候会自动创建一个临时的 Statement
 *
 */

int main( )
{
    try
    {
        //--------------注册---------------------------
        MySQL::Connector::registerConnector();
        //------------创建会话-----------------------
        Poco::Data::Session sess("MySQL",
                "host=127.0.0.1;port=3306;user=root;password=;db=newpos;auto-reconnect=true");
        //-----------判断是否链接成功-------------
        if (sess.isConnected())
        {
            std::cout << "yes connection is successful" << std::endl;
        }
        else
        {
            std::cout << "connection is failed" << std::endl;
        }
      //  Poco::Data::Statement sql(sess);
      //  sql << "update users set modified=\'2014-12-30\', password=\'123456\' where username=\'yuni\'; "
        //"update radcheck set value=\'123456\' where username=\'yuni\' and attribute=\'Cleartext-Password\';"
    //    ;
     //   sql.execute();

///////下面的代码一般也用不到的吧。有兴趣的可以研究一下/////////
        //--------------------------元组--------------------------
        typedef Poco::Tuple< std::string ,std::string ,int> Person;
        typedef std::vector<Person> People;
        //-----------------------------1. 查询-------------------
//      //Poco::Data::Statement select(sess);
//      //可使用元组的方式
//      People data;
//
//      sess << "select * from person limit 10", into(data) ,now;
//      /////////////////////////uint32_t num = select.execute();//这一句的功能和 now 类似。都是立即执行语句。两者不可并存。
////        uint32_t num = sess.execute();//返回获取的行数
////        std::cout << "num:" << num << std::endl;
//      //显示内容
//      People::const_iterator it = data.begin();
//      for( ; it != data.end() ; it++ )
//      {
//          std::cout << it->get<0>() << "  ";
//          std::cout << it->get<1>() << "  ";
//          std::cout << it->get<2>() << std::endl;
//      }

        //-------------如果使用 limit() 或者 range() 那么注意使用 select.done() 来判断是否是全部取出数据
//      People data;
//      Poco::Data::Statement select( sess );
//      select << "select * from person ", into(data) ,range(0,1) ,now;
//
//      do{
//          select.execute();
//          std::cout << "one time" << std::endl;
//      }while( !select.done() );
//
//      People::const_iterator it = data.begin();
//      for (; it != data.end(); it++)
//      {
//          std::cout << it->get<0>() << "  ";
//          std::cout << it->get<1>() << "  ";
//          std::cout << it->get<2>() << std::endl;
//      }

        //----------------------------2.异步查询-------------------------------------
        Poco::Data::Statement select( sess );
        select << "select * from point", now;

        Poco::Data::RecordSet rs(select);
        std::size_t cols = rs.columnCount();
        std::cout << cols << std::endl;

        for (std::size_t col = 0; col < cols; col++)
        {
            std::cout << rs.columnName(col) << "       ";
        }

        std::string name = rs.value( "name", 0) ;
        std::cout <<  "\ndata:" << name << std::endl;
    } catch (MySQL::MySQLException &e)
    {
        std::cerr << "MySQLException : " << e.what() << std::endl;
    } catch (Poco::Exception &e)
    {
        std::cerr << "Exception : " << e.what() << std::endl;
    } catch (...)
    {
        std::cerr << "some error occur" << std::endl;
    }
}
