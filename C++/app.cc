#include <iostream>
#include<mysql-cppconn-8/mysqlx/xdevapi.h>
#include<thread>
using namespace mysqlx;
 
void ptUser() {
    using std::cout;
    using std::endl;
    using std::vector;
 
    try {
        const char* url = "mysqlx://mazamu:Aa5505229@127.0.0.1:33060/webserver?ssl-mode=disabled";  
        //注意 mysqlcppconn8 默认使用的端口：33060，若连接3306端口会提示错误
        //使用用户名：root
        //用户 root 的密码是：rootpwd
        //主机：127.0.0.1
        //端口：33060
        //数据库：webserver
 
        cout << "Creating session on " << url
             << " ..." << endl;
 
        SessionSettings option("127.0.0.1", 33060, "mazamu", "Aa5505229");
        Session sess(option); //也可使用这种方式连接
        //Session sess(url);  第一种方式建立连接
        
        auto schema = sess.createSchema("webserver",true);
        sess.sql(R"(use webserver)").execute();
        auto tableName = schema.getTableNames();
        for(auto i = tableName.begin(); i != tableName.end(); ++i) {
            cout<<"tableName :"<< *i<<endl;
        }
        auto table = schema.getTable("test",true);
        auto it1 = table.insert("film_id","title","description");
        string a = "hello16aaaaaaaaaaaaaaaaaaaaaaaaaaa";
        string b = "dsaadcacsadcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaadfdsaaaaaaaaaaaaaa";
        int j = 16;
        for(int i = 16; i < 1000000; ++i) {
            it1.values(i,a,b);
            if(j % 250000 == 0) {
                it1.execute();
                cout<<"finished"<<j<<endl;
            }
            ++j;
        }
        it1.execute();
        // table.getSession().sql(R"()").execute();
        // table.getSession().sql(R"(insert into film (`film_id`, `title`, `description` ) values
        //                  ('11', 'hellome', '654321aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa'))"
        //                  ).execute();
        auto rows = table.count();
        cout<<rows<<endl;
        // for(auto it : rows) {
        //     cout<< it.get(0).get<int>()<<"  ";
        //     cout<< it.get(1).get<string>()<<"  ";
        //     cout<< it.get(2).get<string>()<<"  ";
        //     cout<<endl;
        // }

        // cout <<"Done!" <<endl;
        // cout <<"Session accepted, creating collection..." <<endl;
        // sess.sql("use films").execute();  //使用数据库 webserver

        // //如何存取时间类型值，在 mysqlcppconn8 中并没有很好的规定
        // //注意，我们在此处将字符串转为 timestamp 类型，以插入该条数据
        // // sess.sql(R"(insert into user (`username`, `email`, `password`, `create_time`) values
        // //                  ('ice', 'kawaii@qq.com', '654321', timestamp('2020-06-14 17:00:00')))"
        // //                  ).execute();
 
        // //注意，我们在此处 timestamp 类型转换为字符串，以取出该条数据
        // RowResult rs = sess.sql("select username, email, password, cast(create_time as char) from user").execute();
        // for (auto it = rs.begin();it != rs.end();++it){
        //     cout << (*it).get(0).get<string>() <<" ";
        //     cout << (*it).get(1).get<string>() <<" ";
        //     cout << (*it).get(2).get<string>() <<" ";
        //     cout << (*it).get(3).get<string>();
        //     cout << endl;
        // }
 
    } catch (const Error& e) {
        cout << e.what() <<endl;
    }
}
int main()
{
    ptUser();
    return 0;
}