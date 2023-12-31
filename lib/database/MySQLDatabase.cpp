//
// Created by 11057 on 2023/11/18.
//

#include "MySQLDatabase.h"

using namespace std;

bool MySQLDatabase::connect(const std::string &host, const std::string &user, const std::string &password,
                            const std::string &database) {
    try {
        std::string connection_string = host;
        if (host.substr(0, 6) != "tcp://") {
            connection_string = "tcp://" + host;
        }
        size_t port_pos = connection_string.find(':', 6); // 从 "tcp://" 后开始查找
        if (port_pos == std::string::npos) {
            // 如果没有找到端口号，则添加默认端口 "3306"
            connection_string += ":3306";
        }

        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        connection.reset(driver->connect(connection_string, user, password));
        connection->setSchema(database);
        cout << "成功连接到  IP:" << host << " 数据库:" << database << endl;
    } catch (const sql::SQLException &e) {
        std::cerr << "连接失败: " << e.what() << std::endl;
        exit(1);
    }
}

void MySQLDatabase::execute(const std::string &query) {
    try {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        stmt->execute(query);
    } catch (const sql::SQLException &e) {
        std::cerr << "执行失败: " << e.what() << std::endl;
        exit(1);
    }
}

void MySQLDatabase::createTable(const std::string &TableName, bool replace) {
    try {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        if (replace) {
            stmt->execute("DROP TABLE IF EXISTS " + TableName);
        }
        stmt->execute("CREATE TABLE IF NOT EXISTS " + TableName + " ("
                                                                  "id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
                                                                  "name VARCHAR(30) NOT NULL,"
                                                                  "age INT UNSIGNED NOT NULL,"
                                                                  "address VARCHAR(50),"
                                                                  "salary DOUBLE(15,2)"
                                                                  ")ENGINE=InnoDB DEFAULT CHARSET=utf8;");
        stmt->execute("CREATE INDEX idx_name ON " + TableName + " (name);");
    } catch (const sql::SQLException &e) {
        std::cerr << "创建表失败: " << e.what() << std::endl;
        exit(1);
    }
}

