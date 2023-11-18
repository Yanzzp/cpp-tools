#include  <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>


using namespace std;


int main() {
    try {
        // 初始化 MySQL 驱动
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

        // 创建连接
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://yanzzp.xyz:3306", "YanSQL", "123zpy"));

        // 连接到数据库
        con->setSchema("ToolsDB");

        // 如果连接成功
        std::cout << "连接成功" << std::endl;
    } catch (const sql::SQLException &e) {
        std::cerr << "连接失败: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}